#include "surftest.h"
#include "matrixdraw.h"
#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include <iostream>
#include <sys/time.h>
#include <vector>


void TestIpts()
{
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;

    itr_math::MathObjStandInit();

    Matrix grayI;
    itr_vision::IOpnm::ReadPGMFile("img3.pgm", grayI);
    Matrix grayO(grayI.GetCol(),grayI.GetRow());

    Matrix gray_matrix_in(grayI.GetCol(),grayI.GetRow());

    //ConvertFormat::ImageGray2Matrix(grayI,gray_matrix_in);
    gray_matrix_in=grayI;
    gray_matrix_in.AllMul(1/255.f);
    itr_vision::SURF surf;
    surf.Init(grayI.GetCol(),grayI.GetRow(),5,4,2,0.0004f);


    std::vector<VectorFeaturePoint> FeaturePointList;
    gettimeofday(&tpstart,NULL);

    surf.Process(gray_matrix_in, FeaturePointList);
    MatrixDraw(surf.OctaveList[0]->GetCol(),surf.OctaveList[0]->GetRow(),surf.OctaveList[0]->Hessian);

    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    printf("\n fast : %f\n",timeuse);
    PRINT_DEBUG(FeaturePointList.size());
    TRACE_DEBUG(timeuse);
    for(S32 i=0; i<FeaturePointList.size(); i++ )
    {
        VectorFeaturePoint p=FeaturePointList[i];
        PRINT_DEBUG(p.X);
        PRINT_DEBUG(p.Y);
        PRINT_DEBUG(p.LevelNo);
        PRINT_DEBUG(p.Dir);
        PRINT_DEBUG(p.Value);
        PRINT_DEBUG(p.Quality);
        PRINT_DEBUG(p.Dir);
        for(S32 j=0; j<64; j++)
        {
            PRINT_DEBUG(p.Feature[j]);
        }


    }
    int kkk;
    std::cin>>kkk;
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

}
