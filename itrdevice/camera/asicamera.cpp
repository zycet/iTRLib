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
//    delete[] bufferlist;
}
/**
* \brief 打开摄像头
* \param Width 图像宽度
* \param Height 图像高度
* \param BufferNum 缓冲区数量(如果>0则表示使用异步采集模式,否则为同步模式)
*/
void AsiCamera::Open(U32 ID,S32 Width,S32 Height,S32 BufferNum)
{

    assert(BufferNum ==0);/// only 实现同步；
    _width=Width;
    _height=Height;
    //_buffernum=BufferNum;
    S32 numDevices;
    numDevices = getNumberOfConnectedCameras();

    assert(numDevices>0);
    assert(numDevices>=(S32)ID);

    bool openresult;
    openresult=openCamera(ID);
    assert(openresult);
    assert((Width*Height)%1024==0);

    initCamera();

//    if(BufferNum>0)
//    {
  //      cycleQueue.Init(BufferNum);
        p_base=new U8[_width*_height]();
//        bufferlist=new U8*[BufferNum]();

//        /// join in the queue
//        for(S32 i=0; i<BufferNum; i++)
//        {
//            cycleQueue.Insert(p_base+i*_width*_height);
//            bufferlist[i]=p_base+i*_width*_height;
//        }
        setImageFormat(_width, _height, 1, IMG_RAW8);
//    }

}

/**
* \brief 关闭摄像头
*/
void AsiCamera::Close()
{
    closeCamera();
}

/**
* \brief 获得图像宽度
*/
S32 AsiCamera::GetWidth()
{
    return (_width);
}

/**
* \brief 获得图像高度
*/
S32 AsiCamera::GetHeight()
{
    return (_height);
}

/**
* \brief 获得采集参数
*/
AsiCamera::AquairePara AsiCamera::GetPara()
{
    return  (_AqPara);
}
/**
* \brief 设置采集参数
*/
void AsiCamera::SetPara(AquairePara Para)
{
    _AqPara.AquaireFreq=Para.AquaireFreq;
    _AqPara.Exposure=Para.Exposure;
    _AqPara.Format=Para.Format;
    _AqPara.Gain=Para.Gain;

    setValue(CONTROL_GAIN,(int)_AqPara.Gain,false);
    setValue(CONTROL_EXPOSURE, (int)_AqPara.Exposure, false); //auto exposure
    setImageFormat(_width, _height, 1, IMG_RAW8);     //
   // setValue(CONTROL_GAMMA,2,false);
//    setValue(CONTROL_BRIGHTNESS,3,false);
//    setValue(CONTROL_BANDWIDTHOVERLOAD,4,false);
}

/**
* \brief 同步获取一帧图像
* \param Raw 输出图像用的缓冲区
* \param Length 输出图像用的缓冲区长度
* \param ExInfo 输出图像用附加信息的缓冲区
* \return 成功写入缓冲区的数据长度,无图像返回0,发生错误返回-1.
* \note 此函数用于同步模式下的图像获取,在Open函数调用时需使BufferNum=0.
*/
S32 AsiCamera::FetchFrame(U8* Raw,S32 Length,void* ExInfo)
{

    startCapture(); //start privew

    bool result;

    result =getImageData(Raw,Length,1/(_AqPara.AquaireFreq*1000));

    stopCapture();

    /// ////ExInfo
    ExInfo=& _AqPara;

    return (result);
}


/**
* \brief 异步捕获开始
* \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
*/
void AsiCamera::Start()
{
    startCapture();
//
//    for(S32 i=0; i<cycleQueue.GetLength(); i++)
//    {
//        cycleQueue.Fetch(p_use);
//        while(!getImageData(p_use,_width*_height,0))
//            callback(*this, p_use, _width*_height, &AqPara);//
//    }
}
/**
* \brief 异步捕获停止
* \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
*/
void AsiCamera::Stop()
{
    stopCapture();
//    cycleQueue.Clear();
}

/**
* \brief 传入回调函数
* \param 当获得一张图片时调用的回调函数
*/
void AsiCamera::RegCallBack(ReceiveFrameCallBack Callback)
{
    if(Callback!=NULL)
        callback=Callback;
}

/**
* \brief 在图像处理完成后将缓冲区返回图像队列(如果无可用图像采集缓冲区会导致图像采集暂停)
* \param Raw 缓冲区地址
* \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
*/
void AsiCamera::PushBufferBack(U8* Raw)
{
//    for(S32 i=0; i<_buffernum; i++)
//    {
//        if(bufferlist[i]== Raw)
//        cycleQueue.Insert(Raw);
//    }
}

}
