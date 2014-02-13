#include "integralimg.h"
#include "itrbase.h"
#include <math.h>

namespace itr_vision
{

    void IntegralImg::Normal(const Matrix &input,Matrix &output)
    {

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
                result += IData[j + i*row];
                OData[j + i*row] = result + OData[i+j-1];
            }
        }

    }

    void IntegralImg::Square(const Matrix &input,Matrix &output)
    {

        S32 row = input.GetRow();
        S32 col = input.GetCol();
        F32 *IData = input.GetData();
        F32 *OData = output.GetData();
        F32 result = 0.0f;

        for(S32 j=0; j<col; j++)
        {
            result += IData[j]*IData[j];
            OData[j] = result;
        }
        for(S32 i=1; i <row; i++)
        {
            for(S32 j=0; j<col; j++)
            {
                result += IData[i + j*row] * IData[i + j*row];
                OData[j + i*row] = result + OData[i-1+j];
            }
        }

    }

    void BoxIntergral(const Matrix &output, S32 row, S32 col, S32 rows, S32 cols,F32 & result)
    {
        S32 r1 = std::min(row,          output.GetRow()) - 1;
        S32 c1 = std::min(col,          output.Getcol())  - 1;
        S32 r2 = std::min(row + rows,   output.GetRow()) - 1;
        S32 c2 = std::min(col + cols,   output.Getcol())  - 1;

        F32 *OData = output.GetData();

        F32 A = OData[r1 * output.Getcol() + c1];
        F32 B = OData[r1 * output.Getcol() + c2];
        F32 C = OData[r2 * output.Getcol() + c1];
        F32 D = OData[r2 * output.Getcol() + c2];

        result = A + D - B - C;

    }
}
