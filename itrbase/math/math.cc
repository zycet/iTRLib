
#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
Numerical* NumericalObj;
Calculate* CalculateObj;
Statistics* StatisticsObj;
Vector* VectorObj;

void MathObjStandInit()
{
    NumericalObj = new Numerical();
    CalculateObj = new Calculate();
    StatisticsObj = new Statistics();
}

void MathObjStandDeinit()
{
    delete NumericalObj;
    delete CalculateObj;
    delete StatisticsObj;
}
}


