
#ifndef GAUSSIANGENERATE_H_
#define GAUSSIANGENERATE_H_

#include "../platform/platform.h"
#include "math.h"

namespace itr_math
{
class GaussianGenerate
{
public:
    static void Generate(F32 Sigma, S32 Length, F32* Data);
    /**
    * \brief 求高斯加权数组的建议长度
    * \param Sigma 数组中个元素的和
    */
    static S32 SuggestLength(F32 Sigma);
    /**
    * \brief 求高斯加权数组的建议长度
    * \param Sigma 数组中个元素的和
    */
    static F32 PDF(F32 mu, F32 sigma, F32 value);
};

} // namespace itr_image
#endif // GAUSSIANGENERATE_H_
