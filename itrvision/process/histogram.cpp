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

}




