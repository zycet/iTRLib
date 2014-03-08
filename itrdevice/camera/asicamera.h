#ifndef ASICAMERA_H
#define ASICAMERA_H

#include "asicameraapi.h"
#include "icamera.h"
#include "itrbase.h"
namespace itr_device
{
class AsiCamera:public ICamera
{
    public:
        AsiCamera();
        virtual ~AsiCamera();
        enum RawFormat
        {
            RawMono8,
            RawMono16,
            RawYUV444,
            RawYUV422,
            RawYUV411,
            RawYUV420,
            RawRGB24,
            RawRGB48,
            RawBGR24,
            RawRGBA32,
            RawBGRA32,
            RawBayer8RGGB,
            RawBayer8GBRG,
            RawBayer8GRBG,
            RawBayer8BGGR,
            RawBayer16RGGB,
            RawBayer16GBRG,
            RawBayer16GRBG,
            RawBayer16BGGR,
        };
        /**
        * \brief 回调函数定义
        * \param ICameraObj 图像采集器本身
        * \param Raw 图像原始数据
        * \param Length 图像原始数据长度
        * \param ExInfo 图像附加信息
        */
        typedef void (*ReceiveFrameCallBack)(AsiCamera& AsiCameraObj,U8* Raw,S32 Length,void* ExInfo);

        /**
        * \brief 打开摄像头
        * \param Width 图像宽度
        * \param Height 图像高度
        * \param BufferNum 缓冲区数量(如果>0则表示使用异步采集模式,否则为同步模式)
        */
        virtual void Open(U32 ID,S32 Width,S32 Height,S32 BufferNum);

        /**
        * \brief 关闭摄像头
        */
        virtual void Close();

        /**
        * \brief 获得图像宽度
        */
        virtual S32 GetWidth();

        /**
        * \brief 获得图像高度
        */
        virtual S32 GetHeight();

        /**
        * \brief 获得采集参数
        */
        virtual AquairePara GetPara();

        /**
        * \brief 设置采集参数
        */
        virtual void SetPara(AquairePara Para);

        /**
        * \brief 同步获取一帧图像
        * \param Raw 输出图像用的缓冲区
        * \param Length 输出图像用的缓冲区长度
        * \param ExInfo 输出图像用附加信息的缓冲区
        * \return 成功写入缓冲区的数据长度,无图像返回0,发生错误返回-1.
        * \note 此函数用于同步模式下的图像获取,在Open函数调用时需使BufferNum=0.
        */
        virtual S32 FetchFrame(U8* Raw,S32 Length,void* ExInfo);

        /**
        * \brief 异步捕获开始
        * \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
        */
        virtual void Start();
        /**
        * \brief 异步捕获停止
        * \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
        */
        virtual void Stop();

        /**
        * \brief 传入回调函数
        * \param 当获得一张图片时调用的回调函数
        */
        virtual void RegCallBack(ReceiveFrameCallBack Callback);

        /**
        * \brief 在图像处理完成后将缓冲区返回图像队列(如果无可用图像采集缓冲区会导致图像采集暂停)
        * \param Raw 缓冲区地址
        * \note 此函数用于异步模式下的图像获取,在Open函数调用时需使BufferNum>0.
        */
        virtual void PushBufferBack(U8* Raw);
        struct AquairePara AqPara;
        S32 _numDevices;
        S32 _width;
        S32 _height;
        itr_container::CycleQueue<U8*>  cycleQueue;
        U8 *p_base, *p_use,**bufferlist;
        S32 _buffernum;
        ReceiveFrameCallBack callback;
    protected:
    private:
};
}
#endif // ASICAMERA_H
