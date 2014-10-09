#include "itrvision.h"
#include"itrdevice.h"
#include"v4linux.h"
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
    cam.Init( 0);
    cam.Open(0,width,height,2);
    for(S32 i=0; i<20; i++)
    {
        cam.FetchFrame(raw,3*width*height,exinfo);
        sprintf(filename,"outrgb%3d.ppm",i);
        fp=fopen(filename,"w+");
        if(fp==NULL)
        {
            printf("fail to open file%d\n",i);
            exit(-1);
        }
        fprintf(fp, "P6\n%d %d 255\n",width,height);
        fwrite(raw,3*width*height, 1, fp);
        fclose(fp);
    }
    cam.Close();
    itr_device::v4linux cam2;
    //yuv
    cam2.Init(1);
    cam2.Open(0,width,height,2);
    for(S32 i=0; i<20; i++)
    {
        cam2.FetchFrame(raw,width*height,exinfo);
        sprintf(filename,"outpgm%3d.pgm",i);
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
    cam2.Close();
}
