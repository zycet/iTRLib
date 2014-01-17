#include <iostream>
#include "itrbase.h"
#include "itrneon.h"

using namespace std;
using namespace itr_math;

#define TESE_NUM 30

void CalculateNeonTest()
{
    F32 a[TESE_NUM];
    F32 b[TESE_NUM];
    F32 r[TESE_NUM];
    for(S32 i=0;i<TESE_NUM;i++)
    {
        a[i]=1;
        b[i]=2;
        r[i]=0;
    }
    itr_math::CalculateObj->Multi(a, b, TESE_NUM, r);
    for(S32 i=0;i<TESE_NUM;i++)
    {
        if(r[i]!=2)
        {
            a[i]=1;
        }
    }
}

int main()
{
    itr_math::MathNeonObjStandInit();
    CalculateNeonTest();
    cout << "Hello world!" << endl;
    return 0;
}
