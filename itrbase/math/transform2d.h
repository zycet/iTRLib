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
 * transform2d.h
 *  Created on: 2013-9-23
 *      Author: buaa
 */

#ifndef TRANSFORM2D_H_
#define TRANSFORM2D_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
/*
 * 2D仿射变换器
 * 初始化后按需求调用偏移、缩放、旋转后调用变换函数对目标坐标进行转换
 */
class Transform2D
{
public:
    Transform2D();
    virtual ~Transform2D();
    /*
     * 返回内部变换矩阵（3*3）
     */
    inline Matrix& GetTransformMatrix()
    {
        return transformMatrix;
    }
    /*
     * 重置为初始状态
     */
    void Reset();
    /*
     * 直角坐标偏移
     */
    void Offset(F32 X, F32 Y);
    /*
     * 直角坐标缩放
     * 系数为1表示不缩放，大于1放到，小于1缩小(负数则镜像)
     */
    void Scale(F32 KX, F32 KY);
    /*
     * 旋转（右手坐标系，逆时针为正，角度制）
     */
    void Rotate(F32 Angle);
    /*
     * 反转矩阵使其可以进行反向变换
     */
    void Inv();

    /*
     * 2元向量坐标变换
     * Input&Output维度均需为3(齐次坐标）
     */
    void Transform(const Vector& Input, Vector& Output);
    /*
     * 2D点坐标变换
     */
    void Transform(const Point2D& Input, Point2D& Output);
    /*
     * 2D坐标变换
     */
    void Transform(F32 InputX, F32 InputY, F32& OutputX, F32& OutputY);

private:
    Matrix transformMatrix;
    Matrix tempMatrix;
    Vector inputVector;
    Vector outputVector;
    Numerical numericalObj;
    void Reset(Matrix& Mat);
};

} // namespace itr_math
#endif // TRANSFORM2D_H_
