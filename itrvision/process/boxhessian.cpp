#include "./boxhessian.h"
#include "itrbase.h"
#include "./integralimg.h"

using itr_math::Matrix;

namespace itr_vision
{
BoxHessian::BoxHessian()
{
    this->Width=0;
    this->Height=0;
    this->Hessian=NULL;
    this->Laplacian=NULL;
}

BoxHessian::~BoxHessian()
{
    if(Hessian!=NULL)
        delete[] Hessian;
    if(Laplacian!=NULL)
        delete[] Laplacian;
}

F32* BoxHessian::GetHessianData() const
{
    return this->Hessian;
}

U8* BoxHessian::GetLaplacianData() const
{
    return this->Laplacian;
}

S32 BoxHessian::GetWidth() const
{
    return this->Width;
}

S32 BoxHessian::GetHeight() const
{
    return this->Height;
}

void BoxHessian::Init(S32 Width,S32 Height,S32 Step,S32 FilterLength)
{
    assert(Width>0);
    assert(Height>0);
    assert(Step>0);
    assert(FilterLength>0);
    assert(this->Hessian==NULL);
    assert(this->Laplacian==NULL);
    this->Width=Width;
    this->Height=Height;
    this->Step=Step;
    this->FilterLength=FilterLength;
    this->Hessian=new F32[Width*Height];
    this->Laplacian=new U8[Width*Height];
    MemoryClear(this->Hessian,Width*Height*sizeof(F32));
    MemoryClear(this->Laplacian,Width*Height*sizeof(U8));
    assert(this->Hessian!=NULL);
    assert(this->Laplacian!=NULL);
}

void BoxHessian::Calc(const Matrix& Img)
{
    //assert(Width==Img.GetCol());
    //assert(Height==Img.GetRow());

    S32 b = (this->FilterLength- 1) / 2;    // border for this filter
    S32 l = this->FilterLength / 3;         // lobe for this filter (filter size / 3)
    S32 w = this->FilterLength;             // filter size
    F32 inverse_area = 1.f/(w*w);         // normalisation factor
    F32 Dxx, Dyy, Dxy;
    S32 r,c;
    S32 offset=GET_MIN(Width/2,Height/2);
    offset=GET_MIN(offset,w);
    for(S32 ar = 0, index = 0; ar < Height; ++ar)
    {
        for(S32 ac = 0; ac < Width; ++ac, index++)
        {
            if(ar<offset)
                continue;
            if(ac<offset)
                continue;
            if(ar>=Height-offset)
                continue;
            if(ac>=Width-offset)
                continue;
            // get the image coordinates
            r = ar * Step;
            c = ac * Step;

            // Compute response components
            Dxx = IntegralImg::BoxFilterStarter(Img, r - l + 1, c - b, 2*l - 1, w)
                  - IntegralImg::BoxFilterStarter(Img, r - l + 1, c - l / 2, 2*l - 1, l)*3;
            Dyy = IntegralImg::BoxFilterStarter(Img, r - b, c - l + 1, w, 2*l - 1)
                  - IntegralImg::BoxFilterStarter(Img, r - l / 2, c - l + 1, l, 2*l - 1)*3;
            Dxy = + IntegralImg::BoxFilterStarter(Img, r - l, c + 1, l, l)
                  + IntegralImg::BoxFilterStarter(Img, r + 1, c - l, l, l)
                  - IntegralImg::BoxFilterStarter(Img, r - l, c - l, l, l)
                  - IntegralImg::BoxFilterStarter(Img, r + 1, c + 1, l, l);

            // Normalise the filter responses with respect to their size
            Dxx *= inverse_area;
            Dyy *= inverse_area;
            Dxy *= inverse_area;

            // Get the determinant of hessian response & laplacian sign
            Hessian[index] = (Dxx * Dyy - 0.81f * Dxy * Dxy);
            Laplacian[index] = (Dxx + Dyy >= 0 ? 1 : 0);
        }
    }
}

F32 BoxHessian::GetHessian(S32 RowPos,S32 ColPos) const
{
    return Hessian[RowPos * Width + ColPos];
}

F32 BoxHessian::GetHessian(S32 RowPos,S32 ColPos,BoxHessian* Scale) const
{
    S32 scale = this->GetWidth() / Scale->GetWidth();
    return this->GetHessian(RowPos*scale,ColPos*scale);
}

U8 BoxHessian::GetLaplacian(S32 RowPos,S32 ColPos) const
{
    return Laplacian[RowPos * Width + ColPos];
}

U8 BoxHessian::GetLaplacian(S32 RowPos,S32 ColPos,BoxHessian* Scale) const
{
    S32 scale = this->GetWidth() / Scale->GetWidth();
    return this->GetLaplacian(RowPos*scale,ColPos*scale);
}
}


