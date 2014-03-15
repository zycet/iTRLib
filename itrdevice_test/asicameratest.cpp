#include "asicameratest.h"
itr_device::AsiCamera image_aquaire;

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
    const S32 height=320;
    const S32 weight=240;
    U8 Raw[height*weight];
    //Raw=new U8[weight*height]();

//    image_aquaire.RegCallBack(&image_do);

    image_aquaire.Open(0,weight,height,0);

    itr_device::ICamera::AquairePara AqPara;

    AqPara.AquaireFreq=60;
    AqPara.Exposure=30*1000;
    AqPara.Gain=1;  ///
    //AqPara.Format=RawMono8;
    image_aquaire.SetPara( AqPara);

    itr_device::ICamera::AquairePara* ExInfo;
    char head[40];
    char filename[10];
    sprintf(head,"P5\n%d %d\n255\n",weight,height);
    int i=0;
    while(image_aquaire.FetchFrame(Raw,weight*height,ExInfo))
    {
        sprintf(filename,"%d.pgm",i);
        FILE* fout=fopen(filename,"w");
        fprintf(fout,head);
        for(int j=0;j<weight*height;++j)
            fprintf(fout,"%c",Raw[j]);
        fclose(fout);
        ++i;
    }

}
