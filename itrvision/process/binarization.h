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
    * \brief 默认构造函数
    */
    Binarization();
    ~Binarization();
    /**
    * \brief 对图像做二值化
    * \param input 输入图像
    * \param UThreshold 阈值上限
    * \param DThreshold 阈值下限
    */
    void Threshold(Matrix &input,F32 UThreshold,F32 DThreshold);
protected:
private:
};
}
#endif // THRESHOLD_H
