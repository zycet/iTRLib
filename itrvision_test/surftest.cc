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
    surf.Process(gray_matrix_in, FeaturePointList);
    for(S32 i=0; i<FeaturePointList.size(); i++ )
    {
        VectorFeaturePoint p=FeaturePointList[i];
        PRINT_DEBUG(p.X);
        PRINT_DEBUG(p.Y);
    }
}

void SurfTest()
{
    PRINT_DEBUG("Find Interesting points!");
    TestIpts();
}
