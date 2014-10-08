#include "V4Ltest.h"
#include "itrbase.h"
#include "itrdevice.h"
#include "itrvision.h"
void F4Ltest()
{
    itr_device::v4linux V4lcamera;
    U32 ID=1;
    S32 Width=640;
    S32 Height=480;
    S32 BufferNum=2;
    V4lcamera.Open( ID, Width, Height, BufferNum);
    U8 *data;
    data=new U8[Width*Height]();
    S32 ExInfo;
    int i=0;
    char filename[]="img001.pgm";
    F32 *data_mat;
    data_mat=new F32[Width*Height]();
    for(S32 i=0; i<Width*Height; i++)
    {
        data_mat[i]=(F32)data[i];
    }
    while(1)
    {
        V4lcamera.FetchFrame(data,Width*Height,& ExInfo);
        for(S32 i=0; i<Width*Height; i++)
        {
            data_mat[i]=(F32)data[i];
        }
        itr_math::Matrix img(Height,Width,data_mat);
        sprintf(filename,"img%03d.pgm",i++);
        itr_vision::IOpnm::WritePGMFile(filename,img);
        getchar();
    }

//    itr_math::Matrix Pic_Mat;
//    F32 *data_mat;
//    data_mat=new F32[Width*Height]();
//    for(S32 i=0;i<Width*Height; i++)
//    {
//        data_mat[i]=(F32)data[i];
//    }
//    Pic_Mat.Init(Height,Width,data_mat);
    printf("\nResult is :\n");
    FILE *fout=fopen("f.pgm","w");
    fprintf(fout,"P5\n640 480\n255\n");
    for(S32 i=0; i<Height; i++)
    {
        for(S32 j=0; j<Width; j++)
        {
            fprintf(fout,"%c",data[i*Width+j]);
        }
        printf("\n");
    }

}
