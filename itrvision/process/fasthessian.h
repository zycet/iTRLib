#ifndef FASTHESSIAN_H
#define FASTHESSIAN_H
#include "itrbase.h"
#include "./feature.h"
using itr_math::Matrix;
class FastHessian
{
    public:
        FastHessian(Matrix &img
                    std::vector<Ipoint> &ipts,
                    const int octaves = 5,
                    const int intervals = 4,
                    const int init_sample = 8,
                    const float thres = 0.0004f);
         ~FastHessian();
         void saveParameters(const int octaves,
                             const int intervals,
                             const int init_sample,
                             const float thres);
         void setIntImage(Matrix &img);
         void getIpoints();
    protected:
    private:
};

#endif // INTEGRALIMG_H
