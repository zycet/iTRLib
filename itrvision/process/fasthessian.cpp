#include "fasthessian.h"
#include "responselayer.h"
#include "itrbase.h"
#include "vectorfeaturepoint.h"
#include <vector>
#include "integralimg.h"

namespace itr_vision
{
FastHessian::FastHessian(std::vector<VectorFeaturePoint> &ipts,
                         const int octaves, const int intervals, const int init_sample,
                         const float thresh)
    : ipts(ipts), i_width(0), i_height(0)
{
    saveParameters(octaves, intervals, init_sample, thresh);
}

FastHessian::FastHessian(Matrix &img, std::vector<VectorFeaturePoint> &ipts,
                         const int octaves, const int intervals, const int init_sample,
                         const float thresh)
    : ipts(ipts), i_width(0), i_height(0)
{
    saveParameters(octaves, intervals, init_sample, thresh);
    setIntImage(img);
}

FastHessian::~FastHessian()
{
    for (unsigned int i = 0; i < responseMap.size(); ++i)
    {
        delete responseMap[i];
    }
}

void FastHessian::saveParameters(const int octaves, const int intervals,
                                 const int init_sample, const float thresh)
{
    this->octaves =
        (octaves > 0 && octaves <= 4 ? octaves : OCTAVES);
    this->intervals =
        (intervals > 0 && intervals <= 4 ? intervals : INTERVALS);
    this->init_sample =
        (init_sample > 0 && init_sample <= 6 ? init_sample : INIT_SAMPLE);
    this->thresh = (thresh >= 0 ? thresh : THRES);
}

void FastHessian::setIntImage(Matrix &img)
{
    this->img = img;

    i_height = img.GetRow();
    i_width = img.GetCol();
}

void FastHessian::getIpoints()
{
    static const int filter_map [OCTAVES][INTERVALS] = {{0,1,2,3}, {1,3,4,5}, {3,5,6,7}, {5,7,8,9}, {7,9,10,11}};
    ipts.clear();
    buildResponseMap();
    ResponseLayer *b, *m, *t;
    for (int o = 0; o < octaves; ++o) for (int i = 0; i <= 1; ++i)
        {
            b = responseMap.at(filter_map[o][i]);
            m = responseMap.at(filter_map[o][i+1]);
            t = responseMap.at(filter_map[o][i+2]);

            for (int r = 0; r < t->height; ++r)
            {
                for (int c = 0; c < t->width; ++c)
                {
                    if (isExtremum(r, c, t, m, b))
                    {
                        interpolateExtremum(r, c, t, m, b);
                    }
                }
            }
        }
}
void FastHessian::buildResponseMap()
{

    for(unsigned int i = 0; i < responseMap.size(); ++i)
        delete responseMap[i];
    responseMap.clear();

    int w = (i_width / init_sample);
    int h = (i_height / init_sample);
    int s = (init_sample);

    if (octaves >= 1)
    {
        responseMap.push_back(new ResponseLayer(w,   h,   s,   9));
        responseMap.push_back(new ResponseLayer(w,   h,   s,   15));
        responseMap.push_back(new ResponseLayer(w,   h,   s,   21));
        responseMap.push_back(new ResponseLayer(w,   h,   s,   27));
    }

    if (octaves >= 2)
    {
        responseMap.push_back(new ResponseLayer(w/2, h/2, s*2, 39));
        responseMap.push_back(new ResponseLayer(w/2, h/2, s*2, 51));
    }

    if (octaves >= 3)
    {
        responseMap.push_back(new ResponseLayer(w/4, h/4, s*4, 75));
        responseMap.push_back(new ResponseLayer(w/4, h/4, s*4, 99));
    }

    if (octaves >= 4)
    {
        responseMap.push_back(new ResponseLayer(w/8, h/8, s*8, 147));
        responseMap.push_back(new ResponseLayer(w/8, h/8, s*8, 195));
    }

    if (octaves >= 5)
    {
        responseMap.push_back(new ResponseLayer(w/16, h/16, s*16, 291));
        responseMap.push_back(new ResponseLayer(w/16, h/16, s*16, 387));
    }

    for (unsigned int i = 0; i < responseMap.size(); ++i)
    {
        buildResponseLayer(responseMap[i]);
    }
}
/*void FastHessian::buildResponseLayer(ResponseLayer *rl)
{
    float *responses = rl->responses;
    unsigned char *laplacian = rl->laplacian;
    int step = rl->step;
    int b = (rl->filter - 1) / 2;
    int l = rl->filter / 3;
    int w = rl->filter;
    float inverse_area = 1.f/(w*w);
    float Dxx, Dyy, Dxy;

    for(int r, c, ar = 0, index = 0; ar < rl->height; ++ar)
    {
        for(int ac = 0; ac < rl->width; ++ac, index++)
        {
            r = ar * step;
            c = ac * step;

            Dxx = BoxIntegral(img, r - l + 1, c - b, 2*l - 1, w)
                  - BoxIntegral(img, r - l + 1, c - l / 2, 2*l - 1, l)*3;
            Dyy = BoxIntegral(img, r - b, c - l + 1, w, 2*l - 1)
                  - BoxIntegral(img, r - l / 2, c - l + 1, l, 2*l - 1)*3;
            Dxy = + BoxIntegral(img, r - l, c + 1, l, l)
                  + BoxIntegral(img, r + 1, c - l, l, l)
                  - BoxIntegral(img, r - l, c - l, l, l)
                  - BoxIntegral(img, r + 1, c + 1, l, l);

            Dxx *= inverse_area;
            Dyy *= inverse_area;
            Dxy *= inverse_area;

            responses[index] = (Dxx * Dyy - 0.81f * Dxy * Dxy);
            laplacian[index] = (Dxx + Dyy >= 0 ? 1 : 0);

#ifdef RL_DEBUG
            rl->coords.push_back(std::make_pair<int,int>(r,c));
#endif
        }
    }
}*/
}




