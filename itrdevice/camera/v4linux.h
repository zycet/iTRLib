#ifndef V4LINUX_H
#define V4LINUX_H
#include "itrbase.h"
#include "icamera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include "libv4l2.h"

#define CLEAR(x) memset(&(x), 0, sizeof(x))


namespace itr_device
{
    class v4linux:public ICamera
    {
        public:

            v4linux();
            virtual ~v4linux();
            enum PIC_TYPE {
                YUV,
                RGB
             };
            /**
            * \brief 初始化摄像头,用来配置图象格式
            * \param typ =0 时输出RGB格式; typ=1时输出YUV格式(只输出Y分量)
            */
            void Init(S32 typ);

            typedef void (*ReceiveFrameCallBack)(ICamera &ICameraObj,U8 *Raw,S32 Length,void *ExInfo);

            /**
            * \brief 打开摄像头
            * \param Width 图像宽度
            * \param Height 图像高度
            * \param BufferNum 缓冲区数量(如果>0则表示使用异步采集模式,否则为同步模式)
            *                                       缓冲区大小为:RGB:3*W*H, YUV:W*H
            */
            virtual int Open(U32 ID,S32 Width,S32 Height,S32 BufferNum);
            /**
            * \brief  Set camera tunnel;
            */
            virtual void SetTunnel(S32 index);
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
            virtual S32 FetchFrame(U8 *Raw,S32 Length,void *ExInfo);

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
            virtual void PushBufferBack(U8 *Raw);

        protected:
        private:

            struct buffer {
                void   *start;
                size_t length;
            };


            struct AquairePara _AqPara;
            S32 _width;
            S32 _height;
            S32 _buffernum;

            S32                             r, fd;
            ReceiveFrameCallBack _callback;

            struct v4l2_format              fmt;
            struct v4l2_buffer              buf;
            struct v4l2_requestbuffers      req;
            enum v4l2_buf_type              type;
            struct buffer                   *buffers;
            struct timeval                  tv;
            fd_set                          fds;

            PIC_TYPE _type;
            void xioctl(int fh, int request, void *arg);
    };
}
#endif // V4LINUX_H
