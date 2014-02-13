#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include "itrbase.h"
#include <vector>
using std::vector;
using itr_math::Matrix;
using itr_math::RectangleS;
class Histogram
{
    public:
        /**
        * \brief 求图像的直方图
        * \param img 输入图像
        * \param statistic 图像的直方图，该数组长度应为256
        */
        static void Info(const Matrix &img,vector<int> &statistic);

        /**
        * \brief 将图像直方图均衡化
        * \param input 输入图像
        * \param output 直方图均衡后的图像
        */
        static void Euqal(const Matrix &input,Matrix &output);

        /**
        * \brief 将图像的一个区域直方图均衡化
        * \param input 输入图像
        * \param rect 需要均衡的区域
        * \param output 直方图均衡后的图像
        */
        static void Euqal(const Matrix &input,const RectangleS &rect,Matrix &output);
    protected:
    private:
};

#endif // HISTOGRAM_H
