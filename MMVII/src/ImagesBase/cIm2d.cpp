#include "include/MMVII_all.h"
#include "include/MMVII_Tpl_Images.h"

namespace MMVII
{

cPt2di DifInSz(const std::string & aN1,const std::string & aN2)
{
    cDataFileIm2D aD1 = cDataFileIm2D::Create(aN1,false);
    cDataFileIm2D aD2 = cDataFileIm2D::Create(aN2,false);

    return aD1.Sz() - aD2.Sz();
}


/* ========================== */
/*          cDataIm2D         */
/* ========================== */



template <class Type>  cDataIm2D<Type>::cDataIm2D(const cPt2di & aP0,const cPt2di & aP1,Type * aRawDataLin,eModeInitImage aModeInit) : 
    cDataTypedIm<Type,2> (aP0,aP1,aRawDataLin,aModeInit),
    mSzYMax (tPB::Sz().y())
{
    mRawData2D = cMemManager::Alloc<tVal*>(mSzYMax) -Y0();
    PostInit();
}

template <class Type> void  cDataIm2D<Type>::PostInit()
{
    for (int aY=Y0() ; aY<Y1() ; aY++)
        mRawData2D[aY] = tBI::mRawDataLin + (aY-Y0()) * SzX() - X0();
}


template <class T> void  cDataIm2D<T>::Resize(const cPt2di& aP0,const cPt2di & aP1,eModeInitImage aMode) 
{
    int aPrevY0 = Y0();
    cDataTypedIm<T,2>::Resize(aP0,aP1,aMode);
    cMemManager::Resize(mRawData2D,aPrevY0,mSzYMax,Y0(),Sz().y());
    PostInit();
}

template <class T> void cDataIm2D<T>::Resize(const cPt2di& aSz,eModeInitImage aMode)
{
   Resize(cPt2di(0,0),aSz,aMode);
}



template <class Type>  cDataIm2D<Type>::~cDataIm2D()
{
   cMemManager::Free(mRawData2D+Y0());
}

// template <class Type>  cDataIm2D<Type>::

template <class Type> int     cDataIm2D<Type>::VI_GetV(const cPt2di& aP)  const
{
   return GetV(aP);
}
template <class Type> double  cDataIm2D<Type>::VD_GetV(const cPt2di& aP)  const 
{
   return GetV(aP);
}

template <class Type> void  cDataIm2D<Type>::VI_SetV(const cPt2di& aP,const int & aV)
{
   SetVTrunc(aP,aV);
}
template <class Type> void  cDataIm2D<Type>::VD_SetV(const cPt2di& aP,const double & aV)
{
   SetVTrunc(aP,aV);
}

template <class Type> const Type * cDataIm2D<Type>::GetLine(int aY)  const
{
   AssertYInside(aY);
   return mRawData2D[aY];
}
template <class Type> Type * cDataIm2D<Type>::GetLine(int aY) 
{
   AssertYInside(aY);
   return mRawData2D[aY];
}

template <class Type>  void cDataIm2D<Type>::ToFile(const std::string & aName) const
{
    cDataFileIm2D aDFI = cDataFileIm2D::Create(aName,tElemNumTrait<Type>::TyNum(),Sz(),1);
    Write(aDFI,P0());
}

template <class Type>  void cDataIm2D<Type>::ClipToFile(const std::string & aName,const cRect2& aBox) const
{
    cDataFileIm2D aDFI = cDataFileIm2D::Create(aName,tElemNumTrait<Type>::TyNum(),aBox.Sz(),1);
    Write(aDFI,-aBox.P0(),1.0,aBox);
}






template <class Type>  void cDataIm2D<Type>::ToFile(const std::string & aName,const tIm &aIG,const tIm &aIB) const
{
    cDataFileIm2D aDFI = cDataFileIm2D::Create(aName,tElemNumTrait<Type>::TyNum(),Sz(),3);
    Write(aDFI,aIG,aIB,P0());
}


/* ========================== */
/*          cIm2D         */
/* ========================== */

template <class Type>  cIm2D<Type>::cIm2D(const cPt2di & aP0,const cPt2di & aP1,Type * aRawDataLin,eModeInitImage aModeInit) :
   mSPtr(new cDataIm2D<Type>(aP0,aP1,aRawDataLin,aModeInit)),
   mPIm (mSPtr.get())
{
}

template <class Type>  cIm2D<Type>::cIm2D(const cPt2di & aSz,Type * aRawDataLin,eModeInitImage aModeInit) :
   cIm2D<Type> (cPt2di(0,0),aSz,aRawDataLin,aModeInit)
{
}


template <class Type>  cIm2D<Type>::cIm2D(const cBox2di & aBox,const cDataFileIm2D & aDataF) :
   cIm2D<Type> (aBox.Sz())
{
    Read(aDataF,aBox.P0());
}


template <class Type>  cIm2D<Type> cIm2D<Type>::FromFile(const std::string & aName)
{
   cDataFileIm2D  aFileIm = cDataFileIm2D::Create(aName,true);
   cIm2D<Type> aRes(aFileIm.Sz());
   aRes.Read(aFileIm,cPt2di(0,0));

   return aRes;
}

template <class Type>  cIm2D<Type> cIm2D<Type>::FromFile(const std::string & aName,const cBox2di & aBox)
{
   cDataFileIm2D  aFileIm = cDataFileIm2D::Create(aName,true);
   cIm2D<Type> aRes(aBox.Sz());
   aRes.Read(aFileIm,aBox.P0());

   return aRes;
}


template <class Type>  cIm2D<Type>  cIm2D<Type>::Dup() const
{
   cIm2D<Type> aRes(DIm().P0(),DIm().P1());
   DIm().DupIn(aRes.DIm());
   return aRes;
}


template <class Type>  cIm2D<Type>  cIm2D<Type>::GaussFilter(double aStdDev,int aNbIter) const
{
    cIm2D<typename tElemNumTrait<Type>::tFloatAssoc> aImFloat(DIm().P0(),DIm().P1());
    CopyIn(aImFloat.DIm(),DIm());
    ExpFilterOfStdDev(aImFloat.DIm(),aNbIter,aStdDev);

    cIm2D<Type> aRes(DIm().P0(),DIm().P1()); //  (DIm().P0(),DIm.P1());
    CopyIn(aRes.DIm(),aImFloat.DIm());

    return aRes;
}

template <class Type>  cPt2di  cIm2D<Type>::SzDecimate(int aFact) const
{
   return mPIm->Sz()/aFact;
}

template <class Type>  cIm2D<Type>  cIm2D<Type>::Decimate(int aFact) const
{

   cIm2D<Type> aRes(SzDecimate(aFact));
   aRes.DecimateInThis(aFact,*this);
   return aRes;
}

template <class Type>  void  cIm2D<Type>::DecimateInThis(int aFact,const cIm2D<Type> & aI) 
{
   MMVII_INTERNAL_ASSERT_strong(aI.DIm().P0()==cPt2di(0,0),"Decimate require (0,0) origin");
   MMVII_INTERNAL_ASSERT_strong(DIm().P0()==cPt2di(0,0),"Decimate require (0,0) origin");
   MMVII_INTERNAL_ASSERT_strong(DIm().Sz()==aI.SzDecimate(aFact),"Incoherent size in DecimateInThis");
   const cDataIm2D<Type> & aDIn = aI.DIm();

   for (const auto & aP : DIm())
      mPIm->SetV(aP,aDIn.GetV(aP*aFact));
}


template <class Type>  cIm2D<Type>  cIm2D<Type>::GaussDeZoom(int aFact, int aNbIterExp,double dilate) const
{
    double aS0 = DefStdDevImWellSample;
    double aSTarg = DefStdDevImWellSample * aFact;

    // double aSig = sqrt(Square(aSTarg)-Square(aS0)) *dilate;
    double aSig = DifSigm(aSTarg,aS0) *dilate;

    return GaussFilter(aSig,aNbIterExp).Decimate(aFact);
}

template <class Type>  cIm2D<Type>  cIm2D<Type>::Transpose() const
{
    cIm2D<Type> aTr(Transp(mPIm->P0()),Transp(mPIm->P1()));

    for (const auto & aP : (*mPIm))
       aTr.mPIm->SetV(Transp(aP),mPIm->GetV(aP));

    return aTr;
}

/* *********************************************************** */
/*                                                             */
/*            cAppliParseBoxIm<TypeEl>                         */
/*                                                             */
/* *********************************************************** */

template<class TypeEl>  cAppliParseBoxIm<TypeEl>::cAppliParseBoxIm
                        (
			      cMMVII_Appli & anAppli,
                              bool IsGray,
			      const cPt2di & aSzTiles,
			      const cPt2di & aSzOverlap
                        ) :
    mBoxTest  (cBox2di::Empty()),      // Fake Init, no def constructor
    mParseBox (nullptr),               // No inside parsing
    mDFI2d    (cDataFileIm2D::Empty()),   // Fake Init, no def constructor
    mIsGray   (IsGray),
    mAppli    (anAppli),
    mSzTiles  (aSzTiles),
    mSzOverlap(aSzOverlap),
    mIm       (cPt2di(1,1))
{
}

template<class TypeEl> void  cAppliParseBoxIm<TypeEl>::APBI_ExecAll()
{
     mDFI2d = cDataFileIm2D::Create(mNameIm,mIsGray);
     if (APBI_TestMode())
     {
         LoadI(CurBoxIn());
	 mAppli.ExeOnParsedBox();
         return;
     }
     AssertNotInParsing();
     cParseBoxInOut<2> aPBIO =  cParseBoxInOut<2>::CreateFromSize(mDFI2d,mSzTiles);
     mParseBox = & aPBIO;

     for (const auto & aPixI : aPBIO.BoxIndex())
     {
         mCurPixIndex = aPixI;
         LoadI(CurBoxIn());
	 mAppli.ExeOnParsedBox();
     }
     mParseBox = nullptr ;   // No longer inside parsing
}

template<class TypeEl> const std::string & cAppliParseBoxIm<TypeEl>::APBI_NameIm() const
{
  return mNameIm;
}

template<class TypeEl> bool  cAppliParseBoxIm<TypeEl>::InsideParsing() const
{
   return mParseBox != nullptr;
}
template<class TypeEl> void  cAppliParseBoxIm<TypeEl>::AssertInParsing() const
{
   MMVII_INTERNAL_ASSERT_strong(InsideParsing(),"cAppliParseBoxIm expected parsing state");
}
template<class TypeEl> void  cAppliParseBoxIm<TypeEl>::AssertNotInParsing() const
{
   MMVII_INTERNAL_ASSERT_strong(!InsideParsing(),"cAppliParseBoxIm expected not parsing state");
}

template<class TypeEl> cBox2di  cAppliParseBoxIm<TypeEl>::CurBoxIn() const
{
    MMVII_INTERNAL_ASSERT_strong(InsideParsing() ^ APBI_TestMode(),"cAppliParseBoxIm, must have InsideParsing() ^ TestMode");
    if (InsideParsing())
        return mParseBox->BoxIn(mCurPixIndex,mSzOverlap);
    else
        return mBoxTest;
}
template<class TypeEl> cBox2di  cAppliParseBoxIm<TypeEl>::CurBoxOut() const
{
    AssertInParsing();
    return mParseBox->BoxOut(mCurPixIndex);
}
template<class TypeEl> cBox2di  cAppliParseBoxIm<TypeEl>::CurBoxOutLoc() const
{
    AssertInParsing();
    return mParseBox->BoxOutLoc(mCurPixIndex,mSzOverlap);
}



template<class TypeEl>  cAppliParseBoxIm<TypeEl>::~cAppliParseBoxIm()
{
}
template<class TypeEl> cCollecSpecArg2007 & cAppliParseBoxIm<TypeEl>::APBI_ArgObl(cCollecSpecArg2007 & anArgObl)
{
   return
        anArgObl
           <<   Arg2007(mNameIm,"Name of input file",{{eTA2007::MPatFile,"0"},eTA2007::FileImage})
   ;
}

template<class TypeEl> cCollecSpecArg2007 & cAppliParseBoxIm<TypeEl>::APBI_ArgOpt(cCollecSpecArg2007 & anArgOpt)
{
    return anArgOpt
              << AOpt2007(mBoxTest,  "TestBox","Box for testing before runing all",{eTA2007::Tuning})
              << AOpt2007(mSzTiles,  "SzTiles","Size of tiles to parse big file",{eTA2007::HDV})
              << AOpt2007(mSzOverlap,"SzOverL","Size of overlap between tiles",{eTA2007::HDV})
    ;
}

template<class TypeEl>  bool cAppliParseBoxIm<TypeEl>::APBI_TestMode() const
{
  return IsInit(&mBoxTest);
}
template<class TypeEl> typename cAppliParseBoxIm<TypeEl>::tDataIm&  cAppliParseBoxIm<TypeEl>::LoadI(const cBox2di & aBox)
{
   mDFI2d.AssertNotEmpty();
   APBI_DIm().Resize(aBox.Sz());
   APBI_DIm().Read(mDFI2d,aBox.P0());

   return APBI_DIm();
}
template<class TypeEl> typename cAppliParseBoxIm<TypeEl>::tDataIm&  cAppliParseBoxIm<TypeEl>::APBI_DIm()
{
   return mIm.DIm();
}

/*  *********************************************************** */
/*             INSTANTIATION                                    */
/*             INSTANTIATION                                    */
/*             INSTANTIATION                                    */
/*  *********************************************************** */

template  class cAppliParseBoxIm<tREAL4>;


#define INSTANTIATE_IM2D(Type)\
template  class cIm2D<Type>;\
template  class cDataIm2D<Type>;

INSTANTIATE_IM2D(tINT1)
INSTANTIATE_IM2D(tINT2)
INSTANTIATE_IM2D(tINT4)

INSTANTIATE_IM2D(tU_INT1)
INSTANTIATE_IM2D(tU_INT2)
INSTANTIATE_IM2D(tU_INT4)


INSTANTIATE_IM2D(tREAL4)
INSTANTIATE_IM2D(tREAL8)
INSTANTIATE_IM2D(tREAL16)


};
