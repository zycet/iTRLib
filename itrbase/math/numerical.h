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
 * numerical.h
 *  Created on: 2013年9月9日
 *      Author: ZYC
 */

#ifndef NUMERICAL_H_
#define NUMERICAL_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
class Numerical
{
public:

    Numerical();
    virtual ~Numerical();
    /**
    * \brief 求正弦值
    * \param Source 输入
    * \param Result 结果
    */
    virtual BOOL Sin(F32 Source, F32& Result) const;
    /**
    * \brief 求余弦值
    * \param Source 输入
    * \param Result 结果
    */
    virtual BOOL Cos(F32 Source, F32& Result) const;
    /**
    * \brief 求正弦值和余弦值
    * \param Source 输入
    * \param ResultSin 正弦结果
    * \param ResultCos 余弦结果
    */
    virtual BOOL SinCos(F32 Source, F32& ResultSin, F32& ResultCos) const;
    /**
    * \brief 求正切值
    * \param Source 输入
    * \param Result 结果
    */
    virtual BOOL Tan(F32 Source, F32& Result) const;
    /**
    * \brief 求反正弦值
    * \param Source 输入
    * \param Result 结果
    */
    virtual BOOL Asin(F32 Source, F32& Result) const;
    /**
    * \brief 求反余弦值
    * \param Source 输入
    * \param Result 结果
    */
    virtual BOOL Acos(F32 Source, F32& Result) const;
    /**
    * \brief 求反正切值
    * \param Source 输入
    * \param Result 结果
    */
    virtual BOOL Atan(F32 Source, F32& Result) const;
    /**
    * \brief 求反正切值
    * \param SourceA 输入A
    * \param SourceB 输入B
    * \param Result 结果
    */
    virtual BOOL Atan2(F32 SourceA, F32 SourceB, F32& Result) const;
    /**
    * \brief 求开方值
    * \param Source 输入
    * \param Result 结果
    */
    virtual BOOL Sqrt(F32 Source, F32& Result) const;
    /**
    * \brief 求开方值的倒数
    * \param Source 输入
    * \param Result 结果
    */
    virtual BOOL InvSqrt(F32 Source, F32& Result) const;
    virtual BOOL Exp(F32 Source, F32& Result) const;
    virtual BOOL Log(F32 Source, F32& Result) const;
    virtual BOOL Log10(F32 Source, F32& Result) const;
    virtual BOOL Pow(F32 SourceA, F32 SourceB, F32& Result) const;
    virtual BOOL Floor(F32 Source, S32& Result) const;
    virtual BOOL Ceil(F32 Source, S32& Result) const;
    virtual BOOL Round(F32 Source, S32& Result) const;
    virtual BOOL Mod(S32 SourceA, S32 SourceB, S32& Result) const;
    virtual BOOL Rand(F32& Result) const;
    virtual BOOL Rand(S32 low, S32 high, S32& Result) const;
    virtual BOOL RandGaussian(F32& Result) const;
    const static float Pi=3.1415926f;
};
}

#endif // NUMERICAL_H_
