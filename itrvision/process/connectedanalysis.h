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
            ConnectedAnalysis(const Matrix& input);
            ~ConnectedAnalysis();
            void Contour(const Matrix &input,Matrix &output,vector<Block> &blocks);
            void Fill(const Matrix &input,S32 x,S32 y,F32 room,Block &blk,F32* f,S32 &area);
            bool Fit(F32 Val);
            void SetPara(F32 Threhold,F32 Diff);
            void SetPixelVal(Matrix& Output,F32* Val);
            void SortBlocks(vector<Block> &blocks);

            const int dx[9] = {-1,0,1,-1,1,-1,0,1};
            const int dy[8] = {-1,-1,-1,0,0,1,1,1};
            F32 Threshold;
            F32 Diff;
            F32 f[1000*1000] = {0};
            S32 ImgWidth;
            S32 ImgHeight;
            S32 BNum;
        protected:
        private:

    };
}
#endif // CONNECTEDANALYSIS_H
