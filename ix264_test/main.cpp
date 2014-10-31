#include "ix264.h"
#include "itrbase.h"
#include "itrvision.h"
#include "itrdevice.h"
#include <stdio.h>
#include "itrsystem.h"


int main()
{
    itr_device::v4linux camera;
    const int width=320;
    const int height=240;
    camera.Open(0,width,height,2);
    itrx264::ix264 compress;
    compress.Open(width,height,20);
    const int length=width*height;
    U8 img[length*2];
    U8 *data[4];
    S32 stride[4];
    const void *out;
    S32 len;
    char filename[20];
    for(int i=0; i<130; i++)
    {
        camera.FetchFrame(img,length*3/2,NULL);
        data[0]=img;
        data[1]=img+length;
        data[2]=img+length+length/4;
        data[3]=NULL;
        stride[0]=width;
        stride[1]=width/2;
        stride[2]=width/2;
        stride[3]=0;
        compress.Compress(data,stride,&out,&len);

        sprintf(filename,"data%d.x264",i);
        FILE *fp=fopen(filename,"w");
        fwrite((U8 *)out,len,1,fp);
        fclose(fp);

    }
    return 0;
}
