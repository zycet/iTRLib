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
/*
void cvText(IplImage* img, const char* text, int x, int y)
{
	CvFont font;

	double hscale = 0.6;
	double vscale = 0.6;
	int linewidth = 2;
	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC,hscale,vscale,0,linewidth);

	CvScalar textColor =cvScalar(0,255,255);
	CvPoint textPos =cvPoint(x, y);

	cvPutText(img, text, textPos, &font,textColor);
}
*/
unsigned long GetTickCount()
{
    //struct timespec ts;
    //clock_gettime(CLOCK_MONOTONIC,&ts);
    //return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
    return 0;
}

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
    int i;
    char c;
    bool bresult;
    unsigned char *pdata;

    int time1,time2;
    int count=0;

    char buf[128]= {0};

    int CamNum=0;

    ///long exposure, exp_min, exp_max, exp_step, exp_flag, exp_default;
    //long gain, gain_min, gain_max,gain_step, gain_flag, gain_default;

    //	IplImage *pRgb;


    int numDevices = getNumberOfConnectedCameras();
    if(numDevices <= 0)
    {
        printf("no camera connected, press any key to exit\n");
        getchar();
        return -1;
    }
    else
        printf("attached cameras:\n");

    for(i = 0; i < numDevices; i++)
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
    width=400;
	height=400;
	initCamera(); //this must be called before camera operation. and it only need init once
	printf("sensor temperature:%02f\n", getSensorTemp());

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
    pdata = new unsigned char[getMaxWidth()*getMaxHeight()];
    //printf("\nPlease input the width and height with one space, ie. 640 480\n");
    //scanf("%d %d", &width, &height);
    /*
    while(!setImageFormat(width, height, 1, IMG_RAW8))
    {
        printf("Set format error, please check the width and height\n ASI120's data size(width*height) must be integer multiple of 1024\n");
        printf("Please input the width and height again，ie. 640 480\n");
        scanf("%d %d", &width, &height);
    }
    */
    //printf("\nset image format success, start privew, press ESC to stop \n");
	//cvNamedWindow("video", 1);

	//pRgb=cvCreateImage(cvSize(getWidth(),getHeight()), IPL_DEPTH_8U, 1);
	printf("***************************\n");
    printf("*Set the value of control**\n");
    printf("***************************\n");
    setValue(CONTROL_GAIN,1,true);
    setValue(CONTROL_EXPOSURE, 33*1000, true); //auto exposure
    setValue(CONTROL_GAMMA,2,true);
    setValue(CONTROL_BRIGHTNESS,3,true);
    setValue(CONTROL_BANDWIDTHOVERLOAD,4,true);

    PrintCameraInfo(CamNum,controls);
    printf("*******************************\n");
    printf("********Get Image Data *********\n");
    printf("*******************************\n\n");

    itr_vision::FormatPPM fpObj();
    S16 pixel[1000*1000];
    startCapture(); //start privew
    //time1 = GetTickCount();
    int count2 = 0;
    getImageData(pdata,width*height,0);
    for(int i = 0;i< width*height;i++)
    {
        pixel[i] = pdata[i];
    }
    itr_vision::ImageGray gImage(width,height,pixel);
    char* filename = "picture";
    WritePPMFile(filename,gImage);
    printf("finish\n");

    /*
    while(1)
    {
        //getImageData((unsigned char*)pRgb->imageData, pRgb->imageSize, -1);
        getImageData(pdata,width*height , -1);
        count++;
        time2 = GetTickCount();
        if(time2-time1 > 1000 )
        {
            sprintf(buf, "fps:%d dropped frames:%lu",count, getDroppedFrames());
            printf("%s\n",buf);
            count = 0;
            time1=GetTickCount();
        }
        //cvText(pRgb, buf, 40,40 );

        //cvFlip(pRgb,NULL,1);//加上这句就水平翻转画面
    /*
        		char c=cvWaitKey(1);
        		switch(c)
        		{
        		case 27://按ESC退出
        			goto END;
        		}

        		cvShowImage("video", pRgb);
    */
    //}*
END:
    delete pdata;
    stopCapture();
    printf("over\n");
    return 1;
}






