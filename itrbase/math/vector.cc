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
 * vector.cc
 *  Created on: 2013年9月20日
 *      Author: ZYC
 */

#include <stddef.h>
#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
/*
 * 初始化维数为Dim的向量(自动分配本地空间)
 */
Vector::Vector(S32 Dim)
{
    data = NULL;
    dim = 0;
    localData = false;
    Init(Dim);
}
/*
 * 初始化维数为Dim的向量(使用Data指向的空间储存数据)
 */
Vector::Vector(S32 Dim, F32* Data)
{
    data = NULL;
    dim = 0;
    localData = false;
    Init(Dim,Data);
}
/*
 * 构造完全一样的向量(Clone)
 */
Vector::Vector(const Vector& Vec)
{
    assert(CalculateObj!=NULL);
    data = new F32[Vec.GetDim()]();
    assert(data!=NULL);
    dim = Vec.GetDim();
    CopyFrom(Vec.GetData());
    localData = true;
}
/*
 * 用于初始化列表的空构造函数
 * 在构造后需手动调用Init函数
 */
Vector::Vector()
{
    data = NULL;
    dim = 0;
    localData = false;
}
/*
 * 回收本地空间(如果曾经分配)
 */
Vector::~Vector()
{
    if (localData == true)
    {
        delete data;
    }
}
//**********后初始化函数**********
/*
* 初始化一个指定行列数的空矩阵(自动分配内存)
*/
void Vector::Init(S32 Dim)
{
    assert(CalculateObj!=NULL);
    assert(Dim > 0);
    data = new F32[Dim]();
    assert(data!=NULL);
    dim = Dim;
    localData = true;
}
/*
 * 初始化一个指定Dim的Vec(以传入的指针为数据区)
 */
 void Vector::Init(S32 Dim,F32* Data)
 {
    assert(CalculateObj!=NULL);
    assert(Dim > 0);
    data = new F32[Dim]();
    assert(data!=NULL);
    dim = Dim;
    MemoryCopy(data,Data,Dim*sizeof(F32));
    localData = false;
 }
void Vector::CopyFrom(S32 Offset, S32 Num, F32* Data)
{
    assert((Offset + Num) <= dim);
    assert(Data!=NULL);
    MemoryCopy(data + Offset, Data, Num * sizeof(F32));
}
/*
 * 复制数据至内部
 */
void Vector::CopyFrom(F32* Data)
{
    assert(Data!=NULL);
    MemoryCopy(data, Data, dim * sizeof(F32));
}
/*
 * 复制指定位置数据到Data
 */
void Vector::CopyTo(S32 Offset, S32 Num, F32* Data) const
{
    assert((Offset + Num) <= dim);
    assert(Data!=NULL);
    MemoryCopy(Data, data + Offset, Num * sizeof(F32));
}
/*
 * 复制数据至Data
 */
void Vector::CopyTo(F32* Data) const
{
    assert(Data!=NULL);
    MemoryCopy(Data, data, dim * sizeof(F32));
}
/*
 * 向量元素积(对应元素相乘)
 */
void Vector::Product(const Vector& Vec)
{
    assert(MatchDim(Vec));
    CalculateObj->Multi(data, Vec.GetData(), dim, data);
}
/*
 * 向量内积(点乘)
 */
F32 Vector::ProductInner(const Vector& Vec) const
{
    assert(MatchDim(Vec));
    F32 result = 0;
    CalculateObj->MultiSum(data, Vec.GetData(), dim, result);
    return result;
}
/*
 * 向量外积(叉乘)
 */
void Vector::ProductOuter(const Vector& Vec, Vector& VecResult) const
{
    assert(MatchDim(Vec));
    assert(MatchDim(VecResult));
    const int dim3 = 3;
    assert(dim == dim3); //暂时只支持维数为3的向量计算
    F32 r0[dim3] =
    { 0 };
    F32 r1[dim3] =
    { 0 };
    F32 a[dim3];
    F32 b[dim3];
    //ay*bz
    a[0] = data[1];
    b[0] = Vec[2];
    //az*bx
    a[1] = data[2];
    b[1] = Vec[0];
    //ax*by
    a[2] = data[0];
    b[2] = Vec[1];
    CalculateObj->Multi(a, b, dim3, r0);

    //-az*by
    a[0] = data[2];
    b[0] = -Vec[1];
    //-ax*bz
    a[1] = data[0];
    b[1] = -Vec[2];
    //-ay*bx
    a[2] = data[1];
    b[2] = -Vec[0];
    CalculateObj->Multi(a, b, dim3, r1);
    //累加
    CalculateObj->Add(r0, r1, dim3, VecResult.GetData());
}
} // namespace itr_math
