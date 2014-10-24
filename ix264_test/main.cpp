#include "ix264.h"
#include "itrbase.h"
#include "itrvision.h"
#include "types.h"
#include <stdio.h>
//压缩后的图像数据指针
const void *imgCompressData;

int main()
{

    Picture pic;
    itrx264::ix264 ix264obj;
    S32 width=640;
    S32 height=480;
    S32 _size=width*height;
    U8 Y[_size];
    U8 U[_size/4];
    U8 V[_size/4];
    S32 imgLength=0;
    U8 imgcomped[_size*3];
    FILE* fp;
    fp=fopen("bin/outpgm11.ppm","+r");
    if(fp==NULL)
    {
    	printf("fail to open Picture!\n");
    	exit(0);
    }
    fscanf(fp, "P5\n%d %d 255\n",&width,&height);
    _size=width*height;
    fread(Y,1,_size,fp);
    fread(U,1,_size/4,fp);
    fread(V,1,_size/4,fp);
    pic.data[0]=Y;
    pic.data[1]=U;
    pic.data[2]=V;

    //void *encoder =
     ix264obj.vc_open(width, height, 30);
//    if (!encoder)
//    {
//        fprintf(stderr, "ERR: can't open x264 encoder\n");
//        exit(-1);
//    }
    int rc = ix264obj.vc_compress(pic.data, pic.stride,&imgCompressData , & imgLength);
    if(rc>0)
    {
    	printf("compress succeed!\n");
    }
    ix264obj.vc_close();
    fclose(fp);
    return 0;
}
