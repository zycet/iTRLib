#ifndef CAMERA_H
#define CAMERA_H
#include "itrbase.h"
using itr_math::Matrix;

class ImageAquaire
{
    public:

        virtual void Init(int Width,int Height,int BufferNum);
        /**
        * \brief 获取一帧图像
        * \param 输出的灰度图像
        */
        virtual void FetchFrame(Matrix &img);

        /**
        * \brief 开始捕获
        */
        virtual void Start();
       /**
        * \brief 停止捕获
        */
        virtual void Stop();

        /**
        * \brief 释放摄像头
        */
        virtual void Close();

        /**
        * \brief 传入回调函数
        * \param 当获得一张图片时调用的回调
        */
        virtual void AddEvent(OnFetchFrame callback);

        /**
        * \brief 将缓冲区返回图像队列
        * \param 缓冲区地址
        */
        virtual void PushBack(Matrix*);


        /**
        * \brief 回调函数定义
        */
        typedef void (*OnFetchFrame)(ImageAquaire&,Matrix*);

    protected:
    private:
};

#endif // CAMERA_H
