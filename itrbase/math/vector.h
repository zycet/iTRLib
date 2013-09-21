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
 * vector.h
 *  Created on: 2013年9月20日
 *      Author: ZYC
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>
#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
    class Vector
    {
        public:
            /*
             * 设置批量计算对象(此函数需要在进行所有计算前调用)
             */
            inline static void SetCalculateObj(Calculate* CalculateObj)
            {
                calculateObj = CalculateObj;
            }
            /*
             * 初始化维数为Dim的向量(自动分配本地空间)
             */
            Vector(S32 Dim);
            /*
             * 初始化维数为Dim的向量(使用Data指向的空间储存数据)
             */
            Vector(S32 Dim, F32* Data);
            /*
             * 构造完全一样的向量(Clone)
             */
            Vector(const Vector& Vec);
            /*
             * 回收本地空间(如果曾经分配)
             */
            virtual ~Vector();
            /*
             * 返回维数
             */
            inline S32 GetDim() const
            {
                return dim;
            }
            /*
             * 返回内部数据地址
             */
            inline F32* GetData() const
            {
                return data;
            }
            /*
             * 返回是否是采用本地分配的空间
             */
            inline BOOL IsLocalData() const
            {
                return localData;
            }
            /*
             * 返回维数是否一致
             */
            inline BOOL MatchDim(const Vector& Vec) const
            {
                return (Vec.GetDim() == dim);
            }
            /*
             * 全部元素清零
             */
            inline virtual void Zero()
            {
                calculateObj->Set(data, 0, dim);
            }
            /*
             * 全部设置为指定值
             */
            inline virtual void Set(F32 K)
            {
                calculateObj->Set(data, K, dim);
            }
            /*
             * 复制数据至内部指定位置
             */
            virtual void CopyFrom(S32 Offset, S32 Num, F32* Data);
            /*
             * 复制数据至内部
             */
            virtual void CopyFrom(F32* Data);
            /*
             * 复制指定位置数据到Data
             */
            virtual void CopyTo(S32 Offset, S32 Num, F32* Data) const;
            /*
             * 复制数据至Data
             */
            virtual void CopyTo(F32* Data) const;
            /*
             * 写入单个元素
             */
            inline F32& operator[](int index)
            {
                assert(index < dim);
                return data[index];
            }
            /*
             * 读取单个元素
             */
            inline F32 operator[](int index) const
            {
                assert(index < dim);
                return data[index];
            }
            /*
             * 全部元素增加K
             */
            inline virtual void Add(F32 K)
            {
                calculateObj->Offset(data, K, dim, data);
            }
            /*
             * 全部元素乘以K
             */
            inline virtual void Mul(F32 K)
            {
                calculateObj->Scale(data, K, dim, data);
            }
            /*
             * 加上向量Vec(维数需一致)
             */
            inline virtual void Add(const Vector& Vec)
            {
                assert(MatchDim(Vec));
                calculateObj->Add(data, Vec.GetData(), dim, data);
            }
            /*
             * 减去向量Vec(维数需一致)
             */
            inline virtual void Sub(const Vector& Vec)
            {
                assert(MatchDim(Vec));
                calculateObj->Sub(data, Vec.GetData(), dim, data);
            }
            /*
             * 向量元素积
             */
            virtual void Product(const Vector& Vec);
            /*
             * 向量内积
             */
            virtual F32 ProductInner(const Vector& Vec) const;
            /*
             * 向量外积
             */
            virtual void ProductOuter(const Vector& Vec);
        private:
            F32* data;
            S32 dim;
            BOOL localData;
            static Calculate* calculateObj;
    };

} // namespace itr_math
#endif // VECTOR_H_
