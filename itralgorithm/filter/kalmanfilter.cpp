#include "kalmanfilter.h"
#include <math.h>
#include <stdio.h>
namespace itr_algorithm
{
    KalmanFilter::KalmanFilter()
    {
        _dimState=-1;
    }

    KalmanFilter::KalmanFilter(S32 DimState):
        x(DimState),
        F_x(DimState,DimState),
        F_n(DimState,DimState),
        P(DimState,DimState)
    {
        _dimState=-1;
    }
    void KalmanFilter::Init(S32 DimState)
    {
        x.Init(DimState);
        F_x.Init(DimState,DimState);
        F_n.Init(DimState,DimState);
        P.Init(DimState,DimState);
        _dimState=DimState;
        F_n.SetDiag(1);
        P.SetDiag(1);
    }

    Vector KalmanFilter::UpdateModel(const Matrix &Q,const Vector &n)
    {
        x=F_x*x+F_n*n;
//    printVec(x);
        P=F_x*P*F_x.Tran()+F_n*Q*F_n.Tran();
//        printMatrix(P);
        return x;
    }

    Vector KalmanFilter::UpdateMeasure(const Matrix &H,const Matrix &R,const Vector &z)
    {
        Matrix K(H.GetCol(),H.GetRow());

        K=P*H.Tran()*((H*P*H.Tran()+R).Inv());

        P=P-K*H*P;

        x=x+K*(z-H*x);

        return x;
    }
}
