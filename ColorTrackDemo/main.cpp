#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "itrbase.h"
#include "itrvision.h"
using namespace std;
using namespace itr_vision;
using namespace itr_math;
void PrintMatrix(Matrix Mat)
{
    int Width = Mat.GetCol();
    int Height = Mat.GetRow();
    for(int i = 0;i<Height;i++)
    {
        for(int j = 0;j<Width;j++)
        {
            cout << Mat.GetData()[i*Width+j]<<" ";
        }
        cout << endl;
    }
}
void PrintBlocks(vector<Block> blocks,S32 BlkNum)
{
    for(int i=0;i<BlkNum;i++)
    {
        cout << "Blocks " << i <<":"<<endl;
        cout << "    " << "x:"<<blocks[i].x<<endl;
        cout << "    " << "y:"<<blocks[i].y<<endl;
        cout << "    " << "Area:" <<blocks[i].Area<<endl;
    }
    cout << endl;
}

int main()
{
    //read the input file (simulate the matrix)
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    if(!infile)
    {
        cout << "Unable to open infile";
        exit(1);
    }
    if(!outfile)
    {
        cout << "Unable to open outfile";
        exit(1);
    }

    const S32 width  = 20;
    const S32 height = 20;
    F32 data[width*height];
    for(S32 i = 0;i < height;i++)
        for(S32 j = 0;j < width;j++)
        {
            infile >> data[i*height+j];
        }
    infile.close();

    for(S32 i = 0;i < height;i++)
    {
        for(S32 j = 0;j < width;j++)
        {
            cout << data[i*height+j] << " ";
        }
        cout << endl;
    }
    //init a connectedanalysis object, and do the Contour correlated work
    MathObjStandInit();
    Matrix Input(width, height, data);
    Matrix Output(width, height);
    vector<Block> blocks;
    //Binarization
    Binarization BObject;
    BObject.Threshold(Input,15,5);
    cout << "**********************"<<endl;
    PrintMatrix(Input);
    //ConnectedAnalysis
    ConnectedAnalysis CAObject;
    CAObject.Contour(Input,blocks);
    //print the result of the Contour
    cout << endl;
    cout << "The blocks information:"<<endl;
    cout << "There are "<<blocks.size()<<" blocks !"<<endl;
    PrintBlocks(blocks,CAObject.BNum);
    return 0;
}
