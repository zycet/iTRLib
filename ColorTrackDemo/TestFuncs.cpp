#include "TestFuncs.h"
#include <string>
using namespace std;
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
//×î´óÖµ
double Max(double a,double b)
{
    return (a>=b)?a:b;
}
//×îÐ¡Öµ
double Min(double a,double b)
{
    return (a<=b)?a:b;
}
/*
 * Class:     com_android_ColorRecognition_natiVec_2Dode
 * Method:    RGB2HSL
 * Signature: ½«Ò»¸öÏñËØµãµÄRGBÐÅÏ¢×ª»¯ÎªHSLÐÅÏ¢
 * HSL:0~1
 * RGB 0~255
 * HSL×ªRGB
 */
void RGB2HSL(int* RGB, float* HSL)
{
    float r = RGB[0] / 255.0;
    float g = RGB[1] / 255.0;
    float b = RGB[2] / 255.0;
    float v;
    float m;
    float vm;
    float r2, g2, b2;

    HSL[0] = 0;
    HSL[1] = 0;
    HSL[2] = 0;
    v = Max(r, g);
    v = Max(v, b);
    m = Min(r, g);
    m = Min(m, b);
    HSL[2] = (m + v) / 2.0;
    if (HSL[2] <= 0.0)
    {
        return;
    }
    vm = v - m;
    HSL[1] = vm;
    if (HSL[1] > 0.0)
    {
        HSL[1] /= (HSL[2] <= 0.5) ? (v + m) : (2.0 - v - m);
    }
    else
    {
        return;
    }
    r2 = (v - r) / vm;
    g2 = (v - g) / vm;
    b2 = (v - b) / vm;
    if (r == v)
    {
        HSL[0] = (g == m ? 5.0 + b2 : 1.0 - g2);
    }
    else if (g == v)
    {
        HSL[0] = (b == m ? 1.0 + r2 : 3.0 - b2);
    }
    else
    {
        HSL[0] = (r == m ? 3.0 + g2 : 5.0 - r2);
    }
    HSL[0] /= 6.0;
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

void ReadFromFile(istream &File,F32* H,F32* S,F32* L,S32 Length)
{
    int rgb[3];
    float hsl[3];
    int h1=0,h2=0;
    File>>h1>>h2;
    while(h1!=640 && h2!=360)
        {
        h1=h2;
        File>>h2;
        cout<<h1<<' '<<h2<<endl;
        }

    for(S32 i = 0;i < Length;i++)
    {
        File>>rgb[0]>>rgb[1]>>rgb[2];
        RGB2HSL(rgb,hsl);
        H[i]=hsl[0]*360;//(rgb[0]+rgb[1]*2.0+rgb[2])/4;
        if(H[i]<20) H[i]+=340;
        S[i]=hsl[1]*100;
        //L[i]=hsl[2]*255;
    }
//    for(int i=-5;i<=5;i++,cout<<endl)
//        for(int j=-5;j<=5;j++)
//            cout<<H[16+j+(9+i)*64]<<' ';
}

void PrintTargetInfo(Block blk)
{
//    cout << "The center of target is: " << endl;
//    cout << "x: " << blk.x << " " << "y: " << blk.y << endl;
//    cout << endl;
    cout<<blk.x*10<<' '<<blk.y*10<<endl;
}

void CheckOpennable(istream &infile)
{
    if(!infile)
    {
        cout << "Unable to open infile";
        exit(1);
    }
}

void AddFileName(istream &infile,string filename,vector<string> &filenames)
{
    while(getline(infile,filename,'\n'))
    {
        filenames.push_back(filename);
    }
}
void TestTrack(istream &infile,S32 Width,S32 Height)
{
    MathObjStandInit();
    Binarization BObject;
    ConnectedAnalysis CAObject;
    vector<Block> blocks;

    Matrix H( Height,Width);
    Matrix S( Height,Width);
    Matrix L( Height,Width);

    Matrix Input(Width, Height);
    const S32 size = Width*Height;
    F32 Data[size];


    /*1.read from file to Matrix
    /*2.Binarization
    /*3.ConnectedAnalysis
    /*4.Output the target coordinate*/


    ReadFromFile(infile,H.GetData(),S.GetData(),L.GetData(),Width*Height);
    //itr_vision::IOpnm::ReadPPMFile("img82.ppm",Input);
//    Matrix img(36,64);
//    itr_vision::Scale::Bilinear(Input,img);

    BObject.Threshold(H,360,330);
    BObject.Threshold(S,90,60);
    itr_vision::IOpnm::WritePGMFile("1.pgm",S);
    itr_vision::IOpnm::WritePGMFile("2.pgm",H);
    for(int i=0;i<Width*Height;++i)
        if(H[i]*S[i]<10)
            H[i]=0;
        else
            H[i]=255;
    itr_vision::IOpnm::WritePGMFile("3.pgm",H);
    CAObject.Contour(H,blocks);
    // PrintMatrix(Input);

    PrintTargetInfo(blocks[1]);//打印第二大联通域中心，即目标中心
    for(int i = 0;i<blocks.size();i++)
        cout << blocks[i].Area<<endl;
}
