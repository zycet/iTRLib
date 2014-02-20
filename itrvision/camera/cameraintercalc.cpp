#include "cameraintercalc.h"
#include "itrbase.h"

using namespace itr_math;

namespace itr_vision
{

CameraInterCalc::CameraInterCalc()
{
    //ctor
    MatC2P.Init(3,4);
    MatP2C.Init(4,3);
    MatC2P.Set(0);
    MatP2C.Set(0);
    isMatC2PAvailable =false;
    isMatP2CAvailable =false;
}

CameraInterCalc::~CameraInterCalc()
{
    //dtor
}

CameraInterCalc::CameraInterCalc(const CameraInterCalc &other)
{
    //copy ctor
    this->MatC2P=other.MatC2P;
    this->MatP2C=other.MatC2P;
    this->isMatC2PAvailable=other.isMatC2PAvailable;
    this->isMatP2CAvailable=other.isMatP2CAvailable;
}

void CameraInterCalc::SetPara(F32 F,F32 dX,F32 dY,F32 u0,F32 v0)
{
    MatC2P(0,0)=F/dX;
    MatC2P(0,2)=u0;
    MatC2P(1,1)=F/dY;
    MatC2P(1,2)=v0;
    MatC2P(2,2)=1;
    isMatC2PAvailable =true;

    MatC2P.Inv(MatP2C);
    isMatP2CAvailable =true;
}
void CameraInterCalc::SetPara(F32 degX,F32 degY,F32 u0,F32 v0)
{
    Numerical NumericalObj;
    NumericalObj.Tan(degX,MatC2P(0,0));
    MatC2P(0,0)=u0/MatC2P(0,0);
    MatC2P(0,2)=u0;
    NumericalObj.Tan(degX,MatC2P(1,1));
    MatC2P(1,1)=v0/MatC2P(1,1);
    MatC2P(1,2)=v0;
    MatC2P(2,2)=1;
    isMatC2PAvailable =true;

    MatC2P.Inv(MatP2C);
    isMatP2CAvailable =true;
}

BOOL CameraInterCalc::CalcC2P(const Vector &CameraPoint,Vector &PixelPoint)
{
    if(isMatC2PAvailable)
    {
        PixelPoint =MatC2P*CameraPoint;
        PixelPoint[0]/=PixelPoint[2];
        PixelPoint[1]/=PixelPoint[2];
        PixelPoint[2]=1;
        return 1;
    }
    return 0;
}

BOOL CameraInterCalc::CalcP2C(const Vector &PixelPoint,F32 Z,Vector &CameraPoint)
{
    if(isMatP2CAvailable)
    {
        CameraPoint =MatP2C*PixelPoint;
        CameraPoint=CameraPoint*Z;
        return 1;
    }
    return 0;
}

}
