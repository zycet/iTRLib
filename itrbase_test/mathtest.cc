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
 * math_test.cc
 *  Created on: 2013年9月17日
 *      Author: ZYC
 */

#include "mathtest.h"
#include "calculatetest.h"
#include "itrbase.h"
#include "math.h"
#include "stdio.h"

void TestMathInit()
{
    itr_math::MathObjStandInit();
}

void TestMathdeDeinit()
{
    itr_math::MathObjStandDeinit();
}

void TestCalculate()
{
    /*
    //Data
    S16 SourceS16Arr_A[50];
    S16 SourceS16Arr_B[50];
    S32 ResultS16Arr[50];

    S32 SourceS32Arr_A[50];
    S32 SourceS32Arr_B[50];
    S32 ResultS32Arr[50];

    F32 SourceF32Arr_A[50];
    F32 SourceF32Arr_B[50];
    F32 SourceF32Arr_C[50];
    F32 SourceF32Arr_D[50];
    F32 SourceF32Arr_E[50];
    F32 SourceF32Arr_F[50];
    F32 ResultF32Arr_A[50];
    F32 ResultF32Arr_B[50];

    F32 CalResultF32;
    S32 CalResultS32;
    F32 CalResutlS16;
    S32 Length = 50;
    S32 AddAns = 2450;
    F32 AddAnsF = 245.0;
    //Init
    for (S32 i = 0; i < Length; i++)
    {
        SourceS32Arr_A[i] = i;
        SourceS32Arr_B[i] = i;
        SourceF32Arr_A[i] = i;
        SourceF32Arr_B[i] = 0;
        SourceF32Arr_C[i] = 0;
        SourceF32Arr_D[i] = i;
        SourceF32Arr_E[i] = -i;
        SourceF32Arr_F[i] = 1;
    }
    //Add
    itr_math::CalculateObj->Add(SourceS16Arr_A,SourceS16Arr_B,Length,CalResutlS16);
    itr_math::CalculateObj->Add(SourceS32Arr_A, SourceS32Arr_B, Length, CalResultS32);
    itr_math::CalculateObj->Add(SourceF32Arr_A, SourceF32Arr_B, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32 == 1225);
    //Sub...
    itr_math::CalculateObj->Sub(SourceF32A, SourceF32B, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32==0);
    //MUlti
    itr_math::CalculateObj->Multi(SourceF32A, SourceF32C, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32==0);
    //Div
    itr_math::CalculateObj->Div(SourceF32C, SourceF32A, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32==0);
    //offset
    itr_math::CalculateObj->Offset(SourceF32C, 2, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32==100);
    //Scale
    itr_math::CalculateObj->Scale(SourceF32A, 2, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32==2450);
    //Normalization
    itr_math::CalculateObj->Normalization(SourceF32C, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32==0);
    //Abs
    itr_math::CalculateObj->Abs(SourceF32E, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32==-1250);
    //Oppsite
    itr_math::CalculateObj->Opposite(SourceF32E, Length, ResultF32A);
    itr_math::CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32==1250);
    //Addsum
    itr_math::CalculateObj->AddSum(SourceF32D, Length, ResultF32);
    assert(ResultF32==1250);
    //MultiSum
    itr_math::CalculateObj->MultiSum(SourceF32C, SourceF32D, Length, ResultF32);
    assert(ResultF32==0);
    //Product
    itr_math::CalculateObj->Product(SourceF32F, Length, ResultF32);
    assert(ResultF32==1);
    //Set
    itr_math::CalculateObj->Set(SourceF32D, 1, Length);
    assert(ResultF32==50);
    TRACE_INFO("OK TestCalculate()");
    */
}

void TestNumerical()
{

}

void TestStatistics()
{
    S32 SourceS32[50];
    F32 SourceF32[50];
    S32 ResultS32;
    F32 ResultF32;
    S32 Length = 50;
    for (S32 i = 0; i < Length; i++)
    {
        SourceS32[i] = i;
        SourceF32[i] = i;
    }
    itr_math::StatisticsObj->Max(SourceS32, Length, ResultS32);
    assert(ResultS32 == 49);
    itr_math::StatisticsObj->Min(SourceS32, Length, ResultS32);
    assert(ResultS32 == 0);
    itr_math::StatisticsObj->Mean(SourceS32, Length, ResultS32);
    assert(ResultS32 == 24);
    itr_math::StatisticsObj->RMS(SourceS32, Length, ResultS32);
    assert(ResultS32 == 28);
    itr_math::StatisticsObj->STD(SourceS32, Length, ResultS32);
    assert(ResultS32 == 14);
}

void TestVector()
{
    //itr_math::Vector v(3);
    //F32 vector(2, 0x1111, 1);
    //CopyFrom
}

void TestMatrix()
{
    //测试数据
    F32 data[3 * 3];
    for (S32 i = 0; i < 3 * 3; i++)
    {
        data[i] = i * i;
    }
    F32* Data = data;
    itr_math::Matrix Source1(3, 3, Data);
    itr_math::Matrix Source2(3, 3, Data);
    itr_math::Matrix Result1(3, 3, Data);
    itr_math::Matrix Result2(3, 3, Data);
    //初等变换
    Source1.AddRow(1, 2);
    Source1.SubRow(1, 2);
    assert(
            MemoryCompare(Source1.GetData(),Source2.GetData(),sizeof(F32)*Source1.GetRow()*Source1.GetCol())==true);
    Source1.AddRow(Source1.GetData(), 2);
    Source1.SubRow(Source1.GetData(), 2);
    assert(
            MemoryCompare(Source1.GetData(),Source2.GetData(),sizeof(F32)*Source1.GetRow()*Source1.GetCol())==true);
    //求逆测试

    Source1.Inv(Result1);
    //Result.Mul(Source, Result2);
    for (S32 i = 0; i < 3 * 3; i++)
    {
        if (i % 3 == 0)
            printf("\n");
        printf("%f ", Result1[i]);
    }
}
void TestCalculateTest()
{
    F32 A[] =
    { 1, 1 };
    F32 B[] =
    { 2, 2 };
    F32 C[] =
    { 0, 0 };
    CalculateTest calcObjT;
    itr_math::Calculate* calcObj = &calcObjT;
    calcObj->Add(A, B, 2, C);

//    itr_math::Calculate calcObj=CalculateTest();
//    calcObj.Add(A,B,2,C);
}
