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
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 * main.cc
 *  Created on: 2013-9-10
 *      Author: buaa
 */

#include "itrbase.h"
#include "platform_test.h"
#include "containertest.h"
#include "mathtest.h"
#include "helpertest.h"

void testSVD(itr_math::Matrix &M)
{

}
void SVD_dec(itr_math::Matrix &A)
{
    S32 m,n,p;
    m=A.GetRow();
    n=A.GetCol();
    p=m>n?n:m;

    itr_math::Matrix U(m,p);
    itr_math::Matrix V(n,p);
    itr_math::Vector S(p);
    if(m>=n)
    {
        itr_math::Matrix B(A);
        decomposition(B,U,S,V);
    }
    else
    {
        F32 K;
        A.Tr(K);
        itr_math::Matrix B(K);
    }
}
int main()
{
    //Platform
    TestAssistMacro();
    TestDebugSupport();
    //TestMemoryOperation();
    TestTypedef();
    //Container
    TestCycleQueue();
    //Math
    TestMathInit();
    TestCalculate();
    TestNumerical();
    TestStatistics();
    TestVector();

    TestCalculateTest();
    TestMathdeDeinit();
    TestMatrix();
    TestGeometry();
    TestTransform();
    //Test Helper
    TestGaussianGenerate();
    TestCalcEff();
    //Finish
    /*************************************/
    itr_math::Matrix M,U,V;
    itr_math::Vector S;

    testSVD(M);
    /*************************************/
    TRACE_INFO("OK All");
    return 0;
}

