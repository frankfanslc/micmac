#include "ZBufferRaster.h"
#include "../DrawOnMesh.h"

string aPatFIm, aMesh, aOri;
int nInt = 0;
Pt2di aSzW;
int rech=1;
double distMax = DBL_MAX;
bool withLbl = true;
bool aNoTif = false;
int method = 3;
double MD_SEUIL_SURF_TRIANGLE = TT_SEUIL_SURF;


extern void sortDescendPt2diY(vector<Pt2di> & input);

cParamZbufferRaster::cParamZbufferRaster():
    mFarScene (false),
    mInt (0),
    mrech (1),
    mDistMax (DBL_MAX),
    mWithLbl (true),
    mNoTif   (false),
    mMethod  (3),
    MD_SEUIL_SURF_TRIANGLE (TT_SEUIL_SURF)
{}



int ZBufferRaster_main(int argc,char ** argv)
{
    cParamZbufferRaster aParam;
    ElInitArgMain
            (
                argc,argv,
                //mandatory arguments
                LArgMain()
                << EAMC(aParam.mMesh, "Mesh",     eSAM_IsExistFile)
                << EAMC(aParam.mPatFIm, "Pattern Image",  eSAM_IsPatFile)
                << EAMC(aParam.mOri, "Ori",       eSAM_IsExistDirOri),
                //optional arguments
                LArgMain()
                << EAM(aParam.mInt, "nInt", true, "niveau Interaction")
                << EAM(aParam.mSzW,  "aSzw",true,"if visu [x,y]")
                << EAM(aParam.mrech,  "rech",true,"cal ZBuff in img Resample - default =1.0 - 2 => 2 times <")
                << EAM(aParam.mDistMax,  "distMax",true,"limit distant cover Maximum from camera - default = NO LIMIT")
                << EAM(aParam.mWithLbl,  "withLbl",true,"Do image label (image label of triangle in surface)")
                << EAM(aParam.mMethod,  "method",true,"method of grab pixel in triangle (1=very good (low), 3=fast (not so good - def))")
                << EAM(aParam.MD_SEUIL_SURF_TRIANGLE, "surfTri", true, "Threshold of surface to filter triangle too small (def=100)")
                << EAM(aParam.mFarScene, "farScene", true, "Detect far scene part")
             );

    if (MMVisualMode) return EXIT_SUCCESS;
    string aDir, aPatIm;
    SplitDirAndFile(aDir, aPatIm, aParam.mPatFIm);
    cInterfChantierNameManipulateur * aICNM = cInterfChantierNameManipulateur::BasicAlloc(aDir);
    vector<string>  vImg = *(aICNM->Get(aPatIm));

    //===========Modifier ou chercher l'image si l'image ne sont pas tif============//
    std::size_t found = aParam.mPatFIm.find_last_of(".");
    string ext = aParam.mPatFIm.substr(found+1);
    cout<<"Ext : "<<ext<<endl;
    if ( ext.compare("tif") )   //ext equal tif
    {
        aNoTif = true;
        cout<<" No Tif"<<endl;
    }
    if (aNoTif)
    {
        list<string> cmd;
        for (uint aK=0; aK<vImg.size(); aK++)
        {
             string aCmd = MM3DStr +  " PastDevlop "+  vImg[aK] + " Sz1=-1 Sz2=-1 Coul8B=0";
             cmd.push_back(aCmd);
        }
        cEl_GPAO::DoComInParal(cmd);
    }
    //===============================================================================//

    StdCorrecNameOrient(aParam.mOri,aDir,true);

    vector<cTri3D> aVTri;

    cout<<"Lire mesh...";
    ElTimer aChrono;
    cMesh myMesh(aParam.mMesh, true);
    const int nFaces = myMesh.getFacesNumber();
    std::set<int> aSetInd;
    for (double aKTri=0; aKTri<nFaces; aKTri++)
    {
        cTriangle* aTri = myMesh.getTriangle(aKTri);
        vector<Pt3dr> aSm;
        aTri->getVertexes(aSm);
        cTri3D aTri3D (   aSm[0],
                          aSm[1],
                          aSm[2],
                          aKTri
                      );
        aVTri.push_back(aTri3D);
        if (aParam.mFarScene)
            aSetInd.insert(aKTri);
    }
    cout<<"Finish - time "<<aChrono.uval()<<" - NbTri : "<<aVTri.size()<<endl;

    cAppliZBufferRaster * aAppli = new cAppliZBufferRaster(aICNM, aDir, aParam.mOri, aVTri, vImg, aNoTif, aParam);

    aAppli->NInt() = aParam.mInt;
    if (EAMIsInit(&aSzW))
    {
        aAppli->SzW() = aParam.mSzW;
    }
    if (EAMIsInit(&aParam.mDistMax))
    {
        aAppli->DistMax() = aParam.mDistMax;
    }
    if (EAMIsInit(& aParam.MD_SEUIL_SURF_TRIANGLE))
        aAppli->SEUIL_SURF_TRIANGLE()=aParam.MD_SEUIL_SURF_TRIANGLE;
    aAppli->Method() = aParam.mMethod;
    aAppli->WithImgLabel() = aParam.mWithLbl;
    aAppli->Reech() = 1.0/double(aParam.mrech);
    aAppli->SetNameMesh(aParam.mMesh);
    aAppli->DoAllIm();

    // statistic far scene part
    //set <int> aTriToWrite;
    DrawOnMesh aDraw;
    vector<vector<Pt3dr> > aTriToWrite;
    if (aParam.mFarScene)
    {
        string farSceneMesh = aParam.mMesh.substr(0,aParam.mMesh.length()-4) + "_Far.ply";
        sortDescendPt2diY(aAppli->AccNbImgVisible());
        int aCount{0};
        for (int aKK=0; aKK<aAppli->AccNbImgVisible().size(); aKK++)
        {
            if (aAppli->AccNbImgVisible()[aKK].y == vImg.size())
            {
                aCount++;
                vector<Pt3dr> aOneTri;
                aOneTri.push_back(aVTri[aKK].P1());
                aOneTri.push_back(aVTri[aKK].P2());
                aOneTri.push_back(aVTri[aKK].P3());
                aTriToWrite.push_back(aOneTri);
                //aTriToWrite.insert(aKK);
            }
            else
            {
                //myMesh.removeTriangle(aKK); // trop lent
            }
        }
        cout<<"Write mesh .. "<<endl;
        aDraw.drawListTriangle(aTriToWrite, farSceneMesh, Pt3dr(255,0,0));
        //myMesh.Export(farSceneMesh, aTriToWrite);
        cout<<"Nb Tri View by all Img : "<<aCount<<" / "<< aVTri.size()<<endl;
    }

    return EXIT_SUCCESS;
}
