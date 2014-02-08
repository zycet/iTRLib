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
                    const int octaves ,
                    const int intervals ,
                    const int init_sample ,
                    const float thres );

         ~FastHessian();

         void getIpoints();
    protected:
    private:
};

#endif // INTEGRALIMG_H
