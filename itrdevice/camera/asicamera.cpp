#include "asicamera.h"
#include "stdio.h"
#include <sys/time.h>
#include <time.h>

namespace itr_device
{
    AsiCamera::AsiCamera()
    {
        //ctor
        _AqPara.AquaireFreq=100000;
    }

    AsiCamera::~AsiCamera()
    {
        //dtor
        delete[] p_base;

    }
    void AsiCamera::Open(U32 ID,S32 Width,S32 Height,S32 BufferNum)
    {

        assert(BufferNum ==0);/// only 实现同步；
        _width=Width;
        _height=Height;

        S32 numDevices;
        numDevices = getNumberOfConnectedCameras();

        assert(numDevices>=0);
        assert(numDevices>=(S32)ID);
        //if(numDevices>0)
        printf("\ndevices number %d\n",numDevices);
        bool openresult;
        openresult=openCamera(ID);
        assert(openresult);
        assert((Width*Height)%1024==0);

        initCamera();

        p_base=new U8[_width*_height]();

        setImageFormat(_width, _height, 1, IMG_RAW8);

        SetPara();
    }

s
    void AsiCamera::Close()
    {
        closeCamera();
    }


    S32 AsiCamera::GetWidth()
    {
        return (_width);
    }


    S32 AsiCamera::GetHeight()
    {
        return (_height);
    }


    AsiCamera::AquairePara AsiCamera::GetPara()
    {
        return  (_AqPara);
    }

    void AsiCamera::SetPara()
    {
        setValue(CONTROL_GAIN,50,true);
        setValue(CONTROL_EXPOSURE, 20*1000, true); //auto exposure

    }
    void AsiCamera::SetPara(AquairePara Para)
    {
        _AqPara.AquaireFreq=Para.AquaireFreq;
        _AqPara.Exposure=Para.Exposure;
        _AqPara.Format=Para.Format;
        _AqPara.Gain=Para.Gain;

        setValue(CONTROL_GAIN,(int)_AqPara.Gain,false);
        setValue(CONTROL_EXPOSURE, (int)_AqPara.Exposure, true); //auto exposure
        setImageFormat(_width, _height, 1, IMG_RAW8);     //

    }


    S32 AsiCamera::FetchFrame(U8 *Raw,S32 Length,void *ExInfo)
    {
        bool result;
        result =getImageData(Raw,Length,-1);
        /// ////ExInfo
        ExInfo=& _AqPara;
        return (result);
    }



    void AsiCamera::Start()
    {
        startCapture();
    }

    void AsiCamera::Stop()
    {
        stopCapture();
    }


    void AsiCamera::RegCallBack(ReceiveFrameCallBack Callback)
    {
        if(Callback!=NULL)
        {
            callback=Callback;
        }
    }


    void AsiCamera::PushBufferBack(U8 *Raw)
    {

    }

}
