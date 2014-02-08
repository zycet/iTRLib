#ifndef FASTHESSIAN_H
#define FASTHESSIAN_H
#include "itrbase.h"
#include "./feature.h"
#include <vector>
using itr_math::Matrix;
class FastHessian
{
    public:
        FastHessian(Matrix &img,
                    std::vector<Ipoint> &ipts,
                    const int octaves = 5,
                    const int intervals = 4 ,
                    const int init_sample = 2,
                    const float thres = 0.0004f );

         ~FastHessian();

         void getIpoints();
    protected:
    private:
};

#endif // INTEGRALIMG_H
