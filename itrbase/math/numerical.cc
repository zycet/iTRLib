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
 * numerical.cc
 *  Created on: 2013骞�鏈�鏃�
 *      Author: ZYC
 */

#include "../platform/platform.h"
#include "math.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
namespace itr_math
{
Numerical::Numerical()
{
    // TODO Auto-generated constructor stub
    srand(time(0));
}

Numerical::~Numerical()
{
    // TODO Auto-generated destructor stub
}

BOOL Numerical::Sin(F32 Source, F32& Result) const
{
    Result = sin(Source);
    return true;
}

BOOL Numerical::Cos(F32 Source, F32& Result) const
{
    Result = sin(Source);
    return true;
}

BOOL Numerical::SinCos(F32 Source, F32& ResultSin, F32& ResultCos) const
{
    ResultSin = sin(Source);
    ResultCos = cos(Source);
    return true;
}

BOOL Numerical::Tan(F32 Source, F32& Result) const
{
    Result = tan(Source);
    return true;
}

BOOL Numerical::Asin(F32 Source, F32& Result) const
{
    Result = asin(Source);
    return true;
}

BOOL Numerical::Acos(F32 Source, F32& Result) const
{
    Result = acos(Source);
    return true;
}

BOOL Numerical::Atan(F32 Source, F32& Result) const
{
    Result = atan(Source);
    return true;
}

BOOL Numerical::Atan2(F32 SourceA, F32 SourceB, F32& Result) const
{
    Result = atan2(SourceA, SourceB);
    return true;
}

BOOL Numerical::Sqrt(F32 Source, F32& Result) const
{
    Result = sqrt(Source);
    return true;
}

BOOL Numerical::InvSqrt(F32 Source, F32& Result) const
{
    Result = sqrt(Source);
    Result = 1 / Result;
    return true;
}

BOOL Numerical::Exp(F32 Source, F32& Result) const
{
    Result = exp(Source);
    return true;
}

BOOL Numerical::Log(F32 Source, F32& Result) const
{
    Result = log(Source);
    return true;
}

BOOL Numerical::Log10(F32 Source, F32& Result) const
{
    Result = log10(Source);
    return true;
}

BOOL Numerical::Pow(F32 SourceA, F32 SourceB, F32& Result) const
{
    Result = pow(SourceA, SourceB);
    return true;
}

BOOL Numerical::Floor(F32 Source, S32& Result) const
{
    Result = floor(Source);
    return true;
}

BOOL Numerical::Ceil(F32 Source, S32& Result) const
{
    Result = ceil(Source);
    return true;
}

BOOL Numerical::Round(F32 Source, S32& Result) const
{
    Result = round(Source);
    return true;
}

BOOL Numerical::Mod(S32 SourceA, S32 SourceB, S32& Result) const
{
    Result = SourceA % SourceB;
    return true;
}

BOOL Numerical::Rand(F32& Result) const
{
    Result = rand() % 1000000 / 1000000.0;
    return true;
}

BOOL Numerical::Rand(S32 low, S32 high, S32& Result) const
{
    Result = rand() % (high - low) + low;
    return true;
}

BOOL Numerical::RandGaussian(F32 mid, F32& Result) const
{
    float r1, r2;
    float R,log,cos;
    Log(r1,log);
    Cos(2 *Pi * r2,cos);
    Rand(r1);
    Rand(r2);
    Sqrt(-2*log,R);
    Result=R*cos;
    return true;
}
}

