#include <iostream>
#include "itrbase.h"
#include "itrneon.h"

using namespace std;
using namespace itr_math;

#define TESE_NUM 10

void CalculateNeonTest()
{
    F32 a[TESE_NUM];
    F32 b[TESE_NUM];
    F32 r[TESE_NUM];
    for(S32 i=0;i<TESE_NUM;i++)
    {
        a[i]=i;
        b[i]=2;
        r[i]=0;
    }
    //Mul_F32 tested;Sub_F32 tested;Add_F32 tested;Div_F32 undone!
    //Offset_F32 finished! Scale_F32 finished! Normalization_F32 finished!(jingdu cha dian)
    itr_math::CalculateObj->Normalization(a,TESE_NUM, r);
    for(S32 i=0;i<TESE_NUM;i++)
    {
        if(r[i]!=1/30)
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
