/**
*\ Circle 画出图像中的一个已知原点半径的圆
*\ LineOffset 画出图像中的已知起点和长宽的偏移值的直线
*\ Line 画出图像中已知起点终点的直线
*\ Cross 画出十字
*\ Rectangul 画出矩形

 */

#ifndef DRAW_H_
#define DRAW_H_
#include "../itrvision.h"
#include "../feature/featurepoint.h"
#include "itrbase.h"
#include <vector>
using std::vector;
using itr_math::RectangleS;
using itr_math::Matrix;
namespace itr_vision
{

    class Draw
    {
        public:
            static void Circle(ImageARGB &Img, S32 x, S32 y, S32 r, U32 color);
            static void Circle(Matrix &Img, S32 x, S32 y, S32 r, S16 color);
            static void LineOffset(Matrix &Img,S32 x, S32 y, S32 offsetx ,S32 offsety,S16 color);
            static void LineOffset(ImageARGB &Img,S32 x, S32 y, S32 offsetx ,S32 offsety,U32 color);
            static void Line(Matrix &Img,S32 beginx, S32 beginy, S32 endx ,S32 endy,S16 color);
            static void Line(ImageARGB &Img,S32 beginx, S32 beginy, S32 endx ,S32 endy,U32 color);
            static void Cross(Matrix &bmp, S32 x, S32 y, S32 scale, S16 color);
            static void Cross(ImageARGB &bmp, S32 x, S32 y, S32 scale, U32 color);
            static void Rectangle(Matrix &Img,RectangleS rect,S16 color);
            static void Rectangle(ImageARGB &Img,RectangleS rect,U32 color);
            static void Correspond(const Matrix &Img1,const Matrix &Img2,const vector<FeaturePoint> &feature1,const vector<FeaturePoint> &feature2,S32 FeatureNum,Matrix &Result);
    };

} // namespace itr_vision
#endif // DRAW_H_
