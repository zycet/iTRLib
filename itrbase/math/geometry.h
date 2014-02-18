
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

    void SetDXDY(F32 DX, F32 DY);
    void SetAngleDistance(F32 Angle, F32 Distance);
    Distance2D();
    Distance2D(const Distance2D& Dis);
    void operator=(Distance2D Dis);
    Distance2D operator+(Distance2D Dis) const;
    Distance2D operator-(Distance2D Dis) const;
    F32 GetAngle() const;
    F32 GetDistance() const;
};

class Point2D
{
public:
    F32 X, Y;

    void SetXY(F32 X, F32 Y);
    Point2D();
    Point2D(F32 X, F32 Y);
    Point2D(const Point2D& Point);
    void operator=(const Point2D& Point);
    Distance2D operator-(const Point2D& Point) const;
    Point2D operator+(const Distance2D Dis) const;
    Point2D operator-(const Distance2D Dis) const;
};

class Point3D
{
public:
    F32 X, Y, Z;
    Point3D(F32 X, F32 Y, F32 Z);
};

class RectangleF
{
public:
    F32 X;
    F32 Y;
    F32 Width;
    F32 Height;

    void SetPoint(Point2D P);
    RectangleF();
    RectangleF(F32 X, F32 Y, F32 Width, F32 Height);
    void Init(F32 X, F32 Y, F32 Width, F32 Height);
    Point2D GetPoint() const;
    Point2D GetCenter() const;
    BOOL IsInRectangle(Point2D Point) const;
};

class RectangleS
{
public:
    S32 X;
    S32 Y;
    S32 Width;
    S32 Height;

    RectangleS();
    RectangleS(S32 X, S32 Y, S32 Width, S32 Height);
    void Init(S32 X, S32 Y, S32 Width, S32 Height);
    BOOL IsInRectangle(S32 X, S32 Y) const;
    void Reset();
    BOOL Next(S32& X, S32& Y);
private:
    S32 _x;
    S32 _y;
    S32 _xEnd;
    S32 _yEnd;
};
}

#endif // GEOMETRY_H_
