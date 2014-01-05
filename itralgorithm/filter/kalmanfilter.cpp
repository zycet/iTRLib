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
        Q(DimState,DimState),
        P(DimState,DimState)
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

        K=P*H.Tran()*((H*P*H.Tran()+R).Inv());

        P=P-K*H*P;

        x=x+K*(z-H*x);

        return x;
    }
}
