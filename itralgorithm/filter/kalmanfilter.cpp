#include "kalmanfilter.h"
#include <math.h>

namespace itr_algorithm
{
    KalmanFilter::KalmanFilter(S32 DimState,S32 DimMeasure):
            F_x(DimState,DimState),F_n(DimState,DimState),H(DimMeasure,DimState),
            Q(DimState,DimState),R(DimState,DimState),P(DimState,DimState),K(DimState,DimState),
            x(DimState)
    {
        _dimMeasure=DimMeasure;
        _dimState=DimState;
        q=1;
        r=1;
        P.MatEye(1);
        Q.MatEye(1);
        R.MatEye(1);
        F_n.MatEye(1);

    }

    Vector KalmanFilter::Update(const Vector& z)
    {
        x=F_x*x;
        P=F_x*P*F_x.trans()+F_n*Q*F_n.trans();
        K=P*H.trans()*((H*P*H.trans()+R).inv());
        P=P-K*H*P;
        x=x+K*(z-H*x);
        return x;
    }
}
