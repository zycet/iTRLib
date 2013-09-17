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
 * calculate.cc
 *  Created on: 2013��9��9��
 *      Author: ZYC
 */

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
    Calculate::Calculate(Numerical* numericalObj)
    {
        this->numericalObj = numericalObj;
    }

    Calculate::~Calculate()
    {
    }

    void Calculate::Add(S32* SourceA, S32* SourceB, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + SourceB[i];
        }
    }

    void Calculate::Add(F32* SourceA, F32* SourceB, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + SourceB[i];
        }
    }

    void Calculate::Sub(S32* SourceA, S32* SourceB, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] - SourceB[i];
        }
    }

    void Calculate::Sub(F32* SourceA, F32* SourceB, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] - SourceB[i];
        }
    }

    void Calculate::Multi(S32* SourceA, S32* SourceB, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * SourceB[i];
        }
    }

    void Calculate::Multi(F32* SourceA, F32* SourceB, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * SourceB[i];
        }
    }

    void Calculate::Div(S32* SourceA, S32* SourceB, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] / SourceB[i];
        }
    }

    void Calculate::Div(F32* SourceA, F32* SourceB, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] / SourceB[i];
        }
    }

    void Calculate::Offset(S32* SourceA, S32 Offset, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + Offset;
        }
    }

    void Calculate::Offset(F32* SourceA, F32 Offset, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] + Offset;
        }
    }

    void Calculate::Scale(S32* SourceA, S32 Scale, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * Scale;
        }
    }

    void Calculate::Scale(F32* SourceA, F32 Scale, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * Scale;
        }
    }

    void Calculate::Normalization(S32* SourceA, S32 Length, S32* Result)
    {
        F32 temp = 0;
        for (S32 i = 0; i < Length; i++)
        {
            temp += SourceA[i] * SourceA[i];
        }
        temp = 1 / numericalObj->Sqrt(temp, temp);
        for (int i = 0; i < Length; i++)
        {
            Result[i] = SourceA[i] * temp;
        }
    }

    void Calculate::Normalization(F32* SourceA, S32 Length, F32* Result)
    {
        F32 temp = 0;
        for (S32 i = 0; i < Length; i++)
        {
            temp += SourceA[i] * SourceA[i];
        }
        temp = 1 / numericalObj->Sqrt(temp, temp);
        Scale(SourceA, temp, Length, Result);
    }

    void Calculate::Abs(S32* SourceA, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            (SourceA[i] >= 0) ? Result[i] = SourceA[i] : Result[i] = -1 * SourceA[i];

        }
    }

    void Calculate::Abs(F32* SourceA, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            (SourceA[i] >= 0) ? Result[i] = SourceA[i] : Result[i] = -1 * SourceA[i];
        }
    }

    void Calculate::Opposite(S32* SourceA, S32 Length, S32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = -1 * SourceA[i];
        }
    }

    void Calculate::Opposite(F32* SourceA, S32 Length, F32* Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result[i] = -1 * SourceA[i];
        }
    }

    void Calculate::Sum(S32* SourceA, S32 Length, S32& Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result += SourceA[i];
        }
    }

    void Calculate::Sum(F32* SourceA, S32 Length, F32& Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result += SourceA[i];
        }
    }
    void Calculate::Product(S32* SourceA, S32 Length, S32& Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result *= SourceA[i];
        }
    }

    void Calculate::Product(F32* SourceA, S32 Length, F32& Result)
    {
        for (S32 i = 0; i < Length; i++)
        {
            Result *= SourceA[i];
        }
    }
} // namespace itr_math
