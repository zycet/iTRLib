#include "itrvision.h"
#include"itrdevice.h"
#include"v4linux.h"
#define _id 0
#define INDEX 0
void v4ltestguan()
{
    FILE *fp;
    itr_device::v4linux cam;
    S32 width,height;
    width=640;
    height=480;
    U8* raw=new U8[3*width*height];
    void *exinfo;
    char filename[20];
    // RGB;
//    cam.Init(PIC_TYPE);
    cam.Open( _id,width,height,2);
  //  cam.SetTunnel(INDEX);
    for(S32 i=0; i<20; i++)
    {
        cam.FetchFrame(raw,width*height,exinfo);
        sprintf(filename,"outyuv%3d.pgm",i);
        fp=fopen(filename,"w+");
        if(fp==NULL)
        {
            printf("fail to open file%d\n",i);
            exit(-1);
        }
        fprintf(fp, "P5\n%d %d 255\n",width,height);
        fwrite(raw,width*height, 1, fp);
        fclose(fp);
    }
    cam.Close();
    itr_device::v4linux cam2;
    //yuv420
    cam2.Init(itr_device::v4linux::PIC_TYPE(1));
    cam2.Open( _id,width,height,2);
    //cam.SetTunnel(INDEX);
    for(S32 i=0; i<20; i++)
    {
        cam2.FetchFrame(raw,width*height*3,exinfo);
        sprintf(filename,"outrgb%3d.ppm",i);
        fp=fopen(filename,"w+");
        if(fp==NULL)
        {
            printf("fail to open file%d\n",i);
            exit(-1);
        }
        fprintf(fp, "P6\n%d %d 255\n",width,height);
        fwrite(raw,width*height*3, 1, fp);
        fclose(fp);
    }
    cam2.Close();
}
