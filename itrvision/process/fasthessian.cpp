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
}




