#include "integralimg.h"

void IntegralImg::Normal(const Matrix &input,Matrix &output)
{
    /*
    S32 row = input.GetRow();
    S32 col = input.GetCol();
    F32 *IData = input.GetData();
    F32 *OData = output.GetData();
    F32 result = 0.0f;

    for(S32 j=0; j <col; j++)
    {
        result += IData[j];
        OData[j] = result;
    }
    for(S32 i=1; i<row; i++)
    {
        result = 0.0f;
        for(S32 j=0; j<col; j++)
        {
            result += Data[j + i*row];
            OData[j + i*row] = result + OData[(i-1)*step+j];
        }
    }
*/
}

void IntegralImg::Square(const Matrix &input,Matrix &output)
{
    /*
    S32 row = input.GetRow();
    S32 col = input.GetCol();
    F32 *Data = input.GetData();
    F32 *OData = output.GetData();
    F32 result = 0.0f;

    for(S32 j=0; j<col; j++)
    {
        result += IData[j]*IData[j];
        OData[j] = result;
    }
    for(S32 i=1; i <row; i++)
    {
        for(S32 i=0; i <col; i++)
        {
            result += Data[i + j*row] * Data[i + j*row];
            OData[j + i*row] = result + OData[(i-1)*step+j];
        }
    }
    */
}
