#ifndef INTEGRALIMG_H
#define INTEGRALIMG_H
#include "itrbase.h"
using itr_math::Matrix;
class IntegralImg
{
    public:
      /**
        * \brief 求输入图像的积分图像
        * \param input 输入图像
        * \param output 原图像的积分图像
        */
        static void  Normal(const Matrix &input,Matrix &output);

        /**
        * \brief 求输入图像的二次积分图像
        * \param input 输入图像
        * \param output 原图像每个像素点平方后的积分图像
        */
        static void Square(const Matrix &input,Matrix &output);
    protected:
    private:
};

#endif // INTEGRALIMG_H
