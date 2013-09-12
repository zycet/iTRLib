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
 *  Created on: 2013年9月9日
 *      Author: ZYC
 */

#include "numerical.h"
#include <math.h>

Numerical::Numerical()
{
    // TODO Auto-generated constructor stub
}

Numerical::~Numerical()
{
    // TODO Auto-generated destructor stub
}

bool Numerical::Sin(F32 Source, F32& Result)
{
    Result = sin(Source);
    return true;
}

bool Numerical::Cos(F32 Source, F32& Result)
{
    Result = sin(Source);
    return true;
}

bool Numerical::SinCos(F32 Source, F32& ResultSin, F32& ResultCos)
{
    ResultSin = sin(Source);
    ResultCos = cos(Source);
    return true;
}

bool Numerical::Tan(F32 Source, F32& Result)
{
    Result = tan(Source);
    return true;
}

bool Numerical::Asin(F32 Source, F32& Result)
{
    Result = asin(Source);
    return true;
}

bool Numerical::Acos(F32 Source, F32& Result)
{
    Result = acos(Source);
    return true;
}

bool Numerical::Atan(F32 Source, F32& Result)
{
    Result = atan(Source);
    return true;
}

bool Numerical::Atan2(F32 SourceA, F32 SourceB, F32& Result)
{
    Result = atan2(SourceA, SourceB);
    return true;
}

bool Numerical::Sqrt(F32 Source, F32& Result)
{
    Result = sqrt(Source);
    return true;
}

bool Numerical::InvSqrt(F32 Source, F32& Result)
{
    Result = sqrt(Source);
    Result = 1 / Result;
    return true;
}

bool Numerical::Exp(F32 Source, F32& Result)
{
    Result = exp(Source);
    return true;
}

bool Numerical::Log(F32 Source, F32& Result)
{
    Result = log(Source);
    return true;
}

bool Numerical::Log10(F32 Source, F32& Result)
{
    Result = log10(Source);
    return true;
}

bool Numerical::Pow(F32 SourceA, F32 SourceB, F32& Result)
{
    Result = pow(SourceA, SourceB);
    return true;
}
bool Numerical::Floor(F32 Source, F32& Result)
{
    Result = floor(Source);
    return true;
}
bool Numerical::Mod(S32 SourceA, S32 SourceB, S32& Result)
{
    Result = SourceA % SourceB;
    return true;
}
