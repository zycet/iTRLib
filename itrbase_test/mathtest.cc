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

itr_math::Numerical* NumericalObj;
itr_math::Calculate* CalculateObj;
itr_math::Statistics* StatisticsObj;

void TestMathInit()
{
    NumericalObj=new itr_math::Numerical();
    itr_math::Calculate::SetNumericalObj(NumericalObj);
    CalculateObj=new itr_math::Calculate();
    itr_math::Statistics::SetNumericalObj(NumericalObj);
    itr_math::Statistics::SetCalculateObj(CalculateObj);
    StatisticsObj=new itr_math::Statistics();
    itr_math::Vector::SetCalculateObj(CalculateObj);
    itr_math::Matrix::SetNumericalObj(NumericalObj);
    itr_math::Matrix::SetCalculateObj(CalculateObj);
}

void TestMathdeDeinit()
{
    delete NumericalObj;
    delete CalculateObj;
    delete StatisticsObj;
}

void TestCalculate()
{
    //Data
    S32 SourceS32A[50];
    S32 SourceS32B[50];
    S32 ResultS32[50];
    F32 SourceF32A[50];
    F32 SourceF32B[50];
    F32 ResultF32A[50];
    F32 ResultF32;
    S32 Length = 50;
    S32 AddAns = 2450;
    F32 AddAnsF = 245.0;
    //Init
    for (S32 i = 0; i < Length; i++)
    {
        SourceS32A[i] = i;
        SourceS32B[i] = i;
        SourceF32A[i] = i;
        SourceF32A[i] = i;
    }
    //Add
    CalculateObj->Add(SourceF32A, SourceF32B, Length, ResultF32A);
    CalculateObj->AddSum(ResultF32A, Length, ResultF32);
    assert(ResultF32 == 2450);
    //Sub...

    TRACE_INFO("OK TestCalculate()");
}

void TestNumerical()
{

}

void TestStatistics()
{

}

void TestVector()
{
    //itr_math::Vector v(3);
}

void TestCalculateTest()
{
    F32 A[]={1,1};
    F32 B[]={2,2};
    F32 C[]={0,0};
    CalculateTest calcObjT;
    itr_math::Calculate* calcObj=&calcObjT;
    calcObj->Add(A,B,2,C);

//    itr_math::Calculate calcObj=CalculateTest();
//    calcObj.Add(A,B,2,C);
}
