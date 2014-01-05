/*
 *
 *   Copyright (C) 2013 BUAA iTR Research Center. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * geometry.h
 *  Created on: 2013-9-23
 *      Author: buaa
 */

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
