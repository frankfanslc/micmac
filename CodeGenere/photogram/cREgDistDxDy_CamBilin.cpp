// File Automatically generated by eLiSe
#include "StdAfx.h"
#include "cREgDistDxDy_CamBilin.h"


cREgDistDxDy_CamBilin::cREgDistDxDy_CamBilin():
    cElCompiledFonc(2)
{
   AddIntRef (cIncIntervale("Intr",0,11));
   Close(false);
}



void cREgDistDxDy_CamBilin::ComputeVal()
{
   double tmp0_ = mLocPts1_x - mLocRegDistxy1_x;
   double tmp1_ = mLocPts1_x - mLocPts0_x;
   double tmp2_ = (tmp0_) / (tmp1_);
   double tmp3_ = mLocPts2_y - mLocRegDistxy1_y;
   double tmp4_ = mLocPts2_y - mLocPts0_y;
   double tmp5_ = (tmp3_) / (tmp4_);
   double tmp6_ = 1 - tmp2_;
   double tmp7_ = 1 - tmp5_;
   double tmp8_ = mCompCoord[3];
   double tmp9_ = mCompCoord[5];
   double tmp10_ = mLocPts1_x - mLocRegDistxy2_x;
   double tmp11_ = (tmp10_) / (tmp1_);
   double tmp12_ = mLocPts2_y - mLocRegDistxy2_y;
   double tmp13_ = (tmp12_) / (tmp4_);
   double tmp14_ = mCompCoord[7];
   double tmp15_ = mCompCoord[9];
   double tmp16_ = 1 - tmp11_;
   double tmp17_ = 1 - tmp13_;
   double tmp18_ = mLocPts1_x - mLocRegDistxy3_x;
   double tmp19_ = (tmp18_) / (tmp1_);
   double tmp20_ = mLocPts2_y - mLocRegDistxy3_y;
   double tmp21_ = (tmp20_) / (tmp4_);
   double tmp22_ = 1 - tmp19_;
   double tmp23_ = 1 - tmp21_;
   double tmp24_ = mLocPts1_x - mLocRegDistxy4_x;
   double tmp25_ = (tmp24_) / (tmp1_);
   double tmp26_ = mLocPts2_y - mLocRegDistxy4_y;
   double tmp27_ = (tmp26_) / (tmp4_);
   double tmp28_ = 1 - tmp25_;
   double tmp29_ = 1 - tmp27_;
   double tmp30_ = (tmp2_) * (tmp5_);
   double tmp31_ = (tmp6_) * (tmp5_);
   double tmp32_ = (tmp2_) * (tmp7_);
   double tmp33_ = (tmp6_) * (tmp7_);
   double tmp34_ = mCompCoord[4];
   double tmp35_ = (tmp11_) * (tmp13_);
   double tmp36_ = mCompCoord[6];
   double tmp37_ = (tmp16_) * (tmp13_);
   double tmp38_ = mCompCoord[8];
   double tmp39_ = (tmp11_) * (tmp17_);
   double tmp40_ = mCompCoord[10];
   double tmp41_ = (tmp16_) * (tmp17_);
   double tmp42_ = (tmp19_) * (tmp21_);
   double tmp43_ = (tmp22_) * (tmp21_);
   double tmp44_ = (tmp19_) * (tmp23_);
   double tmp45_ = (tmp22_) * (tmp23_);
   double tmp46_ = (tmp25_) * (tmp27_);
   double tmp47_ = (tmp28_) * (tmp27_);
   double tmp48_ = (tmp25_) * (tmp29_);
   double tmp49_ = (tmp28_) * (tmp29_);

  mVal[0] = (tmp8_ * tmp30_ + tmp9_ * tmp31_ + tmp14_ * tmp32_ + tmp15_ * tmp33_ + tmp8_ * tmp35_ + tmp9_ * tmp37_ + tmp14_ * tmp39_ + tmp15_ * tmp41_) - (tmp8_ * tmp42_ + tmp9_ * tmp43_ + tmp14_ * tmp44_ + tmp15_ * tmp45_ + tmp8_ * tmp46_ + tmp9_ * tmp47_ + tmp14_ * tmp48_ + tmp15_ * tmp49_);

  mVal[1] = (tmp34_ * tmp30_ + tmp36_ * tmp31_ + tmp38_ * tmp32_ + tmp40_ * tmp33_ + tmp34_ * tmp35_ + tmp36_ * tmp37_ + tmp38_ * tmp39_ + tmp40_ * tmp41_) - (tmp34_ * tmp42_ + tmp36_ * tmp43_ + tmp38_ * tmp44_ + tmp40_ * tmp45_ + tmp34_ * tmp46_ + tmp36_ * tmp47_ + tmp38_ * tmp48_ + tmp40_ * tmp49_);

}


void cREgDistDxDy_CamBilin::ComputeValDeriv()
{
   double tmp0_ = mLocPts1_x - mLocRegDistxy1_x;
   double tmp1_ = mLocPts1_x - mLocPts0_x;
   double tmp2_ = (tmp0_) / (tmp1_);
   double tmp3_ = mLocPts2_y - mLocRegDistxy1_y;
   double tmp4_ = mLocPts2_y - mLocPts0_y;
   double tmp5_ = (tmp3_) / (tmp4_);
   double tmp6_ = 1 - tmp2_;
   double tmp7_ = 1 - tmp5_;
   double tmp8_ = mCompCoord[3];
   double tmp9_ = mCompCoord[5];
   double tmp10_ = mLocPts1_x - mLocRegDistxy2_x;
   double tmp11_ = (tmp10_) / (tmp1_);
   double tmp12_ = mLocPts2_y - mLocRegDistxy2_y;
   double tmp13_ = (tmp12_) / (tmp4_);
   double tmp14_ = mCompCoord[7];
   double tmp15_ = mCompCoord[9];
   double tmp16_ = 1 - tmp11_;
   double tmp17_ = 1 - tmp13_;
   double tmp18_ = mLocPts1_x - mLocRegDistxy3_x;
   double tmp19_ = (tmp18_) / (tmp1_);
   double tmp20_ = mLocPts2_y - mLocRegDistxy3_y;
   double tmp21_ = (tmp20_) / (tmp4_);
   double tmp22_ = 1 - tmp19_;
   double tmp23_ = 1 - tmp21_;
   double tmp24_ = mLocPts1_x - mLocRegDistxy4_x;
   double tmp25_ = (tmp24_) / (tmp1_);
   double tmp26_ = mLocPts2_y - mLocRegDistxy4_y;
   double tmp27_ = (tmp26_) / (tmp4_);
   double tmp28_ = 1 - tmp25_;
   double tmp29_ = 1 - tmp27_;
   double tmp30_ = (tmp2_) * (tmp5_);
   double tmp31_ = (tmp11_) * (tmp13_);
   double tmp32_ = (tmp19_) * (tmp21_);
   double tmp33_ = (tmp25_) * (tmp27_);
   double tmp34_ = (tmp6_) * (tmp5_);
   double tmp35_ = (tmp16_) * (tmp13_);
   double tmp36_ = (tmp22_) * (tmp21_);
   double tmp37_ = (tmp28_) * (tmp27_);
   double tmp38_ = (tmp2_) * (tmp7_);
   double tmp39_ = (tmp11_) * (tmp17_);
   double tmp40_ = (tmp19_) * (tmp23_);
   double tmp41_ = (tmp25_) * (tmp29_);
   double tmp42_ = (tmp6_) * (tmp7_);
   double tmp43_ = (tmp16_) * (tmp17_);
   double tmp44_ = (tmp22_) * (tmp23_);
   double tmp45_ = (tmp28_) * (tmp29_);
   double tmp46_ = mCompCoord[4];
   double tmp47_ = mCompCoord[6];
   double tmp48_ = mCompCoord[8];
   double tmp49_ = mCompCoord[10];
   double tmp50_ = tmp30_ + tmp31_;
   double tmp51_ = tmp32_ + tmp33_;
   double tmp52_ = (tmp50_) - (tmp51_);
   double tmp53_ = tmp34_ + tmp35_;
   double tmp54_ = tmp36_ + tmp37_;
   double tmp55_ = (tmp53_) - (tmp54_);
   double tmp56_ = tmp38_ + tmp39_;
   double tmp57_ = tmp40_ + tmp41_;
   double tmp58_ = (tmp56_) - (tmp57_);
   double tmp59_ = tmp42_ + tmp43_;
   double tmp60_ = tmp44_ + tmp45_;
   double tmp61_ = (tmp59_) - (tmp60_);

  mVal[0] = (tmp8_ * tmp30_ + tmp9_ * tmp34_ + tmp14_ * tmp38_ + tmp15_ * tmp42_ + tmp8_ * tmp31_ + tmp9_ * tmp35_ + tmp14_ * tmp39_ + tmp15_ * tmp43_) - (tmp8_ * tmp32_ + tmp9_ * tmp36_ + tmp14_ * tmp40_ + tmp15_ * tmp44_ + tmp8_ * tmp33_ + tmp9_ * tmp37_ + tmp14_ * tmp41_ + tmp15_ * tmp45_);

  mCompDer[0][0] = 0;
  mCompDer[0][1] = 0;
  mCompDer[0][2] = 0;
  mCompDer[0][3] = tmp52_;
  mCompDer[0][4] = 0;
  mCompDer[0][5] = tmp55_;
  mCompDer[0][6] = 0;
  mCompDer[0][7] = tmp58_;
  mCompDer[0][8] = 0;
  mCompDer[0][9] = tmp61_;
  mCompDer[0][10] = 0;
  mVal[1] = (tmp46_ * tmp30_ + tmp47_ * tmp34_ + tmp48_ * tmp38_ + tmp49_ * tmp42_ + tmp46_ * tmp31_ + tmp47_ * tmp35_ + tmp48_ * tmp39_ + tmp49_ * tmp43_) - (tmp46_ * tmp32_ + tmp47_ * tmp36_ + tmp48_ * tmp40_ + tmp49_ * tmp44_ + tmp46_ * tmp33_ + tmp47_ * tmp37_ + tmp48_ * tmp41_ + tmp49_ * tmp45_);

  mCompDer[1][0] = 0;
  mCompDer[1][1] = 0;
  mCompDer[1][2] = 0;
  mCompDer[1][3] = 0;
  mCompDer[1][4] = tmp52_;
  mCompDer[1][5] = 0;
  mCompDer[1][6] = tmp55_;
  mCompDer[1][7] = 0;
  mCompDer[1][8] = tmp58_;
  mCompDer[1][9] = 0;
  mCompDer[1][10] = tmp61_;
}


void cREgDistDxDy_CamBilin::ComputeValDerivHessian()
{
  ELISE_ASSERT(false,"Foncteur cREgDistDxDy_CamBilin Has no Der Sec");
}

void cREgDistDxDy_CamBilin::SetPts0_x(double aVal){ mLocPts0_x = aVal;}
void cREgDistDxDy_CamBilin::SetPts0_y(double aVal){ mLocPts0_y = aVal;}
void cREgDistDxDy_CamBilin::SetPts1_x(double aVal){ mLocPts1_x = aVal;}
void cREgDistDxDy_CamBilin::SetPts2_y(double aVal){ mLocPts2_y = aVal;}
void cREgDistDxDy_CamBilin::SetRegDistxy1_x(double aVal){ mLocRegDistxy1_x = aVal;}
void cREgDistDxDy_CamBilin::SetRegDistxy1_y(double aVal){ mLocRegDistxy1_y = aVal;}
void cREgDistDxDy_CamBilin::SetRegDistxy2_x(double aVal){ mLocRegDistxy2_x = aVal;}
void cREgDistDxDy_CamBilin::SetRegDistxy2_y(double aVal){ mLocRegDistxy2_y = aVal;}
void cREgDistDxDy_CamBilin::SetRegDistxy3_x(double aVal){ mLocRegDistxy3_x = aVal;}
void cREgDistDxDy_CamBilin::SetRegDistxy3_y(double aVal){ mLocRegDistxy3_y = aVal;}
void cREgDistDxDy_CamBilin::SetRegDistxy4_x(double aVal){ mLocRegDistxy4_x = aVal;}
void cREgDistDxDy_CamBilin::SetRegDistxy4_y(double aVal){ mLocRegDistxy4_y = aVal;}



double * cREgDistDxDy_CamBilin::AdrVarLocFromString(const std::string & aName)
{
   if (aName == "Pts0_x") return & mLocPts0_x;
   if (aName == "Pts0_y") return & mLocPts0_y;
   if (aName == "Pts1_x") return & mLocPts1_x;
   if (aName == "Pts2_y") return & mLocPts2_y;
   if (aName == "RegDistxy1_x") return & mLocRegDistxy1_x;
   if (aName == "RegDistxy1_y") return & mLocRegDistxy1_y;
   if (aName == "RegDistxy2_x") return & mLocRegDistxy2_x;
   if (aName == "RegDistxy2_y") return & mLocRegDistxy2_y;
   if (aName == "RegDistxy3_x") return & mLocRegDistxy3_x;
   if (aName == "RegDistxy3_y") return & mLocRegDistxy3_y;
   if (aName == "RegDistxy4_x") return & mLocRegDistxy4_x;
   if (aName == "RegDistxy4_y") return & mLocRegDistxy4_y;
   return 0;
}


cElCompiledFonc::cAutoAddEntry cREgDistDxDy_CamBilin::mTheAuto("cREgDistDxDy_CamBilin",cREgDistDxDy_CamBilin::Alloc);


cElCompiledFonc *  cREgDistDxDy_CamBilin::Alloc()
{  return new cREgDistDxDy_CamBilin();
}


