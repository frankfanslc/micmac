// File Automatically generated by eLiSe
#include "StdAfx.h"


class cGen2DBundleAttach_Deg1: public cElCompiledFonc
{
   public :

      cGen2DBundleAttach_Deg1();
      void ComputeVal();
      void ComputeValDeriv();
      void ComputeValDerivHessian();
      double * AdrVarLocFromString(const std::string &);
      void SetAmplFixV(double);
      void SetCentrFixV_x(double);
      void SetCentrFixV_y(double);
      void SetFixedV_x(double);
      void SetFixedV_y(double);
      void SetPFixV_x(double);
      void SetPFixV_y(double);


      static cAutoAddEntry  mTheAuto;
      static cElCompiledFonc *  Alloc();
   private :

      double mLocAmplFixV;
      double mLocCentrFixV_x;
      double mLocCentrFixV_y;
      double mLocFixedV_x;
      double mLocFixedV_y;
      double mLocPFixV_x;
      double mLocPFixV_y;
};
