#include "stdio.h"
//#include "highgui/highgui_c.h"
#include "ASICamera.h"
#include <sys/time.h>
#include <time.h>
#include "itrvision.h"
//#pragma comment(lib,"../OpenCV/lib/highgui.lib")
//#pragma comment(lib,"../OpenCV/lib/cxcore.lib")
//#pragma comment(lib,"../../lib/ASIcamera.lib")


#define  MAX_CONTROL 7
using namespace itr_vision;
//Get the Time
unsigned long GetTickCount()
{
    //struct timespec ts;
    //clock_gettime(CLOCK_MONOTONIC,&ts);
    //return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
    return 0;
}
//Write the img to a file
void WritePPMFile(char* filename, ImageGray& img)
{
    S32 length2 = img.GetWidth() * img.GetHeight()*3 + 20;
    U8* bufferWrite = new U8[length2];
    //Write Image
    itr_vision::FormatPPM FormatPPMObj;
    assert(FormatPPMObj.ToBinary(img, bufferWrite, length2)==itr_vision::IFormat::Success);
    //Write File
    FILE* file2 = fopen(filename, "wb+");
    assert(file2!=NULL);
    assert(fwrite(bufferWrite,1,length2,file2)==(U32)length2);
    fflush(file2);
    fclose(file2);
    delete[] bufferWrite;
}
//Display the camera's information
int PrintCameraInfo(int CamNum, char** controls)
{
    printf("%s information\n",getCameraModel(CamNum));
    printf("resolution:%dX%d\n", getMaxWidth(),getMaxHeight());
    bool *pbAuto = NULL;
    bool a = true;
    pbAuto = &a;
    for(int i = 0; i < MAX_CONTROL; i++)
    {
        if(isAvailable((Control_TYPE)i))
            printf("%s support:Yes  %s value: %d\n", controls[i], controls[i], getValue((Control_TYPE)i,pbAuto));
        else
            printf("%s support:No  %s value: %d\n", controls[i], controls[i], getValue((Control_TYPE)i,pbAuto));
    }
    printf("sensor temperature:%02f\n", getSensorTemp());
    return 0;
}

int  main()
{
    int width = getMaxWidth();
    int height = getMaxHeight();
    char* bayer[] = {"RG","BG","GR","GB"};
    char* controls[MAX_CONTROL] = {"Exposure", "Gain", "Gamma", "WB_R", "WB_B", "Brightness", "USB Traffic"};
    bool bresult;
    unsigned char *pdata;
    int CamNum = 0;
    int numDevices = getNumberOfConnectedCameras();
    if(numDevices <= 0)
    {
        printf("no camera connected, press any key to exit\n");
        getchar();
        return -1;
    }
    else
        printf("attached cameras:\n");

    for(int i = 0; i < numDevices; i++)
        printf("%d %s\n",i, getCameraModel(i));

    printf("\nselect one to privew\n");
    scanf("%d", &CamNum);

    bresult = openCamera(CamNum);
    if(!bresult)
    {
        printf("OpenCamera error,are you root?,press any key to exit\n");
        getchar();
        return -1;
    }
    //Init the camera
    width=400;
	height=400;
	initCamera(); //this must be called before camera operation. and it only need init once
	while(!setImageFormat(width, height, 1, IMG_RAW8))
	{
		printf("Set format error, please check the width and height\n ASI120's data size(width*height) must be integer multiple of 1024\n");
		printf("Please input the width and height again£¬ie. 640 480\n");
		scanf("%d %d", &width, &height);
	}
    printf("************************\n");
    printf("Camera Init Successfully\n");
    printf("************************\n");
    PrintCameraInfo(CamNum, controls);
    //pdata = new unsigned char[getMaxWidth()*getMaxHeight()];

	printf("***************************\n");
    printf("*Set the value of control**\n");
    printf("***************************\n");
    setValue(CONTROL_GAIN,1,true);
    setValue(CONTROL_EXPOSURE, 33*1000, true); //auto exposure
    //setValue(CONTROL_GAMMA,2,true);
    //setValue(CONTROL_BRIGHTNESS,3,true);
    //setValue(CONTROL_BANDWIDTHOVERLOAD,4,true);
    PrintCameraInfo(CamNum,controls);

    printf("*******************************\n");
    printf("********Get Image Data *********\n");
    printf("*******************************\n\n");

    S16 pixel[1000*1000];
    startCapture(); //start privew
    pdata = new unsigned char[width*height];
    getImageData(pdata,width*height,0);
    for(int i = 0;i< width*height;i++)
    {
        pixel[i] = pdata[i];
    }
    itr_vision::ImageGray gImage(width,height,pixel);
    char* filename = "picture";
    WritePPMFile(filename,gImage);
    printf("finish\n");

END:
    delete pdata;
    stopCapture();
    printf("over\n");
    return 1;
}






