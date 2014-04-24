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


static void printMatrix(Matrix a)
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
static void printVec(Vector a)
{
    printf("%d : ",a.GetDim());
    for(int i=0; i<a.GetDim(); ++i)
    {
        printf("%.0f,",a[i]);
    }
    printf("\n");
}

void kftest()
{
    printf("*****Begin Kalman Filter Test!*****\n\n");
    KalmanFilter kf(4);
    F32 data[16]= {2 ,0,-1,0,0,2,0,-1,1,0,0,0,0,1,0,0};
    kf.F_x.CopyFrom(data);
    Matrix H(2,4),R(2,2),Q(4,4);
    R.SetDiag(5.012306);
    H.CopyFrom(data+8);
    Q.SetDiag(1);
    printMatrix(H);
    printMatrix(kf.F_x);
    Vector z(2),x(4),X(4),v(2),n(4);
    x[0]=1;
    x[1]=1;
    x[2]=0;
    x[3]=0;
    for(int t=0; t<20; ++t)
    {
        NumericalObj->RandGaussian(data[0]);
        NumericalObj->RandGaussian(data[1]);
        NumericalObj->RandGaussian(data[2]);
        NumericalObj->RandGaussian(data[3]);
//        data[0]=(data[0])*0.1;
//        data[1]=(data[1])*0.1;
//        data[2]=(data[2])*0.1;
//        data[3]=(data[3])*0.1;
        printf("rand:%f,%f\n",data[0],data[1]);
        v.CopyFrom(data);
        n.CopyFrom(data);
        x=kf.F_x*x+kf.F_n*n;
//        printVec(x);
        z=H*x+v;
//        printVec(z);
        kf.UpdateModel(Q,n);
        X=kf.UpdateMeasure(H,R,z);
        printf("Measu:%.0f,%.0f\n",z[0],z[1]);
        printf("State:%.0f,%.0f,%.0f,%.0f\n",x[0],x[1],x[2],x[3]);
        printf("Esti :%.0f,%.0f,%.0f,%.0f\n",X[0],X[1],X[2],X[3]);
        printf("\n");
    }
    printf("*****End Kalman Filter Test!*****\n\n");
}
