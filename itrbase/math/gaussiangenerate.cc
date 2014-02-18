
#include "gaussiangenerate.h"

namespace itr_math
{
void GaussianGenerate::Generate(F32 Sigma, S32 Length, F32* Data)
{
    assert(Sigma>0);
    assert(IS_ODD(Length));
    assert(Data!=NULL);
    S32 r = Length >> 1;
    F32 value = 0;
    itr_math::NumericalObj->Sqrt(2 * PI, value);
    F32 base = 1 / (value * Sigma);
    F32 sigma2 = 1 / (GET_SQUARE(Sigma) * 2);
    for (S32 i = 0; i <= r; i++)
    {
        itr_math::NumericalObj->Exp(-GET_SQUARE(r-i) * sigma2, value);
        value *= base;
        Data[i] = Data[Length - 1 - i] = value;
    }
}

S32 GaussianGenerate::SuggestLength(F32 Sigma)
{
    const F32 Sample = 3.5;
    S32 r = 0;
    itr_math::NumericalObj->Round(Sample * Sigma, r);
    return (r * 2 + 1);
}

F32 GaussianGenerate::PDF(F32 mu, F32 sigma, F32 value)
{
    F32 x = mu - value;
    sigma=1/(sigma+1e-30);
    F32 expv;
    itr_math::NumericalObj->Exp(x * x * sigma * sigma * (-0.5f), expv);
    return expv *sigma/6.28;
}

} // namespace itr_image

