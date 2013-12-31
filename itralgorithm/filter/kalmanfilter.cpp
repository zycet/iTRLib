#include "kalmanfilter.h"
#include <math.h>
#include <stdio.h>
namespace itr_algorithm
{
    KalmanFilter::KalmanFilter()
    {
        _dimState=-1;
    }
    void KalmanFilter::Init(S32 DimState)

    {
        x.Init(DimState);
        F_x.Init(DimState,DimState);
        F_n.Init(DimState,DimState);
        Q.Init(DimState,DimState);
        P.Init(DimState,DimState);
        _dimState=DimState;
        F_n.SetDiag(1);
        P.SetDiag(0.1);
        Q.SetDiag(0.1);

    }
    void printVec(Vector a)
    {
        printf("%d : ",a.GetDim());
        for(int i=0; i<a.GetDim(); ++i)
        {
            printf("%.0f,",a[i]);
        }
        printf("\n");
    }

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
    void KalmanFilter::UpdateModel()
    {
        x=F_x*x;
//    printVec(x);
        P=F_x*P*F_x.Tran()+Q;
//        printMatrix(P);
    }

    Vector KalmanFilter::UpdateMeasure(const Matrix &H,const Matrix &R,const Vector &z)
    {
        Matrix K(H.GetCol(),H.GetRow());
//        printMatrix(K);
        K=P*H.Tran()*((H*P*H.Tran()+R).Inv());
//        printMatrix(K);

        P=P-K*H*P;
//         printMatrix(H);
//        printMatrix(P);
//        printMatrix(K);
//         printVec(z);
//        printVec(x);
        x=x+K*(z-H*x);

        return x;
    }
}
