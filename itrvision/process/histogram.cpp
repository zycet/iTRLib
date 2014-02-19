#include "histogram.h"
using std::vector;
using itr_math::Matrix;
using itr_math::RectangleS;
namespace itr_vision
{
Histogram::Histogram()
{

}
Histogram::~Histogram()
{

}
void Histogram::Info(const Matrix &img,vector<int> &statistic)
{
    for(S32 i = 0; i<img.GetRow()*img.GetCol(); i++)
    {
        statistic[(int)img.GetData()[i]]++;
    }
}
void Histogram::Euqal(const Matrix &input,Matrix &output)
{
    F32 fpHist[256] = {0};
    F32 eqHistTemp[256] = {0};
    S32 eqHist[256] = {0};
    S32 size = input.GetRow()*input.GetCol();
    int temp[256] = {0};
    vector<int> statistic(temp,temp+256);
    Info(input,statistic);
    for(S32 i =0; i<256; i++)
    {
        fpHist[i] = (F32)statistic[i]/(F32)size;
    }
    for(S32 i = 0; i<256; i++)
    {
        if(i = 0)
        {
            eqHistTemp[i] = fpHist[i];
        }
        else
        {
            eqHistTemp[i] = eqHistTemp[i-1]+fpHist[i];
        }
    }
    for(S32 i = 0; i < 256; i++)
    {
        eqHist[i] = (S32)(255.0 * eqHistTemp[i] + 0.5);
    }
    for(S32 i = 0; i < size; i++)
    {
        output.GetData()[i] = eqHist[(S32)input.GetData()[i]];
    }
}
void Histogram::Euqal(const Matrix &input,const RectangleS &rect,Matrix &output)
{
    int temp[256] = {0};
    vector<int> statistic(temp,temp+256);
    Matrix MatROI(rect.Height,rect.Width);
    input.CopyTo(rect.Y,rect.X,rect.Width,rect.Height,MatROI.GetData());
    Info(input,statistic);
    Euqal(MatROI,MatROI);
    MatROI.CopyTo(rect.Y,rect.X,rect.Width,rect.Height,input.GetData());
    output.CopyFrom(input.GetData());
}
}




