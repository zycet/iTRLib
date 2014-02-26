#include "convolutefasttest.h"
#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include <iostream>
#include <sys/time.h>


#define TEST_CYC 50

#define filtervalue 0.33333
#define  filterN 5
//using namespace std;
//using namespace itr_math;
void TestComparefast()
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
    ConvoluteFast con;
    con.Init( filterN, grayI.GetWidth(),grayI.GetHeight());
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        con.Convolute(gray_matrix_in, Filter, graym_matrix_out);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    printf("\n fast : %f\n",timeuse);
    TRACE_DEBUG(timeuse);
    //Verify

}
void TestComparesquare()
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
    ConvoluteSquare conv;
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        conv._KLTComputeSmoothedImage(gray_matrix_in, 0.7, graym_matrix_out);//Input sigma Output
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;

    printf("\n square : %f\n",timeuse);
    TRACE_DEBUG(timeuse);
    //Verify

}

void ConvoluteFastTest()
{


    PRINT_DEBUG("!!!fast!!!");
   // itr_math::MathNeonObjStandInit();
    TestComparefast();
    //itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!square!!!");
   // itr_math::MathObjStandInit();
    TestComparesquare();
   // itr_math::MathObjStandDeinit();




    //ConvertFormat::Matrix2ImageGray(graym_matrix_out,grayO);

    //IOHelper::WritePGMFile("grayconvlute1.pgm", grayO);

    TRACE_INFO("OK ConvoluteFast");
}
