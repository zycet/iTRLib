#ifndef STDCAMERATEST_H
#define STDCAMERATEST_H

//#include "stdimageaquaire.h"
#include "itrdevice.h"
void asicamera_test();
void image_do(itr_device::AsiCamera& AsiCameraObj,U8* Raw,S32 Length,void* ExInfo);
#endif // STDCAMERATEST_H
