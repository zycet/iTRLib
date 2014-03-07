#ifndef STDCAMERATEST_H
#define STDCAMERATEST_H

//#include "stdimageaquaire.h"
#include "itrdevice.h"
void stdcamera_test();
void image_do(itr_device::StdImageAquaire& StdImageAquaireObj,U8* Raw,S32 Length,void* ExInfo);
#endif // STDCAMERATEST_H
