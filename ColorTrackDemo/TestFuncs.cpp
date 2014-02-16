#include "TestFuncs.h"
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

void ReadFromFile(ifstream &File,F32* data,S32 Length)
{
    for(S32 i = 0;i < Length;i++)
        File >> data[i];
}

void PrintTargetInfo(Block blk)
{
    cout << "The center of target is: " << endl;
    cout << "x: " << blk.x << " " << "y: " << blk.y << endl;
    cout << endl;
}

void CheckOpennable(ifstream &infile)
{
    if(!infile)
    {
        cout << "Unable to open infile";
        exit(1);
    }
}

void AddFileName(ifstream &infile,string filename,vector<string> &filenames)
{
    while(getline(infile,filename,'\n'))
    {
        filenames.push_back(filename);
    }
}
void TestTrack(ifstream &infile,S32 Width,S32 Height)
{
    MathObjStandInit();
    Binarization BObject;
    ConnectedAnalysis CAObject;
    vector<Block> blocks;
    Matrix Input(Width, Height);
    F32 Data[25] = {0};

    /*1.read from file to Matrix
    /*2.Binarization
    /*3.ConnectedAnalysis
    /*4.Output the target coordinate*/

    ReadFromFile(infile,Data,Width*Height);
    for(S32 j = 0;j < Width*Height;j++)
    {
        Input.GetData()[j] = Data[j];
    }
    BObject.Threshold(Input,15,5);
    CAObject.Contour(Input,blocks);
    PrintMatrix(Input);
    PrintTargetInfo(blocks[1]);//打印第二大联通域中心，即目标中心
}
