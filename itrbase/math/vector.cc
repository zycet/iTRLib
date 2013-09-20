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

#include "../platform/platform.h"
#include "math.h"
#include <stddef.h>

namespace itr_math
{
    Calculate* Vector::calculateObj = NULL;
    /*
     * 初始化维数为Dim的向量(自动分配本地空间)
     */
    Vector::Vector(S32 Dim)
    {
        data = new F32[Dim];
        dim = Dim;
        localData = true;
    }
    /*
     * 初始化维数为Dim的向量(使用Data指向的空间储存数据)
     */
    Vector::Vector(S32 Dim, F32* Data)
    {
        data = Data;
        dim = Dim;
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

    void Vector::CopyFrom(S32 Offset, S32 Num, F32* Data)
    {
        MemoryCopy(data + Offset, Data, Num * sizeof(F32));
    }
    /*
     * 复制数据至内部
     */
    void Vector::CopyFrom(F32* Data)
    {
        MemoryCopy(data, Data, dim * sizeof(F32));
    }
    /*
     * 复制指定位置数据到Data
     */
    void Vector::CopyTo(S32 Offset, S32 Num, F32* Data) const
    {
        MemoryCopy(Data, data + Offset, Num * sizeof(F32));
    }
    /*
     * 复制数据至Data
     */
    void Vector::CopyTo(F32* Data) const
    {
        MemoryCopy(Data, data, dim * sizeof(F32));
    }
    /*
     * 向量元素积
     */
    void Vector::Product(const Vector& Vec) const
    {
        calculateObj->Multi(data, Vec.GetData(), dim, data);
    }
    /*
     * 向量内积
     */
    F32 Vector::ProductInner(const Vector& Vec) const
    {
        F32 result = 0;
        calculateObj->Product(data, Vec.GetData(), dim, result);
        return result;
    }
    /*
     * 向量外积
     */
    Vector Vector::ProductOuter(const Vector& Vec) const
    {
        assert(false);
        return *this;
    }

} // namespace itr_math
