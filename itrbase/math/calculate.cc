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
 *  Created on: 2013年9月9日
 *      Author: ZYC
 */

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{

Calculate::Calculate()
{
    assert(NumericalObj!=NULL);
}

Calculate::~Calculate()
{
}

void Calculate::Add(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const
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

void Calculate::Add(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
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

void Calculate::Add(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
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

void Calculate::Sub(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const
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

void Calculate::Sub(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
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

void Calculate::Sub(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
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

void Calculate::Multi(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const
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

void Calculate::Multi(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
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

void Calculate::Multi(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
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

void Calculate::Div(S16* SourceA, S16* SourceB, S32 Length, S16* Result) const
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

void Calculate::Div(S32* SourceA, S32* SourceB, S32 Length, S32* Result) const
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

void Calculate::Div(F32* SourceA, F32* SourceB, S32 Length, F32* Result) const
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

void Calculate::DivOrder(S16* SourceA, S32 DivOrder, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(DivOrder>=0);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] >> DivOrder;
    }
}

void Calculate::DivOrder(S32* SourceA, S32 DivOrder, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(DivOrder>=0);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] >> DivOrder;
    }
}

void Calculate::Offset(S16* SourceA, S16 Offset, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + Offset;
    }
}

void Calculate::Offset(S32* SourceA, S32 Offset, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + Offset;
    }
}

void Calculate::Offset(F32* SourceA, F32 Offset, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] + Offset;
    }
}

void Calculate::Scale(S16* SourceA, S16 Scale, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * Scale;
    }
}

void Calculate::Scale(S32* SourceA, S32 Scale, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * Scale;
    }
}

void Calculate::Scale(F32* SourceA, F32 Scale, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * Scale;
    }
}

void Calculate::Normalization(S16* SourceA, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32 temp = 0;
    for (S32 i = 0; i < Length; i++)
    {
        temp += SourceA[i] * SourceA[i];
    }
    NumericalObj->Sqrt(temp, temp);
    temp = 1 / temp;
    for (int i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * temp;
    }
}

void Calculate::Normalization(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32 temp = 0;
    for (S32 i = 0; i < Length; i++)
    {
        temp += SourceA[i] * SourceA[i];
    }
    NumericalObj->Sqrt(temp, temp);
    temp = 1 / temp;
    for (int i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * temp;
    }
}

void Calculate::Normalization(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    F32 temp = 0;
    for (S32 i = 0; i < Length; i++)
    {
        temp += SourceA[i] * SourceA[i];
    }
    NumericalObj->Sqrt(temp, temp);
    temp = 1 / temp;
    for (int i = 0; i < Length; i++)
    {
        Result[i] = SourceA[i] * temp;
    }
}

void Calculate::Abs(S16* SourceA, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = GET_ABS(SourceA[i]);
    }
}

void Calculate::Abs(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = GET_ABS(SourceA[i]);
    }
}

void Calculate::Abs(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = GET_ABS(SourceA[i]);
    }
}

void Calculate::Opposite(S16* SourceA, S32 Length, S16* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = -SourceA[i];
    }
}

void Calculate::Opposite(S32* SourceA, S32 Length, S32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = -SourceA[i];
    }
}

void Calculate::Opposite(F32* SourceA, S32 Length, F32* Result) const
{
    assert(SourceA!=NULL);
    assert(Result!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        Result[i] = -SourceA[i];
    }
}

void Calculate::AddSum(S16* SourceA, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i];
    }
}

void Calculate::AddSum(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i];
    }
}

void Calculate::AddSum(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        Result += SourceA[i];
    }
}

void Calculate::MultiSum(S16* SourceA, S16* SourceB, S32 Length, S16& Result) const
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

void Calculate::MultiSum(S16* SourceA, F32* SourceB, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    F32 value = 0;
    Result = 0;
    for (S32 i = 0; i < Length; i++)
    {
        value += SourceA[i] * SourceB[i];
    }
    Result = value;
}

void Calculate::MultiSum(S32* SourceA, S32* SourceB, S32 Length, S32& Result) const
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

void Calculate::MultiSum(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const
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

void Calculate::Product(S16* SourceA, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 1;
    for (S32 i = 0; i < Length; i++)
    {
        Result *= SourceA[i];
    }
}

void Calculate::Product(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 1;
    for (S32 i = 0; i < Length; i++)
    {
        Result *= SourceA[i];
    }
}

void Calculate::Product(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = 1;
    for (S32 i = 0; i < Length; i++)
    {
        Result *= SourceA[i];
    }
}

void Calculate::Set(S16* SourceA, S16 Value, S32 Length) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        SourceA[i] = Value;
    }
}

void Calculate::Set(S32* SourceA, S32 Value, S32 Length) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        SourceA[i] = Value;
    }
}

void Calculate::Set(F32* SourceA, F32 Value, S32 Length) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    for (S32 i = 0; i < Length; i++)
    {
        SourceA[i] = Value;
    }
}

void Calculate::Compare(F32* SourceA, F32* SourceB, F32 Error,S32 Length,BOOL* IsSame) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    assert(Error > 0);
    (*IsSame)=true;
    F32 error;
    for (S32 i = 0; i < Length; i++)
    {
        error=SourceA[i]-SourceB[i];
        if(error>Error||error<-Error)
        {
            (*IsSame)=false;
            return;
        }
    }
}

void Calculate::Max(S16* SourceA, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] > Result)
        {
            Result = SourceA[i];
        }
    }
}

void Calculate::Max(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] > Result)
        {
            Result = SourceA[i];
        }
    }
}

void Calculate::Max(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] > Result)
        {
            Result = SourceA[i];
        }
    }
}
void Calculate::Max(F32* SourceA, S32 Length, F32& Result,S32 &Order) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    Order=0;
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] > Result)
        {
            Result = SourceA[i];
            Order=i;
        }
    }
}

void Calculate::Min(S16* SourceA, S32 Length, S16& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] < Result)
        {
            Result = SourceA[i];
        }
    }
}

void Calculate::Min(S32* SourceA, S32 Length, S32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] < Result)
        {
            Result = SourceA[i];
        }
    }
}
void Calculate::Min(F32* SourceA, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] < Result)
        {
            Result = SourceA[i];
        }
    }
}
void Calculate::Min(F32* SourceA, S32 Length, F32& Result, S32& Order) const
{
    assert(SourceA!=NULL);
    assert(Length > 0);
    Result = SourceA[0];
    Order =0;
    for (S32 i = 1; i < Length; i++)
    {
        if(SourceA[i] < Result)
        {
            Result = SourceA[i];
            Order =i;
        }
    }
}

void Calculate::Single_dis(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    Result =0;
   for (S32 i = 0; i < Length; i++)
    {
        Result+= GET_ABS(SourceA[i]-SourceB[i]);
    }
}
void Calculate::Double_dis(F32* SourceA, F32* SourceB, S32 Length, F32& Result) const
{
    assert(SourceA!=NULL);
    assert(SourceB!=NULL);
    assert(Length > 0);
    Result =0;
   for (S32 i = 0; i < Length; i++)
    {
        Result+= (SourceA[i]-SourceB[i])*(SourceA[i]-SourceB[i]);
    }
}
} // namespace itr_math
