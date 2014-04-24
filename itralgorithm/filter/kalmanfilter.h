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

            ///观测矩阵,观测向量
            Vector UpdateModel(const Matrix &Q,const Vector &n);
            Vector UpdateMeasure(const Matrix& H,const Matrix &R,const Vector& z);
            ///状态变量
            Vector x,n;
            ///状态转移矩阵，噪声矩阵
            Matrix F_x,F_n;
            ///卡尔曼方差阵
            Matrix P;
        private:
        S32 _dimState;

    };
}
#endif // KALMANFILTER_H
