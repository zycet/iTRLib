#include "binarization.h"
#include "itrbase.h"

using itr_math::Matrix;
namespace itr_vision
{

void Binarization::Threshold(Matrix &input,F32 DThreshold,F32 UThreshold)
{
    assert(UThreshold > DThreshold);
    const S32 Width = input.GetCol();
    const S32 Height = input.GetRow();
    for(int i=0; i<Height; i++)
        for(int j=0; j<Width; j++)
        {
            if(input(i,j)>=DThreshold && input(i,j)<=UThreshold)
                input(i,j) = 255;
            else
                input(i,j) = 0;
        }
}
}

