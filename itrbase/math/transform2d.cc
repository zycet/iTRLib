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
 * transform2d.cc
 *  Created on: 2013-9-23
 *      Author: buaa
 */

#include "transform2d.h"

namespace itr_math
{

Transform2D::Transform2D() :
    transformMatrix(3), tempMatrix(3), inputVector(3), outputVector(3)
{
    Reset(transformMatrix);
}

void Transform2D::Reset()
{
    Reset(transformMatrix);
}

Transform2D::~Transform2D()
{
}

void Transform2D::Offset(F32 X, F32 Y)
{
    Reset(tempMatrix);
    tempMatrix(0, 2) = X;
    tempMatrix(1, 2) = Y;
    transformMatrix = tempMatrix * transformMatrix;
}

void Transform2D::Scale(F32 KX, F32 KY)
{
    Reset(tempMatrix);
    tempMatrix(0, 0) = KX;
    tempMatrix(1, 1) = KY;
    transformMatrix = tempMatrix * transformMatrix;
}

void Transform2D::Rotate(F32 Angle)
{
    F32 rad = ANG2RAD(Angle);
    F32 sin, cos;
    numericalObj.SinCos(rad, sin, cos);
    Reset(tempMatrix);
    tempMatrix(0, 0) = cos;
    tempMatrix(0, 1) = -sin;
    tempMatrix(1, 0) = sin;
    tempMatrix(1, 1) = cos;
    transformMatrix = tempMatrix * transformMatrix;
}

void Transform2D::Inv()
{
    Matrix temp = transformMatrix;
    temp.Inv(transformMatrix);
}

void Transform2D::Transform(const Vector& Input, Vector& Output)
{
    Input[2]=1;
    Output = transformMatrix * Input;
}

void Transform2D::Transform(const Point2D& Input, Point2D& Output)
{
    inputVector[0] = Input.X;
    inputVector[1] = Input.Y;
    Transform(inputVector, outputVector);
    Output.X = outputVector[0];
    Output.Y = outputVector[1];
}

void Transform2D::Transform(F32 InputX, F32 InputY, F32& OutputX, F32& OutputY)
{
    inputVector[0] = InputX;
    inputVector[1] = InputY;
    Transform(inputVector, outputVector);
    OutputX = outputVector[0];
    OutputY = outputVector[1];
}

void Transform2D::Reset(Matrix& Mat)
{
    Mat.Clear();
    Mat.SetDiag(1);
}

} // namespace itr_math
