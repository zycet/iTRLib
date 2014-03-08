#include "icamera.h"

namespace itr_device
{
/**
* \brief 此类为实时图像数据采集的基类,会同时输出原始数据及灰度的Matrix.
* \note 此类支持同步采集和异步数据采集.
*/


    /**
    * \brief 打开摄像头
    * \param Width 图像宽度
    * \param Height 图像高度
    * \param BufferNum 缓冲区数量(如果>0则表示使用异步采集模式,否则为同步模式)
    */
     void ICamera::Open(U32 ID,S32 Width,S32 Height,S32 BufferNum)
     {}

    /**
    * \brief 关闭摄像头
    */
     void ICamera::Close()
     {}

    /**
    * \brief 获得图像宽度
    */
     S32 ICamera::GetWidth()
     {return 0;}

    /**
    * \brief 获得图像高度
    */
     S32 ICamera::GetHeight()
     {return 0;}

    /**
    * \brief 获得采集参数
    */
     ICamera::AquairePara ICamera::GetPara()
     {
        ICamera::AquairePara a;
        return  a;
     }
    /**
    * \brief 设置采集参数
    */
     void ICamera::SetPara(AquairePara Para)
     {}

    /**
    * \brief 同步获取一帧图像
    * \param Raw 输出图像用的缓冲区
    * \param Length 输出图像用的缓冲区长度
    * \param ExInfo 输出图像用附加信息的缓冲区
    * \return 成功写入缓冲区的数据长度,无图像返回0,发生错误返回-1.
    * \note 此函数用于同步模式下的图像获取,在Open函数调用时需使BufferNum=0.
    */
     S32 ICamera::FetchFrame(U8* Raw,S32 Length,void* ExInfo)
     {return 0;}

    /**
    * \brief 异步捕获开始
    * \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
    */
     void ICamera::Start()
     {}
    /**
    * \brief 异步捕获停止
    * \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
    */
     void ICamera::Stop()
     {}

    /**
    * \brief 传入回调函数
    * \param 当获得一张图片时调用的回调函数
    */
     void ICamera::RegCallBack(ReceiveFrameCallBack Callback)
     {}

    /**
    * \brief 在图像处理完成后将缓冲区返回图像队列(如果无可用图像采集缓冲区会导致图像采集暂停)
    * \param Raw 缓冲区地址
    * \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
    */
     void ICamera::PushBufferBack(U8* Raw)
     {}


}

