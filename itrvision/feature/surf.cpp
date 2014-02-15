#include "./surf.h"
#include <vector>
#include "itrbase.h"
#include "./feature.h"
#include "../process/process.h"

using namespace itr_math;

namespace itr_vision
{
SURF::SURF()
{
    OctaveList.clear();
    this->Threshold=SURF_THRESHOLD;
    this->OctaveNum=0;
    this->IntervalNum=0;
    this->InitSample=0;
}

SURF::~SURF()
{
    //dtor
}
void SURF::Init(S32 Width,S32 Height,S32 OctaveNum,S32 IntervalNum,S32 InitSample,F32 Threshold)
{
    assert(Width>0);
    assert(Height>0);
    assert(OctaveNum>0&&OctaveNum<=5);
    assert(IntervalNum==4);
    assert(InitSample>0);
    assert(OctaveList.size()==0);

    this->OctaveNum=OctaveNum;
    this->IntervalNum=IntervalNum;
    this->InitSample=InitSample;
    this->Threshold=Threshold;

    // Get image attributes
    S32 w = (Width / InitSample);
    S32 h = (Height / InitSample);
    S32 s = (InitSample);

    // Calculate responses for the first 4 OctaveNum:
    // Oct1: 9,  15, 21, 27
    // Oct2: 15, 27, 39, 51
    // Oct3: 27, 51, 75, 99
    // Oct4: 51, 99, 147,195
    // Oct5: 99, 195,291,387

    // Calculate approximated determinant of hessian values
    BoxHessian* bh;
    if (OctaveNum >= 1)
    {
        bh=new BoxHessian();
        bh->Init(w,h,s,9);
        OctaveList.push_back(bh);

        bh=new BoxHessian();
        bh->Init(w,h,s,15);
        OctaveList.push_back(bh);

        bh=new BoxHessian();
        bh->Init(w,h,s,21);
        OctaveList.push_back(bh);

        bh=new BoxHessian();
        bh->Init(w,h,s,27);
        OctaveList.push_back(bh);
    }

    if (OctaveNum >= 2)
    {
        bh=new BoxHessian();
        bh->Init(w/2,h/2,s/2,39);
        OctaveList.push_back(bh);

        bh=new BoxHessian();
        bh->Init(w/2,h/2,s/2,51);
        OctaveList.push_back(bh);
    }

    if (OctaveNum >= 3)
    {
        bh=new BoxHessian();
        bh->Init(w/4,h/4,s/4,75);
        OctaveList.push_back(bh);

        bh=new BoxHessian();
        bh->Init(w/4,h/4,s/4,99);
        OctaveList.push_back(bh);
    }

    if (OctaveNum >= 4)
    {
        bh=new BoxHessian();
        bh->Init(w/8,h/8,s/8,147);
        OctaveList.push_back(bh);

        bh=new BoxHessian();
        bh->Init(w/8,h/8,s/8,195);
        OctaveList.push_back(bh);
    }

    if (OctaveNum >= 5)
    {
        bh=new BoxHessian();
        bh->Init(w/16,h/16,s/16,291);
        OctaveList.push_back(bh);

        bh=new BoxHessian();
        bh->Init(w/16,h/16,s/16,387);
        OctaveList.push_back(bh);
    }
    IntImg.Init(Width,Height);
}

BOOL SURF::IsExtremum(S32 r, S32 c, BoxHessian *t, BoxHessian *m, BoxHessian *b)
{
    // bounds check
    S32 layerBorder = (t->FilterLength + 1) / (2 * t->Step);
    if (r <= layerBorder || r >= t->GetHeight() - layerBorder || c <= layerBorder || c >= t->GetWidth() - layerBorder)
        return false;

    // check the candidate point in the middle layer is above thresh
    float candidate = m->GetHessian(r, c, t);
    if (candidate < Threshold)
        return false;

    for (S32 rr = -1; rr <=1; ++rr)
    {
        for (S32 cc = -1; cc <=1; ++cc)
        {
            // if any response in 3x3x3 is greater candidate not maximum
            if (
                t->GetHessian(r+rr, c+cc) >= candidate ||
                ((rr != 0 || cc != 0) && m->GetHessian(r+rr, c+cc, t) >= candidate) ||
                b->GetHessian(r+rr, c+cc, t) >= candidate
            )
                return false;
        }
    }
    return true;
}

void SURF::MakeFeaturePoint(S32 r, S32 c, BoxHessian *t, BoxHessian *m, BoxHessian *b)
{
    //vfp=pos=位置
    //vfp.Dir=dir=方向?
    //vfp.LevleNo=step=尺度
    //vfp.Value=hessian
    //vfp.Quality=laplacian
    //vfp.Feature=向量

    Point2D pos=Point2D(c*t->Step,r*t->Step);//?
    S32 step=m->Step;
    F32 hessian=m->GetHessian(r,c,t);
    F32 laplacian=m->GetLaplacian(r,c,t);
    VectorFeaturePoint vfp;
    vfp.Init(pos,0,0,laplacian,hessian,64,step);
    //CalcFeatureDir(r,c,m,vfp.Feature,&vfp.Dir);
}

S32 SURF::Process(const Matrix& Img,std::vector<VectorFeaturePoint> FeaturePointList)
{
    //Calc Integral Image
    itr_vision::IntegralImg::Integral(Img,IntImg);
    //Calc Hessian in OctaveList
    for(S32 i=0; i<OctaveList.size(); i++)
    {
        OctaveList[i]->Calc(IntImg);
    }

    //Search Interest Point
    S32 pointNum=0;
    BoxHessian *b, *m, *t;//Get the response layers
    for (S32 o = 0; o < OctaveNum; ++o)
    {
        for (S32 i = 0; i <= 1; ++i)
        {
            b = OctaveList.at(SURF_Filter_Map[o][i]);
            m = OctaveList.at(SURF_Filter_Map[o][i+1]);
            t = OctaveList.at(SURF_Filter_Map[o][i+2]);

            // loop over middle response layer at density of the most
            // sparse layer (always top), to find maxima across scale and space
            for (S32 r = 0; r < t->GetHeight(); r++)
            {
                for (S32 c = 0; c < t->GetWidth(); c++)
                {
                    if (IsExtremum(r, c, t, m, b))
                    {
                        MakeFeaturePoint(r,c,t,m,b);
                        pointNum++;
                    }
                }
            }
        }
    }
    return pointNum;
}
}
