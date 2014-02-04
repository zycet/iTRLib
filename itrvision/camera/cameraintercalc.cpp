#include "cameraintercalc.h"
#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{

    CameraInterCalc::CameraInterCalc()
    {
        //ctor
    }

    CameraInterCalc::~CameraInterCalc()
    {
        //dtor
    }

    CameraInterCalc::CameraInterCalc(const CameraInterCalc &other)
    {
        //copy ctor
    }

    void CameraInterCalc::SetPara(F32 F,F32 dX,F32 dY,F32 u0,F32 v0)
    {

    }
    void CameraInterCalc::SetPara(F32 degX,F32 degY,F32 u0,F32 v0)
    {

    }

    BOOL CameraInterCalc::CalcC2P(const Vector &CameraPoint,Vector &PixelPoint)
    {

    }

    BOOL CameraInterCalc::CalcP2C(const Vector &PixelPoint,F32 Z,Vector &CameraPoint)
    {

    }

}
