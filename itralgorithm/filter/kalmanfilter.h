#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include "itrbase.h"
using itr_math::Matrix;
using itr_math::Vector;
namespace itr_algorithm
{
    class KalmanFilter
    {
        public:
            /** Default constructor */
            KalmanFilter();
            KalmanFilter(S32 DimState);
            void Init(S32 DimState);
            void Init_noise(F32 miu,F32 sig);
            ///观测矩阵,观测向量
            Vector UpdateModel();
            Vector UpdateMeasure(const Matrix& H,const Matrix &R,const Vector& z);
            ///状态变量
            Vector x,n;
            ///状态转移矩阵，噪声矩阵
            Matrix F_x,F_n;
            ///噪声方差阵，卡尔曼方差阵
            Matrix Q,P;
            F32 mu,sigma;
        private:
        S32 _dimState,_dimMeasure;

    };
}
#endif // KALMANFILTER_H
