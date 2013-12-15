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

void kftest()
{
    KalmanFilter kf(2);
    F32 data[2];
    data[0]=data[1]=1;
    Matrix H(2,2),R(2,2);
    R.MatEye(1);
    H.CopyRowFrom(1,data);
    //H.CopyRowFrom(2,data);
    kf.F_x.CopyRowFrom(1,data);
    data[0]=0;
    kf.F_x.CopyRowFrom(2,data);
    kf.F_n.MatEye(1);
    data[0]=3;data[1]=2;
    Vector x(2,data),X(2);
    Vector v(2),z(2);
    for(int t=0;t<20;++t)
    {
        NumericalObj->Rand(data[0]);
        NumericalObj->Rand(data[1]);
        data[0]*=5;
        data[1]*=5;
         printf("rand:%f,%f\n",data[0],data[1]);
        v.CopyFrom(data);
        x=kf.F_x*x+kf.F_n*v;
        z=H*x+v;

        kf.UpdateModel();
        X=kf.UpdateMeasure(H,R,z);
        printf("State:%.0f,%.0f\n",x[0],x[1]);
        printf("Measure:%.0f,%.0f\n",z[0],z[1]);
        printf("Estimate:%.0f,%.0f\n",X[0],X[1]);
        printf("\n");
    }
}
