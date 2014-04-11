#include "ransactest.h"
#include "itrbase.h"
#include "itralgorithm.h"
#include <math.h>
#include <algorithm>
using namespace itr_algorithm;

template <class T>
class DataOper:public Ransac<T,T>::Operator
{
    public:
        F32 GetError(T a, T b)
        {
            return (a-b)*(a-b);
        }
        T GetValue(T *data, S32 N)
        {
            std::sort(data,data+N);
            return data[N/2];
        }
        bool Remain(T a,T b)
        {
            return (fabs(a-b)<2);
        }
};

DataOper<F32> oper;
Ransac<F32,F32> ransac;

void ransactest()
{
    ransac.Init(&oper);
    float a[20];
    for(int i=0;i<20;i++)
    {
        itr_math::NumericalObj->RandGaussian(a[i]);
    }
    for(int i=15;i<20;i++)
    {
        a[i]+=3.5;
    }
    int drop;
    float result=ransac.Process(a,20,drop);
    printf("result:%f\n",result);
    for(int i=0;i<20;i++)
        printf("%1.4f ",a[i]);
    printf("\n");

}
