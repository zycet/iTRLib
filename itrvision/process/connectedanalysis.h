#ifndef CONNECTEDANALYSIS_H
#define CONNECTEDANALYSIS_H

#include "itrbase.h"
#include <vector>
#include "../feature/block.h"
using std::vector;
using itr_math::Matrix;
namespace itr_vision
{
class ConnectedAnalysis
{
    public:
        /**
        * \brief 对图像做连通域分析
        * \param input 输入图像
        * \param output 经过分析后的图像，每个像素点的值代表该点所属的连通域
        * \param blocks 所有连通域的信息，按面积从大到小排序
        */
        static void Do(const Matrix &input,Matrix &output,vector<Block> &blocks);
    protected:
    private:
};
}
#endif // CONNECTEDANALYSIS_H
