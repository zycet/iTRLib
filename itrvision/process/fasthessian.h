#ifndef FASTHESSIAN_H
#define FASTHESSIAN_H
#include "itrbase.h"
#include "vectorfeaturepoint.h"
#include <vector>
using itr_math::Matrix;
namespace itr_vision
{
class FastHessian
{
    public:
        FastHessian(Matrix &img,
                    std::vector<VectorFeaturePoint> &ipts,
                    const int octaves = 5,
                    const int intervals = 4 ,
                    const int init_sample = 2,
                    const float thres = 0.0004f );

        ~FastHessian();


        void saveParameters(const int octaves,
                            const int intervals,
                            const int init_sample,
                            const float thres);

        void setIntImage(Matrix *img);

        void getIpoints();
    protected:
    private:
};
}
#endif // INTEGRALIMG_H
