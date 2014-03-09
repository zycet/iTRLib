#include "asicameratest.h"
#define Channel 1
#define IMG_RAW8
void image_do(itr_device::AsiCamera& AsiCameraObj,U8* Raw,S32 Length,void* ExInfo)
{

    F32 *data;
    data=new F32[Length]();
    for(S32 i=0; i<Length; i++)
        data[i]=(F32)Raw[i];
    itr_math::Matrix Img(AsiCameraObj.GetWidth(),AsiCameraObj.GetHeight(),data);
    //itr_vision::FormatConverter convert;
    //convert.Raw2Matrix(Raw,Length,IMG_RAW8,Channel,Img);
    itr_vision::IOpnm::WritePGMFile("grayCAMERA.pgm", Img);
    delete[] data;
}
void asicamera_test()
{
    //itr_device::AsiCamera::ReceiveFrameCallBack call=&image_do;

    itr_device::AsiCamera image_aquaire;

}
