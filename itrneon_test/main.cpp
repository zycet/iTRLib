#include <iostream>
#include "itrbase.h"
#include "itrneon.h"

using namespace std;
using namespace itr_math;

#define TESE_NUM 30

void CalculateNeonTest()
{
    //Mul_F32           finished
    //Sub_F32           finished
    //Add_F32           finished
    //AddSum            finished
    //Div_F32           undone!
    //Offset_F32        finished
    //Scale_F32         finished
    //MultiSum_F32      finished
    //Normalization_F32 finished
    //Abs               finished
    //Opposite          finished
    //Product           finished
    //Set               finished
    //Compare           finished
    F32 a[TESE_NUM];
    F32 b[TESE_NUM];
    F32 r[TESE_NUM];
    F32 k=0;
    BOOL IsSame;
    for(S32 i=0;i<TESE_NUM;i++)
    {
        a[i]=1;
        b[i]=2;
        r[i]=0;
    }
    itr_math::CalculateObj->Compare(a, b, 1,TESE_NUM,&IsSame);
    for(S32 i=0;i<TESE_NUM;i++)
    {
        if(r[i]!=-1)
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
