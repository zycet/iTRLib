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
#include <time.h>
#include <stdlib.h>

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
    //Init
    itr_math::MathObjStandInit();
    //Test Data
    S16 A_S16[] =
    { 2, 2 };
    S16 B_S16[] =
    { 1, 1 };
    S16 C_S16[] =
    { 0, 0 };

    S32 A_S32[] =
    { 2, 2 };
    S32 B_S32[] =
    { 1, 1 };
    S32 C_S32[] =
    { 0, 0 };

    F32 A_F32[] =
    { 2, 2 };
    F32 B_F32[] =
    { 1, 1 };
    F32 C_F32[] =
    { 0, 0 };

    F32 CalResultF32;
    S32 CalResultS32;
    S16 CalResutlS16;

    //AddTest
    itr_math::CalculateObj->Add(A_S16, B_S16, 2, C_S16);
    assert(C_S16[0] == A_S16[0] + B_S16[0] && C_S16[1] == A_S16[1] + B_S16[1]);
    itr_math::CalculateObj->Add(A_S32, B_S32, 2, C_S32);
    assert(C_S32[0] == A_S32[0] + B_S32[0] && C_S32[1] == A_S32[1] + B_S32[1]);
    itr_math::CalculateObj->Add(A_F32, B_F32, 2, C_F32);
    assert(C_F32[0] == A_F32[0] + B_F32[0] && C_F32[1] == A_F32[1] + B_S32[1]);
    //SubTest
    itr_math::CalculateObj->Sub(A_S16, B_S16, 2, C_S16);
    assert(C_S16[0] == A_S16[0] - B_S16[0] && C_S16[1] == A_S16[1] - B_S16[1]);
    itr_math::CalculateObj->Sub(A_S32, B_S32, 2, C_S32);
    assert(C_S32[0] == A_S32[0] - B_S32[0] && C_S32[1] == A_S32[1] - B_S32[1]);
    itr_math::CalculateObj->Sub(A_F32, B_F32, 2, C_F32);
    assert(C_F32[0] == A_F32[0] - B_F32[0] && C_F32[1] == A_F32[1] - B_S32[1]);
    //MultiTest
    itr_math::CalculateObj->Multi(A_S16, B_S16, 2, C_S16);
    assert(C_S16[0] == A_S16[0] * B_S16[0] && C_S16[1] == A_S16[1] * B_S16[1]);
    itr_math::CalculateObj->Multi(A_S32, B_S32, 2, C_S32);
    assert(C_S32[0] == A_S32[0] * B_S32[0] && C_S32[1] == A_S32[1] * B_S32[1]);
    itr_math::CalculateObj->Multi(A_F32, B_F32, 2, C_F32);
    assert(C_F32[0] == A_F32[0] * B_F32[0] && C_F32[1] == A_F32[1] * B_S32[1]);
    //DivTest
    itr_math::CalculateObj->Div(A_S16, B_S16, 2, C_S16);
    assert(C_S16[0] == A_S16[0] / B_S16[0] && C_S16[1] == A_S16[1] / B_S16[1]);
    itr_math::CalculateObj->Div(A_S32, B_S32, 2, C_S32);
    assert(C_S32[0] == A_S32[0] / B_S32[0] && C_S32[1] == A_S32[1] / B_S32[1]);
    itr_math::CalculateObj->Div(A_F32, B_F32, 2, C_F32);
    assert(C_F32[0] == A_F32[0] / B_F32[0] && C_F32[1] == A_F32[1] / B_S32[1]);
    //DivOrderTest
    itr_math::CalculateObj->DivOrder(A_S16, 1, 2, C_S16);
    assert(C_S16[0] == A_S16[0] / 2 && C_S16[1] == A_S16[1] / 2);
    itr_math::CalculateObj->DivOrder(A_S32, 1, 2, C_S32);
    assert(C_S32[0] == A_S32[0] / 2 && C_S32[1] == A_S32[1] / 2);
    //OffsetTest
    itr_math::CalculateObj->Offset(A_S16, 2, 2, C_S16);
    assert(C_S16[0] == A_S16[0] + 2 && C_S16[1] == A_S16[1] + 2);
    itr_math::CalculateObj->Offset(A_S32, 2, 2, C_S32);
    assert(C_S32[0] == A_S32[0] + 2 && C_S32[1] == A_S32[1] + 2);
    itr_math::CalculateObj->Offset(A_F32, 2, 2, C_F32);
    assert(C_F32[0] == A_F32[0] + 2 && C_F32[1] == A_F32[1] + 2);
    //ScaleTest
    itr_math::CalculateObj->Scale(A_S16, 2, 2, C_S16);
    assert(C_S16[0] == A_S16[0] * 2 && C_S16[1] == A_S16[1] * 2);
    itr_math::CalculateObj->Scale(A_S32, 2, 2, C_S32);
    assert(C_S32[0] == A_S32[0] * 2 && C_S32[1] == A_S32[1] * 2);
    itr_math::CalculateObj->Scale(A_F32, 2, 2, C_F32);
    assert(C_F32[0] == A_F32[0] * 2 && C_F32[1] == A_F32[1] * 2);
    //NormalizationTest
    itr_math::CalculateObj->Normalization(A_F32, 2, C_F32);
    assert(C_F32[0] * C_F32[0] + C_F32[1] * C_F32[1] - 1 < 0.0001);
    //AbsTest
    itr_math::CalculateObj->Abs(A_S16, 2, C_S16);
    assert(fabs(A_S16[0]) == C_S16[0] && fabs(A_S16[1]) == C_S16[1]);
    itr_math::CalculateObj->Abs(A_S32, 2, C_S32);
    assert(fabs(A_S32[0]) == C_S32[0] && fabs(A_S32[1]) == C_S32[1]);
    itr_math::CalculateObj->Abs(A_F32, 2, C_F32);
    assert(fabs(A_F32[0]) == C_F32[0] && fabs(A_F32[1]) == C_F32[1]);
    //OppositeTest
    itr_math::CalculateObj->Opposite(A_S16, 2, C_S16);
    assert(A_S16[0] * (-1) == C_S16[0] && A_S16[1] * (-1) == C_S16[1]);
    itr_math::CalculateObj->Opposite(A_S32, 2, C_S32);
    assert(A_S32[0] * (-1) == C_S32[0] && A_S32[1] * (-1) == C_S32[1]);
    itr_math::CalculateObj->Opposite(A_F32, 2, C_F32);
    assert(A_F32[0] * (-1) == C_F32[0] && A_F32[1] * (-1) == C_F32[1]);
    //AddSumTest
    itr_math::CalculateObj->AddSum(A_S16, 2, CalResutlS16);
    assert(CalResutlS16 == A_S16[0] + A_S16[1]);
    itr_math::CalculateObj->AddSum(A_S32, 2, CalResultS32);
    assert(CalResultS32 == A_S32[0] + A_S32[1]);
    itr_math::CalculateObj->AddSum(A_F32, 2, CalResultF32);
    assert(CalResutlS16 == A_S16[0] + A_S16[1]);
    //MultiSum
    itr_math::CalculateObj->MultiSum(A_S16, B_S16, 2, CalResutlS16);
    assert(CalResutlS16 == A_S16[0] * B_S16[0] + A_S16[1] * B_S16[1]);
    itr_math::CalculateObj->MultiSum(A_S16, B_F32, 2, CalResutlS16);
    assert(CalResutlS16 == A_S16[0] * B_F32[0] + A_S16[1] * B_F32[1]);
    itr_math::CalculateObj->MultiSum(A_S32, B_S32, 2, CalResultS32);
    assert(CalResultS32 == A_S32[0] * B_S32[0] + A_S32[1] * B_S32[1]);
    itr_math::CalculateObj->MultiSum(A_F32, B_F32, 2, CalResultF32);
    //ProductTest
    itr_math::CalculateObj->Product(A_S16, 2, CalResutlS16);
    assert(CalResutlS16 == A_S16[0] * A_S16[1]);
    itr_math::CalculateObj->Product(A_S32, 2, CalResultS32);
    assert(CalResultS32 == A_S32[0] * A_S32[1]);
    itr_math::CalculateObj->Product(A_F32, 2, CalResultF32);
    assert(CalResultF32 == A_F32[0] * A_F32[1]);
    //SetTest
    itr_math::CalculateObj->Set(C_S16, 2, 2);
    assert(C_S16[0] == 2 && C_S16[1] == 2);
    itr_math::CalculateObj->Set(C_S32, 2, 2);
    assert(C_S32[0] == 2 && C_S32[1] == 2);
    itr_math::CalculateObj->Set(C_F32, 2, 2);
    assert(C_F32[0] == 2 && C_F32[1] == 2);

    itr_math::CalculateObj->Max(A_F32, 2, CalResultF32);
    assert(CalResultF32 == 2);
    itr_math::CalculateObj->Min(A_F32, 2, CalResultF32);
    assert(CalResultF32 == 2);
    itr_math::CalculateObj->Single_dis(A_F32, B_F32,2, CalResultF32);
    assert(CalResultF32 == 2);
    itr_math::CalculateObj->Double_dis(A_F32, B_F32,2, CalResultF32);
    assert(CalResultF32 == 2);
    TRACE_INFO("OK TestCalculate()");
}

void TestNumerical()
{

}

void TestStatistics()
{
    S32 SourceS32[50];
    //F32 SourceF32[50];
    S32 ResultS32;
    //F32 ResultF32;
    S32 Length = 50;
    for (S32 i = 0; i < Length; i++)
    {
        SourceS32[i] = i;
        //SourceF32[i] = i;
    }
    itr_math::StatisticsObj->Max(SourceS32, Length, ResultS32);
    assert(ResultS32 == 49);
    itr_math::StatisticsObj->Min(SourceS32, Length, ResultS32);
    assert(ResultS32 == 0);
    itr_math::StatisticsObj->Mean(SourceS32, Length, ResultS32);
    assert(ResultS32 == 24);
    itr_math::StatisticsObj->RMS(SourceS32, Length, ResultS32);
    assert(ResultS32 == 28);
    itr_math::StatisticsObj->Variance(SourceS32, Length, ResultS32);
    assert(ResultS32 == 14);
}

void TestVector()
{
    S32 i;
    F32 *Data1, *Data2, ve1[3], ve2[3], resultF32;
    itr_math::Vector v(3);
    itr_math::Vector v2(3, ve2);
    for (i = 0; i < 3; i++)
    {
        ve1[i] = i * 1.0;
        ve2[i] = 5.0 + i;
    }
    Data1 = ve1;
    Data2 = ve2;
    v.CopyFrom(Data1);
    v.CopyTo(Data2);
    //test CopyTo and CopyFrom
    assert(*(Data2) == 0);
    assert(*(Data2 + 1) == 1);
    assert(*(Data2 + 2) == 2);
    //   F32 vector(2, 0x1111, 1);
    //test CopyTo and CopyFrom with offset
    ve2[0] = 5, ve2[1] = 6, ve2[2] = 7;
    v.CopyFrom(1, 2, ve2);
    v.CopyTo(1, 2, ve2);
    v.CopyTo(Data2);
    assert(*(Data2) == 0);
    assert(*(Data2 + 1) == 5);
    assert(*(Data2 + 2) == 6);

    v.Product(v);                   //test product;
    v.CopyTo(Data2);
    assert(*(Data2) == 0);
    assert(*(Data2 + 1) == 25);
    assert(*(Data2 + 2) == 36);

    v2.CopyFrom(Data1);//0 1 2
    resultF32 = v.ProductInner(v2);
    assert((97) == resultF32);

    ve2[0] = 5, ve2[1] = 6, ve2[2] = 7;
    ve1[0] = 1, ve2[1] = 2, ve2[2] = 3;
    v.CopyFrom(ve1);
    v2.CopyFrom(ve2);
    F32 ve3[3];
    Data2 = ve3;
    itr_math::Vector v3(3);
    v.ProductOuter(v2, v3);          //function "ProductOuter" err
    v3.CopyTo(Data2);
    //assert(*(Data2)==(-4));             //计算结果出错，找不到问题所在
    // assert(*(Data2+1) == 8 );
    //assert(*(Data2+2)==-4);
    TRACE_INFO("OK TestVector()");
}

void printMatrix(itr_math::Matrix a)
{
    printf("The Matrix is:\n");
    for (int i = 0; i < a.GetRow(); ++i)
    {
        for (int j = 0; j < a.GetCol(); ++j)
        {
            printf("%f ", a(i, j));
        }
        printf("\n");
    }
    printf("\n");
}

void printVector(itr_math::Vector a)
{
    printf("The Vector is\n");
    for(int i = 0; i<a.GetDim(); i++)
    {
        printf("%f ",a.GetData()[i]);
    }
    printf("\n");
    printf("\n");
}

void printArray(F32* data, int length)
{
    printf("The Array is:\n");
    for(int i = 0;i<length;i++)
    {
        printf("%f ",data[i]);
    }
    printf("\n");
    printf("\n");
}

void TestMatrix()
{
    //Init
    itr_math::MathObjStandInit();
    /////////
    printf("************ svd test ********************\n");
    F32 dataaa1[72]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    itr_math::Matrix A(8,9,dataaa1);
    itr_math::Matrix V(9,9);
    itr_math::Vector W(9);
    //test svd   /////////////////////////////

    A.Svdcmp(W,V);
    printf("matrix V :\n");
    printMatrix(V);
    printf("vector W :\n");
    printVector(W);
    printf("matrix U :\n");
    printMatrix(A);
    //test pinv   /////////////////////////////

    printf("************ pinv test ********************\n");
    F32 dataaa2[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    F32 dataaa3[9]={1,3,5,7,9,6,7,8,9};
    itr_math::Matrix Afdet(3,3,dataaa3);
    itr_math::Matrix AA(4,4,dataaa2);
    itr_math::Matrix X(4,4);
    itr_math::Matrix XAA(4,4);
    AA.pinv(X);
    XAA=AA*X;
    F32 result_f32;
    Afdet.Det(result_f32);
    printf("Det of Afdet: %f\n",result_f32);
    printf("matrix AA :\n");
    printMatrix(AA);
    printf("matrix X :\n");
    printMatrix(X);
    printf("matrix X*AA :\n");
    printMatrix(XAA);
    //test copyto &copyfrom
    itr_math::Matrix Ac(2,2);
    AA.CopyTo(2,2,2,2,Ac.GetData());
    printf("matrix AA :\n");
    printMatrix(AA);
    printf("matrix Ac :\n");
    printMatrix(Ac);
    AA.CopyFrom(0,1,2,2,Ac.GetData());
    AA.CopyTo(2,2,2,2,Ac.GetData());
    printf("matrix AA :\n");
    printMatrix(AA);

    //测试数据
    /* 1   4  9
     * 16 25 36
     * 49 64 91
     */
    /*初始化数据*/
    F32 data1[3 * 3];
    F32 data2[3 * 3];
    F32 data3[3 * 3] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    F32 data4[3 * 3] =
    { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    F32 data5[3 * 3] =
    { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    F32 data6[3 * 3] =
    { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    F32 data7[3 * 3] =
    { 1, 0, 0, 0, 2, 0, 0, 0, 4 };
    F32 dataRect[3 * 3] =
    { 10, 200, 30, 40, 0, 0, 0, 0, 0 };
    F32 ExData[] =
    { 1, 1, 1 };
    F32 ExTemp[] =
    { 0, 0, 0 };
    F32 VecData[] =
    { 1, 1, 1 };
    for (S32 i = 0; i < 3 * 3; i++)
    {
        data1[i] = (i + 1) * (i + 1);
        data2[i] = (i + 1) * (i + 1);
    }
    F32 MatData[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    itr_math::Matrix Source1(3, 3, data1);
    itr_math::Matrix Source2(3, 3, data2);
    itr_math::Matrix Result(3, 3, data3);
    itr_math::Matrix Source3(3, 3, data4);
    itr_math::Matrix Source4(3, 3, data5);
    itr_math::Matrix SourceEye(3, 3, data6);
    itr_math::Matrix Source5(3, 3, data7);
    itr_math::Matrix Template(3, 3, data1);
    itr_math::Matrix GeneralMat(3,5,MatData);
    itr_math::Vector VecSource(3, VecData);

    //初等变换测试
    Source1.AddRow(0, 1);
    assert(Source1.GetData()[3] == 17 && Source1.GetData()[4] == 29 && Source1.GetData()[5] == 45);
    Source1.SubRow(0, 1);
    assert(Source1.GetData()[3] == 16 && Source1.GetData()[4] == 25 && Source1.GetData()[5] == 36);

    Source1.AddRow(ExData, 0);
    assert(Source1.GetData()[0] == 2 && Source1.GetData()[1] == 5 && Source1.GetData()[2] == 10);
    Source1.SubRow(ExData, 0);
    assert(Source1.GetData()[0] == 1 && Source1.GetData()[1] == 4 && Source1.GetData()[2] == 9);

    Source1.AddCol(0, 1);
    assert(Source1.GetData()[1] == 5 && Source1.GetData()[4] == 41 && Source1.GetData()[7] == 113);
    Source1.SubCol(0, 1);
    assert(Source1.GetData()[1] == 4 && Source1.GetData()[4] == 25 && Source1.GetData()[7] == 64);

    Source1.AddCol(ExData, 0);
    assert(Source1.GetData()[0] == 2 && Source1.GetData()[3] == 17 && Source1.GetData()[6] == 50);
    Source1.SubCol(ExData, 0);
    assert(Source1.GetData()[0] == 1 && Source1.GetData()[3] == 16 && Source1.GetData()[6] == 49);

    Result.Add(Source3);
    assert(Result.GetData()[0] == 1 && Result.GetData()[4] == 1 && Result.GetData()[8] == 1);
    Result.Add(Source4);
    assert(Result.GetData()[0] == 0 && Result.GetData()[4] == 0 && Result.GetData()[8] == 0);
    Result.Sub(Source3);
    assert(Result.GetData()[0] == -1 && Result.GetData()[4] == -1 && Result.GetData()[8] == -1);
    Result.Sub(Source4);
    assert(Result.GetData()[0] == 0 && Result.GetData()[4] == 0 && Result.GetData()[8] == 0);

    Source3.MulRow(2, 0);
    assert(Source3.GetData()[0] == 2 && Source3.GetData()[1] == 2 && Source3.GetData()[2] == 2);
    Source3.MulRow(0.5, 0);
    assert(Source3.GetData()[0] == 1 && Source3.GetData()[1] == 1 && Source3.GetData()[2] == 1);

    Source3.MulCol(2, 0);
    assert(Source3.GetData()[0] == 2 && Source3.GetData()[3] == 2 && Source3.GetData()[6] == 2);
    Source3.MulCol(0.5, 0);
    assert(Source3.GetData()[0] == 1 && Source3.GetData()[3] == 1 && Source3.GetData()[6] == 1);

    Source3.Mul(Result, Result);
    assert(Result.GetData()[0] == 0 && Result.GetData()[4] == 0 && Result.GetData()[8] == 0);

    Source1.SwapRow(0, 1);
    assert(Source1.GetData()[0] == 16 && Source1.GetData()[1] == 25 && Source1.GetData()[2] == 36);
    Source1.SwapRow(1, 0);
    assert(Source1.GetData()[0] == 1 && Source1.GetData()[1] == 4 && Source1.GetData()[2] == 9);

    Source1.SwapCol(0, 1);
    assert(Source1.GetData()[0] == 4 && Source1.GetData()[3] == 25 && Source1.GetData()[6] == 64);
    Source1.SwapCol(1, 0);
    assert(Source1.GetData()[0] == 1 && Source1.GetData()[3] == 16 && Source1.GetData()[6] == 49);

    //常量相关运算测试
    Source1.AllAdd(1);
    assert(Source1.GetData()[0] == 2 && Source1.GetData()[4] == 26 && Source1.GetData()[8] == 82);
    Source1.AllAdd(-1);
    assert(Source1.GetData()[0] == 1 && Source1.GetData()[4] == 25 && Source1.GetData()[8] == 81);

    Source3.AllMul(2);
    assert(Source3.GetData()[0] == 2 && Source3.GetData()[4] == 2 && Source3.GetData()[8] == 2);
    Source3.AllMul(0.5);
    assert(Source3.GetData()[0] == 1 && Source3.GetData()[4] == 1 && Source3.GetData()[8] == 1);

    //常用操作测试
    Source3.ColExtract(Source3.GetData(), 0, Source3.GetCol(), 3, ExTemp);
    assert(ExTemp[0] == 1 && ExTemp[1] == 1 && ExTemp[2] == 1);
    Result.ColExtract(Result.GetData(), 0, Result.GetCol(), 3, ExTemp);
    assert(ExTemp[0] == 0 && ExTemp[1] == 0 && ExTemp[2] == 0);

    //矩阵相关运算
    VecSource = Source3 * VecSource;
    assert(VecSource[0] == 3 && VecSource[1] == 3 && VecSource[2] == 3);
    VecSource.Set(1);
    assert(VecSource[0] == 1 && VecSource[1] == 1 && VecSource[2] == 1);
    printMatrix(Result);
    //printMatrix(Source1);
    //printMatrix(Source1 * SourceEye);
    Result = Source1 * SourceEye;    //乘单位阵
    //printMatrix(Result);
    assert(Result.GetData()[0] == 1 && Result.GetData()[4] == 25 && Result.GetData()[8] == 81);
    Result.Set(0);

    Result = Result + Source3;
    assert(Result.GetData()[0] == 1 && Result.GetData()[4] == 1 && Result.GetData()[8] == 1);
    Result.Set(0);

    Result = Source1 - Source2;
    assert(Result.GetData()[0] == 0 && Result.GetData()[4] == 0 && Result.GetData()[8] == 0);
    Result.Set(0);

    Result.Clear();
    Result.SetDiag(2);
    assert(Result.GetData()[0] == 2 && Result.GetData()[4] == 2 && Result.GetData()[8] == 2);
    Result.Set(0);

    //此处测试啦，没有问题啊！！！
    //Source5.Inv(Result);
    //Result = Source5 * Result;
    Result = Source5.Inv();
    Result = Source5*Result;
    printMatrix(Result);
    assert(
        fabs(Result.GetData()[0] - 1) < 0.0001 && fabs(Result.GetData()[4] - 1) < 0.0001
        && fabs(Result.GetData()[8] - 1) < 0.0001);
    Result.Set(0);

    //Source1.Tran(Result);
    Result = Source1.Tran();
    assert(
        Source1.GetData()[0] == Result.GetData()[0]
        && Source1.GetData()[1] == Result.GetData()[3]
        && Source1.GetData()[2] == Result.GetData()[6]);



    F32 SourceData[3*3] = {1,2,3,4,5,6,7,8,9};
    //F32 InsertData[3*3] = {2,2,2,2,2,2,2,2,2};
    F32 ExtractData[3*3];
    F32 RowData[3] = {11,22,33};
    //测试:inline void virtual CopyFrom(S32 RowPos, S32 ColPos, S32 Width, S32 Height,F32* Data)
    printf("测试:inline void virtual CopyFrom(S32 RowPos, S32 ColPos, S32 Width, S32 Height,F32* Data)\n");
    Source1.Set(1);
    printMatrix(Source1);
    Source1.CopyFrom(1, 1, 2, 2, dataRect);
    printMatrix(Source1);
    Source1.Set(1);    //复原数据
    //测试：inline void virtual CopyFrom(F32* Data)
    printf("测试：inline void virtual CopyFrom(F32* Data)\n");
    printMatrix(Source1);
    Source1.CopyFrom(SourceData);
    printMatrix(Source1);
    Source1.Set(1);    //复原数据
    printMatrix(Source1);
    //测试：inline void virtual CopyTo(S32 RowPos, S32 ColPos, S32 Width, S32 Height, F32* Data) const
    printf("测试：inline void virtual CopyTo(S32 RowPos, S32 ColPos, S32 Width, S32 Height, F32* Data) const\n");
    Source1.CopyTo(0, 0, 3, 3, ExtractData);
    for(S32 i = 0; i<9; i++)
    {
        printf("%f ",ExtractData[i]);
    }
    printf("\n");
    //测试：inline void virtual CopyTo(F32* Data) const
    printf("测试：inline void virtual CopyTo(F32* Data) const\n");
    Source1.Set(5);
    printMatrix(Source1);
    Source1.CopyTo(ExtractData);
    for(int i = 0; i<9; i++)
    {
        printf("%f ",ExtractData[i]);
    }
    printf("\n");
    //Test:inline void virtual CopyRowFrom(S32 RowPos, S32 ColPos, S32 ColNum, F32* Data)
    printf("Test:inline void virtual CopyRowFrom(S32 RowPos, S32 ColPos, S32 ColNum, F32* Data)\n");
    Source1.Set(3);
    Source1.CopyRowFrom(1,0,3,RowData);
    printMatrix(Source1);
    Source1.Set(0);
    //Test:inline void virtual CopyRowFrom(S32 RowNo, F32* Data)
    printf("inline void virtual CopyRowFrom(S32 RowNo, F32* Data)\n");
    Source1.CopyRowFrom(1,RowData);
    printMatrix(Source1);
    Source1.Set(0);
    //Test:inline void virtual CopyRowTo(S32 RowNo, S32 ColOffset, S32 ColNum, F32* Data) const
    printf("inline void virtual CopyRowTo(S32 RowNo, S32 ColOffset, S32 ColNum, F32* Data) const\n");
    Source1.CopyRowTo(1,1,2,RowData);
    for(S32 i = 0; i<3; i++)
        printf("%f ",RowData[i]);
    printf("\n");
    //Test:inline void virtual CopyRowTo(S32 RowNo, F32* Data) const
    printf("inline void virtual CopyRowTo(S32 RowNo, F32* Data) const\n");
    Source2.CopyRowTo(2,RowData);
    for(S32 i = 0; i<3; i++)
        printf("%f ",RowData[i]);
    printf("\n");
    //Test:inline void virtual CopyColFrom(S32 ColPos, S32 RowPos, S32 RowNum, F32* Data)
    printf("inline void virtual CopyColFrom(S32 ColPos, S32 RowPos, S32 RowNum, F32* Data)\n");
    printMatrix(GeneralMat);
    printArray(RowData,3);
    GeneralMat.CopyColFrom(0,1,2,RowData);
    printMatrix(GeneralMat);
    //Test:inline void virtual CopyColFrom(S32 ColNo, F32* Data)
    printf("inline void virtual CopyColFrom(S32 ColNo, F32* Data)\n");
    printArray(RowData,3);
    Source2.CopyColFrom(2,RowData);
    printMatrix(Source2);
    //Test:inline void virtual CopyColTo(S32 ColPos, S32 RowPos, S32 RowNum, F32* Data) const
    printf("inline void virtual CopyColTo(S32 ColPos, S32 RowPos, S32 RowNum, F32* Data) const\n");
    printMatrix(GeneralMat);
    printArray(RowData,3);
    GeneralMat.CopyColTo(4,1,2,RowData);
    printArray(RowData,3);
    //Test:inline Řvoid virtual CopyColTo(S32 ColNo, F32* Data) const
    printf("inline void virtual CopyColTo(S32 ColNo, F32* Data) const\n");
    printMatrix(GeneralMat);
    printArray(RowData,3);
    GeneralMat.CopyColTo(3,RowData);
    //printArray(RowData,3);

    TRACE_INFO("OK TestMatrix()");
    //Test:inline Řvoid virtual CopyColTo(S32 ColNo, F32* Data) const
    //printf("inline void virtual CopyColTo(S32 ColNo, F32* Data) const\n");
    //

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
void TestTransform()
{
    itr_math::Vector Input(3), veco(3);
    F32 data1[3] =
    { 1, 2, 0 }, data2[3], data3[3] =
    { 2, 0, 0 };
    Input.CopyFrom(data1);

    itr_math::Transform2D trans1;
    trans1.Reset();                             //测试初始化函数
    trans1.Transform(Input, veco);
    veco.CopyTo(data2);
    assert(*data2 == 1);
    assert(*(data2 + 1) == 2);

    trans1.Offset(1, 3);                 //test Offset function:没有变化
    trans1.Transform(Input, veco);
    veco.CopyTo(data2);
    assert(*data2 == 2);
    assert(*(data2 + 1) == 5);

    trans1.Offset(-1, -3);               //test Offset function (minus)
    trans1.Transform(Input, veco);
    veco.CopyTo(data2);
    assert(*data2 == 1);
    assert(*(data2 + 1) == 2);

    trans1.Reset();
    trans1.Scale(2, 4);                  //test Scale function (amplify)
    trans1.Transform(Input, veco);
    veco.CopyTo(data2);
    assert(*data2 == 2);
    assert(*(data2 + 1) == 8);

    trans1.Inv();
    trans1.Transform(veco, veco);
    veco.CopyTo(data2);
    assert(*data2 == 1);
    assert(*(data2 + 1) == 2);

    trans1.Reset();
    trans1.Scale(0.5, 0.25);             //test Scale function (reduce)
    trans1.Transform(Input, veco);
    veco.CopyTo(data2);
    assert(*data2 == 0.5);
    assert(*(data2 + 1) == 0.5);

    Input.CopyFrom(data3);              //test Rotate function(90 degree)
    trans1.Reset();
    trans1.Rotate(90);
    trans1.Transform(Input, veco);
    veco.CopyTo(data2);
    assert(GET_ABS(*data2) < 0.0001);
    assert(GET_ABS(*(data2 + 1)-2) <0.0001);
    trans1.Rotate(-60);
    trans1.Transform(Input, veco);
    veco.CopyTo(data2);
    assert(*(data2 + 1) == 1);

    itr_math::Point2D pos1, pos2;
    pos1.SetXY(1, 2);
    trans1.Reset();
    trans1.Transform(pos1, pos2);
    assert(pos1.X == pos2.X);
    assert(pos1.Y == pos2.Y);

    trans1.Reset();
    trans1.Offset(1, 3);             //test Offset function
    trans1.Transform(pos1, pos2);
    //printf("%f,%f\n",pos2.X,pos2.Y);
    assert(pos2.X == 2);
    assert(pos2.Y == 5);
    trans1.Offset(-1, -3);               //test Offset function (minus)
    trans1.Transform(pos1, pos2);
    assert(pos2.X == 1);
    assert(pos2.Y == 2);

    trans1.Scale(2, 4);                  //test Scale function (amplify)
    trans1.Transform(pos1, pos2);
    assert(pos2.X == 2);
    assert(pos2.Y == 8);
    trans1.Scale(0.5, 0.25);             //test Scale function (reduce)
    trans1.Transform(pos1, pos2);
    assert(pos2.X == 1);
    assert(pos2.Y == 2);

    pos1.X = 2;
    pos1.Y = 0;
    trans1.Reset();
    trans1.Rotate(90);                  //test Rotate function(90 degree)
    trans1.Transform(pos1, pos2);
    assert(GET_ABS(pos2.X - 0) < 0.001);
    assert(pos2.Y == 2);
    trans1.Reset();
    trans1.Rotate(-60);
    trans1.Transform(pos1, pos2);
    assert(GET_ABS(pos2.X-1)<0.001);
    assert(GET_ABS(pos2.Y+1.732)<0.01);

    trans1.Inv();
    trans1.Transform(pos1, pos2);
    assert(GET_ABS(pos2.X-1)<0.01);
    assert(GET_ABS(pos2.Y-1.732)<0.01);

    F32 inx = 1, iny = 2, outx, outy;
    trans1.Reset();
    trans1.Transform(inx, iny, outx, outy);
    assert(inx == outx);
    assert(iny == outy);

    trans1.Offset(1, 3);             //test Offset function
    trans1.Transform(inx, iny, outx, outy);
    assert(outx == 2);
    assert(outy == 5);
    trans1.Offset(-1, -3);               //test Offset function (minus)
    trans1.Transform(inx, iny, outx, outy);
    assert(outx == 1);
    assert(outy == 2);

    trans1.Scale(2, 4);                  //test Scale function (amplify)
    trans1.Transform(inx, iny, outx, outy);
    assert(outx == 2);
    assert(outy == 8);
    trans1.Scale(0.5, 0.25);             //test Scale function (reduce)
    trans1.Transform(inx, iny, outx, outy);
    assert(outx == 1);
    assert(outy == 2);

    inx = 2;
    iny = 0;
    trans1.Reset();
    trans1.Rotate(90);                  //test Rotate function(90 degree)
    trans1.Transform(inx, iny, outx, outy);
    assert(GET_ABS(outx - 0) < 0.001);
    assert(outy == 2);

    trans1.Reset();
    trans1.Rotate(-60);
    trans1.Transform(inx, iny, outx, outy);
    assert(GET_ABS(outx -1)<0.01);
    assert(GET_ABS(outy+1.732)<0.01);

    trans1.Inv();
    trans1.Transform(inx, iny, outx, outy);
    assert(GET_ABS(outx-1)<0.01);
    assert(GET_ABS(outy-1.732)<0.01);

    TRACE_INFO("OK TestTransform2D()");
}

void TestGeometry()
{
    /************测试itr_math::Distance2D函数***************/
    itr_math::Distance2D dis1, dis2(dis1);
    assert(dis1.DX == 0 && dis1.DY == 0);
    assert(dis2.DX == 0 && dis2.DY == 0);
    dis1.SetDXDY(10, 20);                //test SetDXDY
    assert(dis1.DX == 10 && dis1.DY == 20);

    dis1.SetAngleDistance(90, 20);       //
    assert(
        (dis1.DX < 0.0001 && dis1.DX > -0.0001)
        && ((dis1.DY - 20) > -0.001 && (dis1.DY - 20) < 0.0001));

    dis1.SetDXDY(10, 20);
    dis2 = dis1;
    assert(dis2.DX == 10 && dis2.DY == 20);

    dis2 = dis2 + dis1;
    assert(dis2.DX == 20);
    assert(dis2.DY == 40);

    dis2 = dis2 - (dis1);
    assert(dis2.DX == 10 && dis2.DY == 20);

    F32 andis;
    dis2.SetDXDY(10, 17.32050808);
    andis = dis2.GetAngle();
    assert(((andis - 60) < 0.0001) && ((andis - 60) > -0.0001));

    andis = dis2.GetDistance();
    assert(andis == 20);              //itr_math::Distance2D测试完毕

    /************测试itr_math::Point2D函数****************/
    itr_math::Point2D pos1, pos2(1, 2), pos3(pos2);
    assert(pos1.X == 0 && pos1.Y == 0);
    assert(pos2.X == 1 && pos2.Y == 2);
    assert(pos3.X == 1 && pos3.Y == 2);

    pos1.SetXY(3, 4);
    assert(pos1.X == 3 && pos1.Y == 4);

    pos1 = pos2;
    assert(pos1.X == 1 && pos1.Y == 2);

    dis1 = pos1 - (pos2);
    assert(dis1.DX == 0 && dis1.DY == 0);

    dis1.SetDXDY(10, 20);
    pos2 = pos1 + (dis1);
    assert(pos2.X == 11 && pos2.Y == 22);

    pos1 = pos2 - (dis1);
    assert(pos1.X == 1 && pos1.Y == 2);

    /************测试 itr_math::Point3D函数***************/
    itr_math::Point3D pos3d1(1, 2, 3);
    assert(pos3d1.X == 1 && pos3d1.Y == 2 && pos3d1.Z == 3);       //question 4 :我把的成员改为公用的了！

    /************测试itr_math::RectangleF函数*************/
    itr_math::RectangleF rect1(1, 2, 10, 20);
    assert(rect1.X == 1 && rect1.Y == 2 && rect1.Width == 10 && rect1.Height == 20);
    pos1.SetXY(3, 4);
    rect1.SetPoint(pos1);
    assert(rect1.X == 3 && rect1.Y == 4);
    pos2 = rect1.GetPoint();
    assert(pos2.X == 3 && pos2.Y == 4);
    pos2 = rect1.GetCenter();
    assert(pos2.X == (3 + 5) && pos2.Y == (4 + 10));

    assert(rect1.IsInRectangle(pos2));
    pos3.SetXY(14, 10);
    assert(!rect1.IsInRectangle(pos3));
    pos3.SetXY(0, 0);
    assert(!rect1.IsInRectangle(pos3));
    pos3.SetXY(3, 4);
    assert(rect1.IsInRectangle(pos3));      //含边缘。。。

    /************测试 itr_math::RectangleS函数************/
    itr_math::RectangleS recS(1, 2, 10, 20);
    assert(recS.X == 1 && recS.Y == 2 && recS.Width == 10 && recS.Height == 20);
    assert(recS.IsInRectangle(3, 5));
    assert(recS.IsInRectangle(1, 2));
    assert(!recS.IsInRectangle(12, 5));
    assert(!recS.IsInRectangle(4, 23));

    S32 X = 1, Y = 2;
    recS.Reset();
    while (recS.Next(X, Y))
    {
        assert(recS.IsInRectangle(X, Y));
    }
    assert(X == 10 && Y == 22);
    //

    TRACE_INFO("OK TestGeometry()");
}

void TestCalcEff()
{
    clock_t start,end;
    double t;
    S32 width = 100;
    S32 height = 100;
//    S16 RawDataS16a[100*100];
//    S16 RawDataS16b[100*100];
    //S16 RawDataS16c[100*100];
//    S32 RawDataS32a[100*100];
//    S32 RawDataS32b[100*100];
    //S32 RawDataS32c[100*100];
//    F32 RawDataF32a[100*100];
//    F32 RawDataF32b[100*100];
    //F32 RawDataF32c[100*100];

    srand(time(0));//设置随机种子
    for(int i = 0;i<width*height;i++)
    {
//       RawDataS16a[i] = rand()%100 + 1;
//       RawDataS16b[i] = rand()%100 + 1;
//       RawDataS32a[i] = rand()%100 + 1;
//       RawDataS32b[i] = rand()%100 + 1;
//       RawDataF32a[i] = 99.0*(rand()%10000)/10000 + 1;
//       RawDataF32b[i] = 99.0*(rand()%10000)/10000 + 1;
    }

    //开始计时处写：
    start = clock();
        for(int j=0;j<100;++j)
    for(int i = 0;i<width*height;i++)
    {
        //RawDataS16c[i] = RawDataS16a[i] + RawDataS16b[i];
    }
    //结束计时处写：
    end = clock();
    t=(end - start);
    printf("S16 + use %lf ms\n\n", t);

    //开始计时处写：
    start = clock();
    for(int j=0;j<100;++j)
    for(int i = 0;i<width*height;i++)
    {
        //RawDataS16c[i] = RawDataS16a[i] * RawDataS16b[i];
    }
    //结束计时处写：
    end = clock();
    t=(end - start);
    //printf("S16 * use %d ms\n\n", (end - start));

    //开始计时处写：
    start = clock();
        for(int j=0;j<100;++j)
    for(int i = 0;i<width*height;i++)
    {
        //RawDataS32c[i] = RawDataS32a[i] + RawDataS32b[i];
    }
    //结束计时处写：
    end = clock();
    t=(end - start);
    printf("S32 + use %lf ms\n\n", t);

    //开始计时处写：
    start = clock();
        for(int j=0;j<100;++j)
    for(int i = 0;i<width*height;i++)
    {
        //RawDataS32c[i] = RawDataS32a[i] * RawDataS32b[i];
    }
    //结束计时处写：
    end = clock();
    t=(end - start);
    printf("S32 * use %lf ms\n\n", t);

    //开始计时处写：
    start = clock();
        for(int j=0;j<100;++j)
    for(int i = 0;i<width*height;i++)
    {
       // RawDataF32c[i] = RawDataF32a[i] + RawDataF32b[i];
    }
    //结束计时处写：
    end = clock();
    t=(end - start);
    printf("F32 + use %lf ms\n\n", t);

    //开始计时处写：
    start = clock();
        for(int j=0;j<101;++j)
    for(int i = 0;i<width*height;i++)
    {
       // RawDataF32c[i] = RawDataF32a[i] * RawDataF32b[i];
    }
    //结束计时处写：
    end = clock();
    t=(end - start);
    printf("F32 * use %lf ms\n\n", t);

}
