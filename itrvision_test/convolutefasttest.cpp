#include "convolutefasttest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include <iostream>
#include <sys/time.h>

using namespace std;
using namespace itr_math;

#define TEST_CYC 100

#define filtervalue 0.33333
#define  filterN 71
void TestCompare()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    ImageGray grayI;
    IOHelper::ReadPGMFile("table1.pgm", grayI);
    ImageGray grayO(grayI.GetWidth(),grayI.GetHeight());

    Matrix gray_matrix_in(grayI.GetWidth(),grayI.GetHeight());
    Matrix graym_matrix_out(grayI.GetWidth(),grayI.GetHeight());

    ConvertFormat::ImageGray2Matrix(grayI,gray_matrix_in);

    //Init
    F32 Filter[filterN];
    for(S32 i=0; i<filterN; i++)
    {
        *(Filter+i)=filtervalue;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Compare(a, b, err, TEST_NUM,&IsSame);

        ConvoluteFast con;
        con.Init( filterN, grayI.GetWidth(),grayI.GetHeight());
        con.Convolute(gray_matrix_in, Filter, graym_matrix_out);

        ConvoluteSquare conv;
        conv._KLTComputeSmoothedImage(Img, 0.7, img[0]);//Input sigma Output
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify

}

void ConvoluteFastTest()
{


    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestCompare();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestCompare();
    itr_math::MathObjStandDeinit();




    //ConvertFormat::Matrix2ImageGray(graym_matrix_out,grayO);

    //IOHelper::WritePGMFile("grayconvlute1.pgm", grayO);

    TRACE_INFO("OK ConvoluteFast");
}
