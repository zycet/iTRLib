#include "surftest.h"
#include "matrixdraw.h"
#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include <iostream>
#include <sys/time.h>
#include <vector>

using namespace itr_vision;
using namespace itr_math;

void TestIpts()
{
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;

    itr_math::MathObjStandInit();

    Matrix gray_matrix_in;
    IOpnm::ReadPGMFile("img3.pgm", gray_matrix_in);
    S32 w=gray_matrix_in.GetCol();
    S32 h=gray_matrix_in.GetRow();
    gray_matrix_in.AllMul(1/255.f);

    SURF surf;
    surf.Init(w,h,5,4,2,0.0004f);

    std::vector<VectorFeaturePoint> FeaturePointList;
    gettimeofday(&tpstart,NULL);
    surf.ProcessAll(gray_matrix_in, FeaturePointList);
    //MatrixDraw(surf.OctaveList[0]->GetCol(),surf.OctaveList[0]->GetRow(),surf.OctaveList[0]->Hessian);

    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse*=0.0001f;
    PRINT_DEBUG(timeuse);
    for(S32 i=0; i<FeaturePointList.size(); i++ )
    {
        VectorFeaturePoint p=FeaturePointList[i];
        PRINT_DEBUG(p.X);
        PRINT_DEBUG(p.Y);
        PRINT_DEBUG(p.Dir);
        PRINT_DEBUG(p.Quality);
        PRINT_DEBUG(p.Value);
        PRINT_DEBUG(p.LevelNo);
        PRINT_DEBUG(p.Scale);
        for(S32 j=0; j<64; j++)
        {
            PRINT_DEBUG(p.Feature[j]);
        }
    }
}

void MatrixDrawTest()
{
    Matrix gray_matrix_in;
    IOpnm::ReadPGMFile("img2.pgm", gray_matrix_in);
    MatrixDraw(gray_matrix_in.GetCol(),gray_matrix_in.GetRow(),gray_matrix_in.GetData());
}

void InterBoxTest()
{
    Matrix img(64,64);
    img.Set(1);
    Matrix imgI(64,64);
    IntegralImg::Integral(img,imgI);
    F32 I=0;
    I=IntegralImg::BoxFilterStarter(imgI,-1,-1,3,3);
    I=IntegralImg::BoxFilterStarter(imgI,1,1,3,3);
    I=I;
}

void SurfTest()
{
    //PRINT_DEBUG("Find Interesting points!");
    TestIpts();
    //MatrixDrawTest();

    //InterBoxTest();
}
