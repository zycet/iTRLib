#include "integralimg.h"

void IntegralImg::Normal(const Matrix &input,Matrix &output)
{
    S32 row = input.GetRow();
    S32 col = input.GetCol();
    F32 *Data = input.GetData();
    F32 result = 0.0f;

    for(S32 j=0; j<row; j++)
    {
        for(S32 i=0; i <col; i++)
        {
            result += Data[i + j*row];
        }
    }

}

void IntegralImg::Square(const Matrix &input,Matrix &output)
{
    S32 row = input.GetRow();
    S32 col = input.GetCol();
    F32 *Data = input.GetData();
    for(S32 j=0; j<row; j++)
    {
        for(S32 i=0; i <col; i++)
        {
            result += Data[i + j*row] * Data[i + j*row];
        }
    }
}
