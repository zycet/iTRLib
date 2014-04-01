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
        n(DimState),
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
        P.SetDiag(1);
        Q.SetDiag(1);
        mu=0;
        sigma2=1;
    }
    void KalmanFilter::Init_noise(F32 miu,F32 sig2)
    {
        mu=miu;
        sigma2=sig2;
        Q.SetDiag(sigma2);
    }
    Vector KalmanFilter::UpdateModel()
    {
    /// TODO: n new value,nuw public miyou,sigma
        for(S32 i=0; i<_dimState; i++)
        {
            itr_math::NumericalObj->RandGaussian(n[i]);
            n[i]=n[i]*sigma2+mu;
        }
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
