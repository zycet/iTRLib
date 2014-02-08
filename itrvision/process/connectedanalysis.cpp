#include "connectedanalysis.h"
#include "itrbase.h"
#include <vector>
#include "../feature/block.h"
using std::vector;
using itr_math::Matrix;
namespace itr_vision
{
    ConnectedAnalysis::ConnectedAnalysis(const Matrix& input)
    {
        this->Threshold = 0;
        this->Diff = 0;
        this->BNum = 0;
        ImgWidth = input.GetCol();
        ImgHeight = input.GetRow();
    }
    ConnectedAnalysis::~ConnectedAnalysis()
    {

    }
    //Do the Contour Analysis work,i.e. get the information of each block, including x,y & area, etc.
    void ConnectedAnalysis::Contour(const Matrix &input,Matrix &output,vector<Block> &blocks)
    {
        int room = 0;
        int area = 1;
        while(++room>0)
        {
            int x=-1,y=-1;
            for(int i=0;i<ImgHeight;i++)
            {
                for(int j=0;j<ImgWidth;j++)
                if(Fit(input.GetData()[i*ImgWidth+j]) && f[i*ImgWidth+j] == 0)
                {
                    x = j;
                    y = i;
                    break;
                }
                if(x!=-1||y!=-1)
                    break;
            }
            if(x==-1&&y==-1)
            {
                //--room;
                SetPixelVal(output,f);
                SortBlocks(blocks);
                return;
            }
            blocks[BNum].x = x;
            blocks[BNum].y = y;
            Fill(input,x,y,room,blocks[BNum],f,area);
            blocks[BNum].x /= area;
            blocks[BNum].y /= area;
            blocks[BNum].Area = area;
            BNum++;
            area = 1;
        }
    }
    //Fill the connected pixel to form a block
    void ConnectedAnalysis::Fill(const Matrix &input,S32 x,S32 y,F32 room,Block& blk,F32* f,S32 &area)
    {
        f[y*ImgWidth+x] = room;
        for(int i =0;i<8;i++)
        {
            int newx = x + dx[i];
            int newy = y + dy[i];
            if(newx < 0|| newx >= ImgWidth)continue;
            if(newy < 0|| newy >= ImgHeight)continue;
            if(Fit(input.GetData()[newy*ImgWidth+newx]) && f[newy*ImgWidth+newx]==0)
            {
                area++;
                blk.x += newx;
                blk.y += newy;
                Fill(input,newx,newy,room,blk,f,area);
            }
        }
    }
    //To judge whether the pixel is aroundz the threshold
    bool ConnectedAnalysis::Fit(F32 Val)
    {
        if(Val >= Threshold && Val- Threshold <= Diff)
            return true;
        if(Val <= Threshold && Threshold - Val <= Diff)
            return true;
        else
            return false;
    }
    //Set the paras
    void ConnectedAnalysis::SetPara(F32 Threhold,F32 Diff)
    {
        this->Threshold = Threhold;
        this->Diff = Diff;
    }
    //Set the Pixel Val of the Output Img
    void ConnectedAnalysis::SetPixelVal(Matrix& Output,F32* Val)
    {
        for(int i = 0;i<Output.GetRow()*Output.GetCol();i++)
            Output.GetData()[i] = Val[i];
    }
    //Sort the block
    void ConnectedAnalysis::SortBlocks(vector<Block> &blocks)
    {
        Block BTemp;
        //blob sort
        for(int i = 0;i<BNum;i++)
        {
            for(int j =0;j<BNum - i;j++)
            if(blocks[j].Area < blocks[j+1].Area)
            {
                BTemp = blocks[j];
                blocks[j] = blocks[j+1];
                blocks[j+1] = BTemp;
            }
        }
        for(int i = 0;i<BNum;i++)
        {
            blocks[i].No = i;
        }
    }
}
