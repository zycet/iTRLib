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
    /**
     * \brief 初始化维数为Dim的向量(自动分配本地空间)
     * \param Dim 向量维数
     */
    Vector(S32 Dim);
    /**
     * \brief 初始化维数为Dim的向量(使用Data指向的空间储存数据)
     * \param Dim 向量维数
     * \param Data 向量所指向的数组
     */
    Vector(S32 Dim, F32 *Data);
    /**
     * \brief 构造完全一样的向量(Clone)
     * \param Vec clone的对象
     */
    Vector(const Vector &Vec);
    /**
     * \brief 用于初始化列表的空构造函数
     * \brief 在构造后需手动调用Init函数
     */
    Vector();
    /**
     * 回收本地空间(如果曾经分配)
     */
    virtual ~Vector();
    //**********后初始化函数**********
    /**
     * \brief 初始化一个指定行列数的空Vec(自动分配内存，只能在无参数构造对象后调用)
     * \param Dim 向量维数
     */
    void Init(S32 Dim);
    /**
     * \brief 初始化一个指定Dim的Vec(以传入的指针为数据区，只能在无参数构造对象后调用)
     * \param Dim 向量维数
     * \param Data 向量所指向的数据
     */
    void Init(S32 Dim, F32 *Data);
    /**
     * \brief 返回维数
     */
    inline S32 GetDim() const
    {
        return dim;
    }
    /**
     * \brief 返回内部数据地址
     */
    inline F32 *GetData() const
    {
        return data;
    }
    /**
     * \brief 返回是否是采用本地分配的空间
     */
    inline BOOL IsLocalData() const
    {
        return localData;
    }
    /**
     * \brief 返回维数是否一致
     */
    inline BOOL MatchDim(const Vector &Vec) const
    {
        return (Vec.GetDim() == dim);
    }
    /**
     * \brief 全部元素清零
     */
    inline virtual void Zero()
    {
        CalculateObj->Set(data, 0, dim);
    }
    /**
     * \brief 全部设置为指定值
     * \param K 指定的数值
     */
    inline virtual void Set(F32 K)
    {
        CalculateObj->Set(data, K, dim);
    }
    /**
     * \brief 复制数据至内部指定位置
     * \param Offset 内部向量的偏移量（写入的起始位置）
     * \param Num 写入数据数量
     * \param Data 给定数据
     */
    virtual void CopyFrom(S32 Offset, S32 Num, F32 *Data);
    /**
     * \brief 复制数据至内部
     * \param Data 给定数据
     */
    virtual void CopyFrom(F32 *Data);
    /**
     * \brief 复制指定位置数据到Data
     * \param Offset 内部向量的偏移量（读取的起始位置）
     * \param Num 写入数据数量
     * \param Data 给定数据
     */
    virtual void CopyTo(S32 Offset, S32 Num, F32 *Data) const;
    /**
     * \brief 复制数据至Data
     */
    virtual void CopyTo(F32 *Data) const;
    /**
     * \brief 写入单个元素
     * \param index 位置
     */
    inline F32 &operator[](int index)
    {
        assert(index < dim);
        return data[index];
    }
    /**
     * \brief 读取单个元素
     * \param index 位置
     */
    inline F32 &operator[](int index) const
    {
        assert(index < dim);
        return data[index];
    }
    /**
     * \brief 复制运算符重载
     */
    inline Vector &operator=(const Vector &Vec)
    {
        assert(MatchDim(Vec));
        Vec.CopyTo(data);
        return *this;
    }

    /**
     * \brief 全部元素增加 K
     * \param K 加数
     */
    inline virtual void Add(F32 K)
    {
        CalculateObj->Offset(data, K, dim, data);
    }

    inline Vector operator+(F32 K)
    {
        this->Add(K);
        return (*this);
    }
    /**
     * \brief 全部元素乘以 K
     * \param K 乘数
     */
    inline virtual void Mul(F32 K)
    {
        CalculateObj->Scale(data, K, dim, data);
    }
    /**
     * \brief 全部元素乘以 K
     * \param K 乘数
     */
    inline Vector operator*(F32 K) const
    {
        Vector temp(*this);
        temp.Mul(K);
        return (temp);
    }
    /**
     * \brief 加上向量Vec(维数需一致)
     * \param 相加的向量
     */
    inline virtual void Add(const Vector &Vec)
    {
        assert(MatchDim(Vec));
        CalculateObj->Add(data, Vec.GetData(), dim, data);
    }
    inline Vector operator+(const Vector &Vec) const
    {
        Vector temp(dim,data);
        temp.Add(Vec);
        return (temp);
    }

    /**
     * \brief 减去向量Vec(维数需一致)
     * \param 相减的向量
     */
    inline virtual void Sub(const Vector &Vec)
    {
        assert(MatchDim(Vec));
        CalculateObj->Sub(data, Vec.GetData(), dim, data);
    }
    inline Vector operator-(const Vector &Vec) const
    {
        Vector temp(dim,data);
        temp.Sub(Vec);
        return (temp);
    }


    /**
     * \brief 向量元素积
     * \param 与之相乘的向量
     */
    virtual void Product(const Vector &Vec);
    /**
     * \brief 向量内积
     * \param Vec 计算内积的向量
     */
    virtual F32 ProductInner(const Vector &Vec) const;

    inline F32 operator*(const Vector &Vec)
    {
        return this->ProductInner(Vec);
    }

    /**
     * \brief 向量外积
     * \param Vec 相乘的向量
     * \param VecResult 结果
     */
    virtual void ProductOuter(const Vector &Vec, Vector &VecResult) const;
private:
    F32 *data;
    S32 dim;
    BOOL localData;
};

} // namespace itr_math
#endif // VECTOR_H_
