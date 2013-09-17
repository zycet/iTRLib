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
            virtual bool Sin(F32 Source, F32& Result);
            virtual bool Cos(F32 Source, F32& Result);
            virtual bool SinCos(F32 Source, F32& ResultSin, F32& ResultCos);
            virtual bool Tan(F32 Source, F32& Result);
            virtual bool Asin(F32 Source, F32& Result);
            virtual bool Acos(F32 Source, F32& Result);
            virtual bool Atan(F32 Source, F32& Result);
            virtual bool Atan2(F32 SourceA, F32 SourceB, F32& Result);
            virtual bool Sqrt(F32 Source, F32& Result);
            virtual bool InvSqrt(F32 Source, F32& Result);
            virtual bool Exp(F32 Source, F32& Result);
            virtual bool Log(F32 Source, F32& Result);
            virtual bool Log10(F32 Source, F32& Result);
            virtual bool Pow(F32 SourceA, F32 SourceB, F32& Result);
            virtual bool Floor(F32 Source, F32& Result);
            virtual bool Mod(S32 SourceA, S32 SourceB, S32& Result);
    };
}

#endif // NUMERICAL_H_
