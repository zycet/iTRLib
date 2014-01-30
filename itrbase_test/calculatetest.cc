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
 * calculatetest.cc
 *  Created on: 2013年9月22日
 *      Author: ZYC
 */

#include "calculatetest.h"

CalculateTest::CalculateTest()
{
    // TODO Auto-generated constructor stub

}

CalculateTest::~CalculateTest()
{
    // TODO Auto-generated destructor stub
}

void CalculateTest::Add(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + SourceB[i];
    }
}

void CalculateTest::Add(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + SourceB[i];
    }
    PRINT_DEBUG("CalculateTest::Add");
}

void CalculateTest::Sub(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] - SourceB[i];
    }
}

void CalculateTest::Sub(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] - SourceB[i];
    }
}

void CalculateTest::Multi(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * SourceB[i];
    }
}

void CalculateTest::Multi(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * SourceB[i];
    }
}

void CalculateTest::Div(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] / SourceB[i];
    }
}

void CalculateTest::Div(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] / SourceB[i];
    }
}

void CalculateTest::Offset(S32* SourceA, S32 Offset, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + Offset;
    }
}

void CalculateTest::Offset(F32* SourceA, F32 Offset, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + Offset;
    }
}

void CalculateTest::Scale(S32* SourceA, S32 Scale, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * Scale;
    }
}

void CalculateTest::Scale(F32* SourceA, F32 Scale, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * Scale;
    }
}

void CalculateTest::Normalization(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32 temp = 0;
    for (S32 i = 0; i < Length; i++)
    {
        temp += SourceA[i] * SourceA[i];
    }
    //temp = 1 / numericalObj->Sqrt(temp, temp);
    for (int i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * temp;
    }
}

void CalculateTest::Normalization(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32 temp = 0;
    for (S32 i = 0; i < Length; i++)
    {
        temp += SourceA[i] * SourceA[i];
    }
    //temp = 1 / numericalObj->Sqrt(temp, temp);
    Scale(SourceA, temp, Length, Result);
}

void CalculateTest::Abs(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        (SourceA[i] >= 0) ? Result[i] = SourceA[i] : Result[i] = -1 * SourceA[i];

    }
}

void CalculateTest::Abs(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        (SourceA[i] >= 0) ? Result[i] = SourceA[i] : Result[i] = -1 * SourceA[i];
    }
}

void CalculateTest::Opposite(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = -1 * SourceA[i];
    }
}

void CalculateTest::Opposite(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = -1 * SourceA[i];
    }
}

void CalculateTest::AddSum(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i];
    }
}

void CalculateTest::AddSum(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i];
    }
}

void CalculateTest::MultiSum(S32* SourceA, S32* SourceB, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i] * SourceB[i];
    }
}

void CalculateTest::MultiSum(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i] * SourceB[i];
    }
}

void CalculateTest::Product(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result *= SourceA[i];
    }
}

void CalculateTest::Product(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result *= SourceA[i];
    }
}
//Product

void CalculateTest::Set(S32* SourceA, S32 Value, S32 Length) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        SourceA[i] = Value;
    }
}

void CalculateTest::Set(F32* SourceA, F32 Value, S32 Length) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        SourceA[i] = Value;
    }
}
void CalculateTest::Max(S16* SourceA, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] > Result)
        Result = SourceA[i];
    }
}

void CalculateTest::Max(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] > Result)
        Result = SourceA[i];
    }
}

void CalculateTest::Max(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] > Result)
        Result = SourceA[i];
    }
}

void CalculateTest::Min(S16* SourceA, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] < Result)
        Result = SourceA[i];
    }
}

void CalculateTest::Min(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] < Result)
        Result = SourceA[i];
    }
}

void CalculateTest::Min(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] < Result)
        Result = SourceA[i];
    }
}

