#include "itrbase.h"
#include "calculateneon.h"

namespace itr_math
{

void MathNeonObjStandInit()
{
    NumericalObj = new Numerical();
    CalculateObj = new CalculateNeon();
    StatisticsObj = new Statistics();
}

void MathNeonObjStandDeinit()
{
    delete NumericalObj;
    delete CalculateObj;
    delete StatisticsObj;
}

}
