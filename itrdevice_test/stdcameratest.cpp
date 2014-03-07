#include "stdcameratest.h"

void image_do(itr_device::StdImageAquaire& StdImageAquaireObj,U8* Raw,S32 Length,void* ExInfo)
{

}
void stdcamera_test()
{
    itr_device::StdImageAquaire::ReceiveFrameCallBack call=image_do;
    itr_device::StdImageAquaire image_aquaire;
}
