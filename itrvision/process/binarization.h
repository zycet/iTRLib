#ifndef BINARIZATION_H
#define BINARIZATION_H
#include "itrbase.h"

using itr_math::Matrix;
namespace itr_vision
{
class Binarization
{
public:
    /**
    * \brief 对图像做二值化
    * \param input 输入图像
    * \param DThreshold 阈值下限
    * \param UThreshold 阈值上限
    */
    static void Threshold(Matrix &input,F32 DThreshold,F32 HThreshold);
protected:
private:
};
}
#endif // THRESHOLD_H
