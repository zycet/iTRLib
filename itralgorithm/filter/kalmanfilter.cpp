#include "kalmanfilter.h"
#include <math.h>
#include <stdio.h>
namespace itr_algorithm
{
    KalmanFilter::KalmanFilter(S32 DimState):
            x(DimState),
            F_x(DimState,DimState),F_n(DimState,DimState),
            Q(DimState,DimState),P(DimState,DimState)

    {
        _dimState=DimState;
        F_n.MatEye(1);
        P.MatEye(1);
        Q.MatEye(1);

    }
void printVec(Vector a)
{
        printf("%d : ",a.GetDim());
        for(int i=0;i<a.GetDim();++i)
         printf("%.0f,",a[i]);
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
        P=F_x*P*F_x.Tran()+F_n*Q*F_n.Tran();
    }

    Vector KalmanFilter::UpdateMeasure(const Matrix &H,const Matrix &R,const Vector& z)
    {
        Matrix K(H.GetCol(),H.GetRow());
        K=P*H.Tran()*((H*P*H.Tran()+R).Inv());
        P=P-K*H*P;
        x=x+K*(z-H*x);
        return x;
    }
}
