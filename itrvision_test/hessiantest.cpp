#include "hessiantest.h"
//#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include <math.h>
#include <iostream>

void TestBoxHessian()
{
    TestCalBoxHessian();
    TestGetHessian();
    TestGetLaplacian();
    TestGetLaplacianS();
}

void TestCalBoxHessian()
{
    itr_math::MathObjStandInit();
    Matrix Input(80, 80);
    Matrix Output(80, 80);
    F32 result;
    Input.Set(2);
    itr_vision::IntegralImg::Integral(Input, Output);
    itr_vision::BoxHessian bh;
    bh.Init(80,80,2,9);
    bh.Calc(Output);
    Input.Set(2);
}


void TestGetHessian()
{
    itr_math::MathObjStandInit();
    Matrix Input(80, 80);
    Matrix Output(80, 80);
    F32 result;
    Input.Set(1);
    itr_vision::IntegralImg::Integral(Input, Output);
    itr_vision::BoxHessian bh;
    bh.Init(80,80,2,9);
    bh.Calc(Output);
    bh.GetHessian(30,30);

}

void TestGetLaplacian()
{

}

void TestGetLaplacianS()

{

}


