#include "camerastereocalc.h"

namespace itr_vision
{

CameraStereoCalc::CameraStereoCalc()
{
    //(CalcExInfo.Equ).Init(3);//ctor
    this->InstallAngle=0;
}

CameraStereoCalc::~CameraStereoCalc()
{
    //dtor
}
void CameraStereoCalc::Init(CameraInterCalc* CameraInterCalc0,CameraInterCalc* CameraInterCalc1,F32 Distance)
{
    this->Distance=Distance;
    this->CameraInterCalc0=CameraInterCalc0;
    this->CameraInterCalc1=CameraInterCalc1;
}


//this->CalcExInfo CameraStereoCalc::CalcExInfo GetCalcExInfo()
//{
//
//}

}
