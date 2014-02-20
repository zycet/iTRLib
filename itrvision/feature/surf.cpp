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

S32 SURF::Process(const Matrix& Img,std::vector<VectorFeaturePoint> FeaturePointList)
{
    //Calc Integral Image
    itr_vision::IntegralImg::Integral(Img,IntImg);
    //Calc Hessian in OctaveList
    for(S32 i=0; i<(S32)OctaveList.size(); i++)
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
    F32 scale=0.1333f * m->FilterLength;
    VectorFeaturePoint vfp;
    vfp.Init(pos,0,0,laplacian,hessian,64,step,scale);
    GetOrientation(vfp);
    GetDescriptor(vfp);
}

S32 fRound(float flt)
{
    return (S32)floor(flt+0.5f);
}

float getAngle(float X, float Y)
{
    const F32 pi = 3.14159f;
    if(X > 0 && Y >= 0)
        return atan(Y/X);

    if(X < 0 && Y >= 0)
        return pi - atan(-Y/X);

    if(X < 0 && Y < 0)
        return pi + atan(Y/X);

    if(X > 0 && Y < 0)
        return 2*pi - atan(-Y/X);

    return 0;
}

F32 gaussian(int x, int y, float sig)
{
    const F32 pi = 3.14159f;
    return (1.0f/(2.0f*pi*sig*sig)) * exp( -(x*x+y*y)/(2.0f*sig*sig));
}


F32 SURF::HaarX(S32 row, S32 column, S32 s)
{
    return IntegralImg::BoxFilterStarter(IntImg, row-s/2, column, s, s/2)
           - IntegralImg::BoxFilterStarter(IntImg, row-s/2, column-s/2, s, s/2);
}

F32 SURF::HaarY(S32 row, S32 column, S32 s)
{
    return IntegralImg::BoxFilterStarter(IntImg, row, column-s/2, s/2, s)
           - IntegralImg::BoxFilterStarter(IntImg, row-s/2, column-s/2, s/2, s);
}

void SURF::GetOrientation(VectorFeaturePoint& Point)
{
    const F32 pi = 3.14159f;
    const S32 id[] = {6,5,4,3,2,1,0,1,2,3,4,5,6};
    const S32 s = fRound(Point.Scale), r =Point.Y , c = Point.X;
    std::vector<F32> resX(109), resY(109), Ang(109);

    F32 gauss = 0;
    S32 idx = 0;
    // calculate haar responses for points within radius of 6*scale
    for(S32 i = -6; i <= 6; ++i)
    {
        for(int j = -6; j <= 6; ++j)
        {
            if(i*i + j*j < 36)
            {
                gauss = static_cast<F32>(SURF_Gauss25[id[i+6]][id[j+6]]);  // could use abs() rather than id lookup, but this way is faster
                resX[idx] = gauss * HaarX(r+j*s, c+i*s, 4*s);
                resY[idx] = gauss * HaarY(r+j*s, c+i*s, 4*s);
                Ang[idx] = getAngle(resX[idx], resY[idx]);
                ++idx;
            }
        }
    }

    // calculate the dominant direction
    F32 sumX=0.f, sumY=0.f;
    F32 max=0.f, orientation = 0.f;
    F32 ang1=0.f, ang2=0.f;

    // loop slides pi/3 window around feature point
    for(ang1 = 0; ang1 < 2*pi;  ang1+=0.15f)
    {
        ang2 = ( ang1+pi/3.0f > 2*pi ? ang1-5.0f*pi/3.0f : ang1+pi/3.0f);
        sumX = sumY = 0.f;
        for(U32 k = 0; k < Ang.size(); ++k)
        {
            // get angle from the x-axis of the sample point
            const F32 & ang = Ang[k];

            // determine whether the point is within the window
            if (ang1 < ang2 && ang1 < ang && ang < ang2)
            {
                sumX+=resX[k];
                sumY+=resY[k];
            }
            else if (ang2 < ang1 &&
                     ((ang > 0 && ang < ang2) || (ang > ang1 && ang < 2*pi) ))
            {
                sumX+=resX[k];
                sumY+=resY[k];
            }
        }

        // if the vector produced from this window is longer than all
        // previous vectors then this forms the new dominant direction
        if (sumX*sumX + sumY*sumY > max)
        {
            // store largest orientation
            max = sumX*sumX + sumY*sumY;
            orientation = getAngle(sumX, sumY);
        }
    }
    Point.Dir=orientation;
}

void SURF::GetDescriptor(VectorFeaturePoint& Point)
{
    S32 y, x, sample_x, sample_y, count=0;
    S32 i = 0, ix = 0, j = 0, jx = 0, xs = 0, ys = 0;
    F32 scale, *desc, dx, dy, mdx, mdy, co, si;
    F32 gauss_s1 = 0.f, gauss_s2 = 0.f;
    F32 rx = 0.f, ry = 0.f, rrx = 0.f, rry = 0.f, len = 0.f;
    F32 cx = -0.5f, cy = 0.f; //Subregion centers for the 4x4 gaussian weighting

    scale = Point.Scale;
    x =Point.X;
    y =Point.Y;
    desc = Point.Feature.GetData();

    co = cos(Point.Dir);
    si = sin(Point.Dir);

    i = -8;

    //Calculate descriptor for this interest point
    while(i < 12)
    {
        j = -8;
        i = i-4;

        cx += 1.f;
        cy = -0.5f;

        while(j < 12)
        {
            dx=dy=mdx=mdy=0.f;
            cy += 1.f;

            j = j - 4;

            ix = i + 5;
            jx = j + 5;

            xs = fRound(x + ( -jx*scale*si + ix*scale*co));
            ys = fRound(y + ( jx*scale*co + ix*scale*si));

            for (int k = i; k < i + 9; ++k)
            {
                for (int l = j; l < j + 9; ++l)
                {
                    //Get coords of sample point on the rotated axis
                    sample_x = fRound(x + (-l*scale*si + k*scale*co));
                    sample_y = fRound(y + ( l*scale*co + k*scale*si));

                    //Get the gaussian weighted x and y responses
                    gauss_s1 = gaussian(xs-sample_x,ys-sample_y,2.5f*scale);
                    rx = HaarX(sample_y, sample_x, 2*fRound(scale));
                    ry = HaarY(sample_y, sample_x, 2*fRound(scale));

                    //Get the gaussian weighted x and y responses on rotated axis
                    rrx = gauss_s1*(-rx*si + ry*co);
                    rry = gauss_s1*(rx*co + ry*si);

                    dx += rrx;
                    dy += rry;
                    mdx += fabs(rrx);
                    mdy += fabs(rry);

                }
            }

            //Add the values to the descriptor vector
            gauss_s2 = gaussian(cx-2.0f,cy-2.0f,1.5f);

            desc[count++] = dx*gauss_s2;
            desc[count++] = dy*gauss_s2;
            desc[count++] = mdx*gauss_s2;
            desc[count++] = mdy*gauss_s2;

            len += (dx*dx + dy*dy + mdx*mdx + mdy*mdy) * gauss_s2*gauss_s2;

            j += 9;
        }
        i += 9;
    }

    //Convert to Unit Vector
    len = sqrt(len);
    for(int i = 0; i < 64; ++i)
        desc[i] /= len;

}
}
