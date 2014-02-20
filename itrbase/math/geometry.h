
#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
class Distance2D
{
public:
    F32 DX;
    F32 DY;
    /**
     * \brief 设置两点坐标
     * \param DX 横坐标
     * \param DY 纵坐标
     */
    void SetDXDY(F32 DX, F32 DY);
    /**
     * \brief 设置角度和距离
     * \param Angle 角度
     * \param Distance 距离
     */
    void SetAngleDistance(F32 Angle, F32 Distance);
    /**
     * \brief 初始化
     */
    Distance2D();
    Distance2D(const Distance2D& Dis);
    /**
     * \brief 重载运算，赋值
     */
    void operator=(Distance2D Dis);
    /**
     * \brief 重载运算，相加
     */
    Distance2D operator+(Distance2D Dis) const;
    /**
     * \brief 重载运算，相减
     */
    Distance2D operator-(Distance2D Dis) const;
    /**
     * \brief 获取角度
     */
    F32 GetAngle() const;
    /**
     * \brief 获取距离
     */
    F32 GetDistance() const;
};

class Point2D
{
public:
    F32 X, Y;
    /**
     * \brief 设置两点坐标
     * \param X 横坐标
     * \param Y 纵坐标
     */
    void SetXY(F32 X, F32 Y);
    /**
     * \brief 初始化
     */
    Point2D();
    /**
     * \brief 初始化
     * \param X 横坐标
     * \param Y 纵坐标
     */
    Point2D(F32 X, F32 Y);
    /**
     * \brief 初始化
     * \param Point 应用的其他坐标点
     */
    Point2D(const Point2D& Point);
    /**
     * \brief 重载运算，赋值
     */
    void operator=(const Point2D& Point);
    /**
     * \brief 重载运算，相减，Distance2D减Point2D
     */
    Distance2D operator-(const Point2D& Point) const;
    /**
     * \brief 重载运算，相加，Point2D加Distance2D
     */
    Point2D operator+(const Distance2D Dis) const;
    /**
     * \brief 重载运算，相减，Point2D减Distance2D
     */
    Point2D operator-(const Distance2D Dis) const;
};

class Point3D
{
public:
    /**
     * \brief 初始化
     * \param X 横坐标
     * \param Y 纵坐标
     * \param Z 深度坐标
     */
    F32 X, Y, Z;
    /**
     * \brief 设置参数
     * \param X 横坐标
     * \param Y 纵坐标
     * \param Z 深度坐标
     */
    Point3D(F32 X, F32 Y, F32 Z);
};

class RectangleF
{
public:
    F32 X;
    F32 Y;
    F32 Width;
    F32 Height;
    /**
     * \brief 设置起点坐标
     * \param P 给定坐标点
     */
    void SetPoint(Point2D P);
    /**
     * \brief 初始化
     */
    RectangleF();
    /**
     * \brief 全参数初始化
     * \param X 横坐标
     * \param Y 纵坐标
     * \param Width 宽度
     * \param Height 高度
     */
    RectangleF(F32 X, F32 Y, F32 Width, F32 Height);
    /**
     * \brief 后初始化
     * \param X 横坐标
     * \param Y 纵坐标
     * \param Width 宽度
     * \param Height 高度
     */
    void Init(F32 X, F32 Y, F32 Width, F32 Height);
    /**
     * \brief 获取起点坐标
     */
    Point2D GetPoint() const;
    /**
     * \brief 获取中心点坐标
     */
    Point2D GetCenter() const;
    /**
     * \brief 判断Point是否是在矩形内部
     * \param Point 要判断的点
     */
    BOOL IsInRectangle(Point2D Point) const;
};

class RectangleS
{
public:
    S32 X;
    S32 Y;
    S32 Width;
    S32 Height;
    /**
     * \brief 初始化
     */
    RectangleS();
    /**
     * \brief 全参数初始化
     * \param X 横坐标
     * \param Y 纵坐标
     * \param Width 宽度
     * \param Height 高度
     */
    RectangleS(S32 X, S32 Y, S32 Width, S32 Height);
    /**
     * \brief 后初始化
     * \param X 横坐标
     * \param Y 纵坐标
     * \param Width 宽度
     * \param Height 高度
     */
    void Init(S32 X, S32 Y, S32 Width, S32 Height);
    /**
     * \brief 判断Point是否是在矩形内部
     * \param X 要判断的点的横坐标
     * \param Y 要判断的点的纵坐标
     */
    BOOL IsInRectangle(S32 X, S32 Y) const;
    /**
     * \brief 重置
     */
    void Reset();
    /**
     * \brief 遍历矩形区域内所有点
     * \param X 起点横坐标
     * \param Y 起点纵坐标
     */
    BOOL Next(S32& X, S32& Y);
private:
    S32 _x;
    S32 _y;
    S32 _xEnd;
    S32 _yEnd;
};
}

#endif // GEOMETRY_H_
