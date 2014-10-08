#include "TestFuncs.h"
#include "Udp.h"
#include <string>
#include <math.h>
using namespace std;
void PrintMatrix(Matrix Mat)
{
    int Width = Mat.GetCol();
    int Height = Mat.GetRow();
    for(int i = 0; i<Height; i++)
    {
        for(int j = 0; j<Width; j++)
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
void RGB2HSL(int *RGB, float *HSL)
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
    for(int i=0; i<BlkNum; i++)
    {
        cout << "Blocks " << i <<":"<<endl;
        cout << "    " << "x:"<<blocks[i].x<<endl;
        cout << "    " << "y:"<<blocks[i].y<<endl;
        cout << "    " << "Area:" <<blocks[i].Area<<endl;
    }
    cout << endl;
}

void ReadFromFile(FILE *File,F32 *H,F32 *S,F32 *L,S32 Length)
{
    int rgb[3];
    float hsl[3];
    unsigned char p;
    char str[100];
    //string str;
    fscanf(File,"P6\n64 36\n255");
    fscanf(File,"%c",&p);
    for(S32 i = 0; i < Length; i++)
    {
        fscanf(File,"%c",&p);
        rgb[0]=p;
        fscanf(File,"%c",&p);
        rgb[1]=p;
        fscanf(File,"%c",&p);
        rgb[2]=p;
        printf("%x %x %x\n",rgb[0],rgb[1],rgb[2]);

        RGB2HSL(rgb,hsl);
        H[i]=hsl[0]*360;//(rgb[0]+rgb[1]*2.0+rgb[2])/4;
        S[i]=hsl[1]*100;
        //L[i]=hsl[2]*255;
    }
}

Udp _udp(9000);
int running=1;
char cmd[150];
Udp::UdpPackage package;


void ReadFromUdp(F32 *H,F32 *S,F32 *L,S32 Length)
{
    int rgb[3];
    float hsl[3];
    unsigned char data[128*72*2];
    int k=0;
    int len=_udp.Receive((char *)data,128*72*2);
    unsigned char w1,w2;
    char filename[15];
    sprintf(filename,"%d.ppm",running);
    FILE *fout=fopen(filename,"w");
    fprintf(fout,"P6\n128 72\n255\n");
    if(len==Length*2)
        for(S32 i = 0; i < Length; i++)
        {
            w2=data[k];
            w1=data[k+1];
            k+=2;
            rgb[0]=(w1 >> 3) & 0x1F;
            rgb[2]=w2 & 0x1F;
            rgb[1]=((w1& 0x07)<<3)|((w2>>5) & 0x07);

            rgb[0]=rgb[0]<<3;
            rgb[1]=rgb[1]<<2;
            rgb[2]=rgb[2]<<3;

            fprintf(fout,"%c%c%c",(unsigned char)(rgb[0]),(unsigned char)(rgb[1]),(unsigned char)(rgb[2]));

            RGB2HSL(rgb,hsl);
            H[i]=hsl[0]*360;//(rgb[0]+rgb[1]*2.0+rgb[2])/4;
            S[i]=hsl[1]*100;
            //L[i]=hsl[2]*255;
        }


    fclose(fout);
}


void PrintTargetInfo(Block blk)
{
//    cout << "The center of target is: " << endl;
    cout << "x: " << blk.x << " y: " << blk.y<<" area: "<<blk.Area << endl;
    cmd[0]=blk.x;
    cmd[1]=blk.y;
    cmd[2]=blk.Area;
    package.IP="127.0.0.1";
    package.port=5557;
    package.pbuffer=cmd;
    package.len=3;
    _udp.Send(package);
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
void TestTrack(FILE *infile,S32 Width,S32 Height)
{
    MathObjStandInit();
    Binarization BObject;
    ConnectedAnalysis CAObject;
    vector<Block> blocks;

    Matrix H( Height,Width);
    Matrix S( Height,Width);
    Matrix L( Height,Width);

    /*1.read from file to Matrix
    /*2.Binarization
    /*3.ConnectedAnalysis
    /*4.Output the target coordinate*/


//    ReadFromFile(infile,H.GetData(),S.GetData(),L.GetData(),Width*Height);
    ReadFromUdp(H.GetData(),S.GetData(),L.GetData(),Width*Height);
    //itr_vision::IOpnm::ReadPPMFile("img82.ppm",Input);
//    Matrix img(36,64);
//    itr_vision::Scale::Bilinear(Input,img);
    itr_vision::IOpnm::WritePGMFile("0a1.pgm",S);
    itr_vision::IOpnm::WritePGMFile("0a2.pgm",H);
    Binarization::Threshold(H,1,20);
    Binarization::Threshold(S,50,100);
    itr_vision::IOpnm::WritePGMFile("1a1.pgm",S);
    itr_vision::IOpnm::WritePGMFile("1a2.pgm",H);
    for(int i=0; i<Width*Height; ++i)
        if(H[i]*S[i]<10)
        {
            H[i]=0;
        }
        else
        {
            H[i]=255;
        }
    itr_vision::IOpnm::WritePGMFile("1a3.pgm",H);
    CAObject.Contour(H,blocks);
    // PrintMatrix(Input);

    if(blocks.size()>0&&blocks[0].Area>1)
    {
        PrintTargetInfo(blocks[0]);//打印第二大联通域中心，即目标中心
    }
    else
    {
        Block block;
        block.x=Width/2;
        block.y=Height/2;
        block.Area=0;
        PrintTargetInfo(block);
    }
//    for(int i = 0; i<blocks.size(); i++)
//    {
//        cout << blocks[i].Area<<endl;
//    }
}
