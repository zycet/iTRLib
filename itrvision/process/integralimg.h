#ifndef INTEGRALIMG_H
#define INTEGRALIMG_H
#include "itrbase.h"

using itr_math::Matrix;

namespace itr_vision
{
class IntegralImg
{
public:
    /**
    * \brief 求输入图像的积分图像
    * \param input 输入图像
    * \param output 原图像的积分图像
    */
    static void Integral(const Matrix &input,Matrix &output);
    /**
    * \brief 计算指定图像的盒子积分值(起始坐标系)
    * \param input 积分图像
    * \param RowPos 行位置(起始Y坐标)
    * \param ColPos 列位置(起始X坐标)
    * \param RowNum 行数(积分盒高度)
    * \param ColNum 列数(积分盒宽度)
    */
    static F32 BoxFilterStarter(const Matrix &input,S32 RowPos,S32 ColPos,S32 RowNum,S32 ColNum);
    /**
    * \brief 计算指定图像的盒子积分值(中央坐标系)
    * \param input 积分图像
    * \param RowPos 行位置(中央Y坐标)
    * \param ColPos 列位置(中央X坐标)
    * \param RowHalfWidth 积分盒半高(积分盒高度必须为奇术)
    * \param ColHalfWidth 积分盒半宽(积分盒宽度必须为奇术)
    */
    static F32 BoxFilterCenter(const Matrix &input,S32 RowPos,S32 ColPos,S32 RowHalfWidth,S32 ColHalfWidth);
protected:
private:
};
}

#endif // INTEGRALIMG_H
