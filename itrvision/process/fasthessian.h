#ifndef FASTHESSIAN_H
#define FASTHESSIAN_H
#include "itrbase.h"
#include "vectorfeaturepoint.h"
#include <vector>
using itr_math::Matrix;

class ResponseLayer;
static const int OCTAVES = 5;
static const int INTERVALS = 4;
static const float THRES = 0.0004f;
static const int INIT_SAMPLE = 2;
namespace itr_vision
{
class FastHessian
{

public:

    FastHessian(std::vector<VectorFeaturePoint> &ipts,
                const int octaves = OCTAVES,
                const int intervals = INTERVALS,
                const int init_sample = INIT_SAMPLE,
                const float thres = THRES);

    FastHessian(Matrix &img,
                std::vector<VectorFeaturePoint> &ipts,
                const int octaves = OCTAVES,
                const int intervals = INTERVALS,
                const int init_sample = INIT_SAMPLE,
                const float thres = THRES);

    ~FastHessian();

    void saveParameters(const int octaves,
                        const int intervals,
                        const int init_sample,
                        const float thres);

    void setIntImage(Matrix &img);

    void getIpoints();

private:

    void buildResponseMap();

    void buildResponseLayer(ResponseLayer *r);

    int isExtremum(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b);

    void interpolateExtremum(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b);
    void interpolateStep(int r, int c, ResponseLayer *t, ResponseLayer *m, ResponseLayer *b,
                         double* xi, double* xr, double* xc );

    Matrix img;
    int i_width, i_height;

    std::vector<VectorFeaturePoint> &ipts;
    std::vector<ResponseLayer *> responseMap;

    int octaves;
    int intervals;
    int init_sample;
    float thresh;
};
}

#endif // INTEGRALIMG_H
