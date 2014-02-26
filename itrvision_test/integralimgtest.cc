#include "integralimgtest.h"
//#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include <math.h>
#include <iostream>

void IntegralImgTest()
{
    TestIntegral();
    TestBoxFilterStarter();
    TestColHalfWidth();
}
void TestIntegral()
{
    itr_math::MathObjStandInit();
    Matrix Input(4, 4);
    Matrix Output(4, 4);
    Input.Set(1);
    itr_vision::IntegralImg::Integral(Input, Output);
    Input.Set(2);
}

void TestBoxFilterStarter()
{
    itr_math::MathObjStandInit();
    Matrix Input(4, 4);
    Matrix Output(4, 4);
    F32 result;
    Input.Set(1);
    itr_vision::IntegralImg::Integral(Input, Output);
    itr_vision::IntegralImg::BoxFilterStarter(Output ,0 ,0 ,2 ,2 );
    Input.Set(2);
}

void TestColHalfWidth()
{
    itr_math::MathObjStandInit();
    Matrix Input(5, 5);
    Matrix Output(5, 5);
    F32 result;
    Input.Set(1);
    itr_vision::IntegralImg::Integral(Input, Output);
    itr_vision::IntegralImg::BoxFilterCenter(Output,3,3,1,1);
}
