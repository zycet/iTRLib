#ifndef DRAW_H_
#define DRAW_H_
#include "../itrvision.h"
#include "itrbase.h"
#include <math.h>
#include <vector>
using std::vector;
using itr_math::RectangleS;
using itr_math::Matrix;
using itr_math::Point2D;
namespace itr_vision
{

class Draw
{
public:
    /**
      * \brief 在输入图像中绘制圆
      * \param Img 输入图像
      * \param x 圆心原点横坐标
      * \param y 圆心原点纵坐标
      * \param r 圆的半径
      * \param color 图像灰度值
      */
    static void Circle(Matrix &Img, S32 x, S32 y, S32 r, S16 color);
    /**
      * \brief 在输入图像中绘制直线
      * \param Img 输入图像
      * \param x 起始点横坐标
      * \param y 起始点纵坐标
      * \param offsetx 直线长度x方向投影
      * \param offsety 直线长度y方向投影
      * \param color 图像灰度值
      */
    static void LineOffset(Matrix &Img,S32 x, S32 y, S32 offsetx ,S32 offsety,S16 color);
    
    /**
      * \brief 在输入图像中绘制线段
      * \param Img 输入图像
      * \param x 起始点横坐标
      * \param y 起始点纵坐标
      * \param endx 终点横坐标
      * \param endy 终点纵坐标
      * \param color 图像灰度值
      */
    static void Line(Matrix &Img,S32 beginx, S32 beginy, S32 endx ,S32 endy,S16 color);
    
    /**
      * \brief 在输入图像中绘制十字
      * \param bmp 输入图像
      * \param x 中心点横坐标
      * \param y 中心点纵坐标
      * \param scale 十字长度
      * \param color 图像灰度值
      */
    static void Cross(Matrix &bmp, S32 x, S32 y, S32 scale, S16 color);
    
    /**
      * \brief 在输入图像中绘制矩形
      * \param Img 输入图像
      * \param RectangleS 绘制矩形的参数
      * \param color 图像灰度值
      */
    static void Rectangle(Matrix &Img,RectangleS rect,S16 color);
    

    /**
      * \brief 绘制两幅图像之间特征点的匹配关系
      * \param Img1 输入图像1
      * \param Img2 输入图像2
      * \param feature1 图像1的特征点
      * \param feature2 图像2的特征点
      * \param FeatureNum 最多绘制的特征点数
      * \param 结果图像
      */
    static void Correspond(const Matrix &Img1,const Matrix &Img2,const vector<Point2D> &feature1,const vector<Point2D> &feature2,S32 FeatureNum,Matrix &Result);
};

} // namespace itr_vision
#endif // DRAW_H_
