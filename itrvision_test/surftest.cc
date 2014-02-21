#include "surftest.h"
#include "iohelper.h"
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

    ImageGray grayI;
    IOHelper::ReadPGMFile("SurfTest.pgm", grayI);
    ImageGray grayO(grayI.GetWidth(),grayI.GetHeight());

    Matrix gray_matrix_in(grayI.GetWidth(),grayI.GetHeight());
    Matrix graym_matrix_out(grayI.GetWidth(),grayI.GetHeight());

    ConvertFormat::ImageGray2Matrix(grayI,gray_matrix_in);

    SURF surf;
    surf.Init(grayI.GetWidth(),grayI.GetHeight(),5,4,2,10.f);

    std::vector<VectorFeaturePoint> FeaturePointList;
    gettimeofday(&tpstart,NULL);
    surf.Process(gray_matrix_in, FeaturePointList);
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    printf("\n fast : %f\n",timeuse);
    TRACE_DEBUG(timeuse);
    for(S32 i=0; i<FeaturePointList.size(); i++ )
    {
        VectorFeaturePoint p=FeaturePointList[i];
        PRINT_DEBUG(p.X);
        PRINT_DEBUG(p.Y);
        PRINT_DEBUG(p.Feature[0]);
        PRINT_DEBUG(p.Scale);
        for(S32 j=0; j<64; j++)
        {
            PRINT_DEBUG(p.Feature[j]);
        }
    }
    int kkk;
    std::cin>>kkk;
}

void SurfTest()
{
    PRINT_DEBUG("Find Interesting points!");
    TestIpts();
}
