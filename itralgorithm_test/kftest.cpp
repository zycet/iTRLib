#include "kftest.h"
#include "itrbase.h"
#include "itralgorithm.h"
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
using std::vector;
using std::ofstream;
using namespace itr_math;
using namespace itr_algorithm;

void printMatrix(Matrix a)
{
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
void kftest()
{
    KalmanFilter kf(4);
    F32 data[16]={2 ,0,-1,0,0,2,0,-1,0,0,1,0,0,0,0,1};
    kf.F_x.CopyRowFrom(1,data);
    kf.F_x.CopyRowFrom(2,data+4);
    kf.F_x.CopyRowFrom(3,data+8);
    kf.F_x.CopyRowFrom(4,data+12);
    Matrix H(2,4),R(2,2);
    R.MatEye(0.1);
    H.CopyRowFrom(1,data+10);
    H.CopyRowFrom(2,data+9);
    printMatrix(H);
    printMatrix(kf.F_x);
    Vector z(2),x(4),X(4),v(2),n(4);
    for(int t=0;t<20;++t)
    {
        NumericalObj->Rand(data[0]);
        NumericalObj->Rand(data[1]);
          NumericalObj->Rand(data[2]);
        NumericalObj->Rand(data[3]);
        data[0]*=5;
        data[1]*=5;
        data[2]*=5;
        data[3]*=5;
         printf("rand:%f,%f\n",data[0],data[1]);
        v.CopyFrom(data);
        n.CopyFrom(data);
        x=kf.F_x*x+kf.F_n*n;
        z=H*x+v;

        kf.UpdateModel();
        X=kf.UpdateMeasure(H,R,z);
        printf("State:%.0f,%.0f,%.0f,%.0f\n",x[0],x[1],x[2],x[3]);
        printf("Measure:%.0f,%.0f\n",z[0],z[1]);
        printf("Estimate:%.0f,%.0f,%.0f,%.0f\n",X[0],X[1],X[2],X[3]);
        printf("\n");
    }
}
