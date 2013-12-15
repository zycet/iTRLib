#include "kalmanfilter.h"
#include <math.h>
#include <stdio.h>
namespace itr_algorithm
{
    KalmanFilter::KalmanFilter(S32 DimState):
            x(DimState),
            F_x(DimState,DimState),F_n(DimState,DimState),
            Q(DimState,DimState),R(DimState,DimState),P(DimState,DimState),K(DimState,DimState)

    {
        _dimState=DimState;
        F_n.MatEye(1);
        P.MatEye(1);
        Q.MatEye(1);
        R.MatEye(1);

    }

    void KalmanFilter::UpdateModel()
    {
        x=F_x*x;
        P=F_x*P*F_x.Tran()+F_n*Q*F_n.Tran();
        printf("%.0f , %.0f\n",x[0],x[1]);
    }

    Vector KalmanFilter::UpdateMeasure(const Matrix &H,const Vector& z)
    {
        K=P*H.Tran()*((H*P*H.Tran()+R).Inv());
        P=P-K*H*P;
        x=x+K*(z-H*x);
        return x;
    }
}
