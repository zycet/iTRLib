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
            KalmanFilter(int DimState,int DimMeasure);
            Vector Update(const Vector& z);
            ///状态转移矩阵，噪声矩阵，观测矩阵
            Matrix F_x,F_n,H;
            ///噪声方差阵，观测方差阵，卡尔曼方差阵,卡尔曼增益
            Matrix Q,R,P,K;
            ///状态变量，观测变量
            Vector x,z;
            ///噪声
            Vector n,v;

        private:
        S32 _dimState,_dimMeasure;
        F32 q,r;
    };
}
#endif // KALMANFILTER_H
