#include "pftest.h"
#include "itralgorithm.h"
#include "itrbase.h"
#include "kftest.h"
#include <stdio.h>
using namespace itr_algorithm;
using namespace itr_math;

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

void test1()
{
 printf("*****Begin Particle Filter Test!*****\n\n");
    ParticleFilter pf;
    Vector z(1),x(1),X(1);
    x[0]=0;
    pf.Init(80,x);
    F32 data[16]= {2 ,0,-1,0,0,2,0,-1,1,0,0,0,0,1,0,0};
    pf.F_x.CopyFrom(data);
    Matrix H(2,4),R(2,2);
    R.SetDiag(5.012306);
    H.CopyFrom(data+8);
    printMatrix(H);
    printMatrix(pf.F_x);

    FILE* fstate=fopen("pfteststate.txt","w");
    FILE* festi=fopen("pftestesti.txt","w");
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
        //v.CopyFrom(data);
        //n.CopyFrom(data);
        x=pf.F_x*x;
//        printVec(x);
        z=H*x;//+v;
//        printVec(z);
        pf.UpdateModel();
        pf.UpdateMeasure(H,R,z);
        pf.GetState(X);
        printf("Measu:%.1f,%.1f\n",z[0],z[1]);
        printf("State:%.1f,%.1f,%.1f,%.1f\n",x[0],x[1],x[2],x[3]);
        printf("Esti :%.1f,%.1f,%.1f,%.1f\n",X[0],X[1],X[2],X[3]);
        fprintf(fstate,"%.1f %.1f %.1f %.1f\n",x[0],x[1],x[2],x[3]);
        fprintf(festi,"%.1f %.1f %.1f %.1f\n",X[0],X[1],X[2],X[3]);
        printf("\n");
    }
    fclose(fstate);
    fclose(festi);
    printf("*****End Particle Filter Test!*****\n\n");
}

void test2()
{
    printf("*****Begin Particle Filter Test!*****\n\n");
    ParticleFilter pf;
    Vector z(2),x(4),X(4),v(2),n(4);
    x[0]=1;
    x[1]=1;
    x[2]=0;
    x[3]=0;
    pf.Init(80,x);
    F32 data[16]= {2 ,0,-1,0,0,2,0,-1,1,0,0,0,0,1,0,0};
    pf.F_x.CopyFrom(data);
    Matrix H(2,4),R(2,2);
    R.SetDiag(5.012306);
    H.CopyFrom(data+8);
    printMatrix(H);
    printMatrix(pf.F_x);

    FILE* fstate=fopen("pfteststate.txt","w");
    FILE* festi=fopen("pftestesti.txt","w");
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
        x=pf.F_x*x;
//        printVec(x);
        z=H*x+v;
//        printVec(z);
        pf.UpdateModel();
        pf.UpdateMeasure(H,R,z);
        pf.GetState(X);
        printf("Measu:%.1f,%.1f\n",z[0],z[1]);
        printf("State:%.1f,%.1f,%.1f,%.1f\n",x[0],x[1],x[2],x[3]);
        printf("Esti :%.1f,%.1f,%.1f,%.1f\n",X[0],X[1],X[2],X[3]);
        fprintf(fstate,"%.1f %.1f %.1f %.1f\n",x[0],x[1],x[2],x[3]);
        fprintf(festi,"%.1f %.1f %.1f %.1f\n",X[0],X[1],X[2],X[3]);
        printf("\n");
    }
    fclose(fstate);
    fclose(festi);
    printf("*****End Particle Filter Test!*****\n\n");
}
void pftest()
{
    test1();
    test2();
}
