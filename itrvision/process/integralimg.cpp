#include "integralimg.h"
#include "itrbase.h"
#include <math.h>

namespace itr_vision
{
void IntegralImg::Integral(const Matrix &input,Matrix &output)
{
    assert(input.GetRow()==output.GetRow());
    assert(input.GetCol()==output.GetCol());

    S32 row = input.GetRow();
    S32 col = input.GetCol();
    F32 *IData = input.GetData();
    F32 *OData = output.GetData();
    F32 result = 0.0f;

    //计算第一行
    for(S32 j=0; j <col; j++)
    {
        result += IData[j];
        OData[j] = result;
    }

    //计算剩余行
    S32 pCurr=col,pPrev=0;
    for(S32 i=1; i<row; i++)
    {
        result = 0.0f;
        for(S32 j=0; j<col; j++)
        {
            result += IData[pCurr];
            OData[pCurr] = result + OData[pPrev];
            pCurr++;
            pPrev++;
        }
    }
}

void IntegralImg::Integral2(const Matrix &input,Matrix &output)
{
    assert(input.GetRow()==output.GetRow());
    assert(input.GetCol()==output.GetCol());

    S32 row = input.GetRow();
    S32 col = input.GetCol();
    F32 *IData = input.GetData();
    F32 *OData = output.GetData();
    F32 result = 0.0f;

    //计算第一行
    for(S32 j=0; j <col; j++)
    {
        result += IData[j]*IData[j];
        OData[j] = result;
    }

    //计算剩余行
    S32 pCurr=col,pPrev=0;
    for(S32 i=1; i<row; i++)
    {
        result = 0.0f;
        for(S32 j=0; j<col; j++)
        {
            result += IData[pCurr]*IData[pCurr];
            OData[pCurr] = result + OData[pPrev];
            pCurr++;
            pPrev++;
        }
    }
}

F32 IntegralImg::BoxFilterStarter(const Matrix &input,S32 RowPos,S32 ColPos,S32 RowNum,S32 ColNum)
{
    S32 rowMax=input.GetRow();
    S32 colMax=input.GetCol();

    S32 r1 = GET_MIN(RowPos,rowMax) - 1;
    S32 c1 = GET_MIN(ColPos,colMax) - 1;
    S32 r2 = GET_MIN(RowPos + RowNum, rowMax) - 1;
    S32 c2 = GET_MIN(ColPos + ColNum, colMax) - 1;

    F32 a=0,b=0,c=0,d=0;
    if (r1 >= 0 && c1 >= 0) a = input[r1 * colMax + c1];
    if (r1 >= 0 && c2 >= 0) b = input[r1 * colMax + c2];
    if (r2 >= 0 && c1 >= 0) c = input[r2 * colMax + c1];
    if (r2 >= 0 && c2 >= 0) d = input[r2 * colMax + c2];
    return GET_MAX(0,a-c-b+d);
}

F32 IntegralImg::BoxFilterCenter(const Matrix &input,S32 RowPos,S32 ColPos,S32 RowHalfWidth,S32 ColHalfWidth)
{
    S32 rowMax=input.GetRow();
    S32 colMax=input.GetCol();

    S32 r1 = GET_MIN(RowPos - RowHalfWidth, rowMax)-1;
    S32 c1 = GET_MIN(ColPos - ColHalfWidth, colMax)-1;
    S32 r2 = GET_MIN(RowPos + RowHalfWidth, rowMax);
    S32 c2 = GET_MIN(ColPos + ColHalfWidth, colMax);

    F32 a=0,b=0,c=0,d=0;
    if (r1 >= 0 && c1 >= 0) a = input[r1 * colMax + c1];
    if (r1 >= 0 && c2 >= 0) b = input[r1 * colMax + c2];
    if (r2 >= 0 && c1 >= 0) c = input[r2 * colMax + c1];
    if (r2 >= 0 && c2 >= 0) d = input[r2 * colMax + c2];
    return GET_MAX(0,a-c-b+d);
}
}
