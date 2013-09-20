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

#include "../platform/platform.h"

namespace itr_math
{
    class Vector
    {
        public:
            /*
             * 设置数值计算对象
             */
            inline static void SetNumericalObj(Numerical* NumericalObj)
            {
                numericalObj = NumericalObj;
            }
            /*
             * 设置批量计算对象
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
            inline S32 GetData() const
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
            inline BOOL matchDimension(const Vector& Vec) const
            {
                return (Vec.GetDim() == dim);
            }
            /*
             * 全部元素清零
             */
            inline virtual void Zero()
            {

            }
            /*
             * 全部设置为指定值
             */
            inline virtual void Set(F32 K)
            {

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
                return data[index];
            }
            /*
             * 读取单个元素
             */
            inline F32 operator[](int index) const
            {
                return data[index];
            }
            /*
             * 全部元素增加K
             */
            inline virtual void Add(F32 K)
            {

            }
            /*
             * 全部元素乘以K
             */
            inline virtual void Mul(F32 K)
            {

            }
            /*
             * 加上向量Vec(维数需一致)
             */
            inline virtual void Add(const Vector& Vec)
            {

            }
            /*
             * 减去向量Vec(维数需一致)
             */
            inline virtual void Sub(const Vector& Vec)
            {

            }
            /*
             * 向量内积
             */
            inline virtual F32 Mul(const Vector& Vec) const;
            /*
             * 向量外积
             */
            virtual Vector DotMul(const Vector& Vec) const;
        private:
            F32* data;
            S32 dim;
            BOOL localData;
            static Numerical* numericalObj;
            static Calculate* calculateObj;
    };

} // namespace itr_math
#endif // VECTOR_H_
