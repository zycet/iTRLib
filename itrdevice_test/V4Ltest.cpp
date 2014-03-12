#include "V4Ltest.h"
#include "itrbase.h"
#include "itrdevice.h"
void F4Ltest()
{
    itr_device::v4linux V4lcamera;
    U32 ID=0;
    S32 Width=640;
    S32 Height=480;
    S32 BufferNum=0;
    V4lcamera.Open( ID, Width, Height, BufferNum);
    U8*data;
    data=new U8[Width*Height]();
    S32 ExInfo;
    V4lcamera.FetchFrame(data,Width*Height,& ExInfo);
    itr_math::Matrix Pic_Mat;
    F32 *data_mat;
    data_mat=new F32[Width*Height]();
    for(S32 i=0;i<Width*Height; i++)
    {
        data_mat[i]=(F32)data[i];
    }
    Pic_Mat.Init(Height,Width,data_mat);

}
