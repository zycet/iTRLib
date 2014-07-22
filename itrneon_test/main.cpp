#include <iostream>
#include "itrbase.h"
#include "itrneon.h"
#include <sys/time.h>

using namespace std;
using namespace itr_math;

#define TEST_CYC 100
#define TEST_NUM 300

void TestAdd()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 r[TEST_NUM];
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=125;
        b[i]=200;
        r[i]=0;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Add(a, b,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(r[i]==325);
    }
}
void TestSub()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 r[TEST_NUM];
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=125;
        b[i]=500;
        r[i]=0;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Sub(a, b,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(r[i]==-375);
    }
}

void TestMulti()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 r[TEST_NUM];
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=21;
        b[i]=9;
        r[i]=0;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Multi(a, b,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(r[i]==189);
    }
}

void TestAddSum()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r=0;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->AddSum(a,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    assert(r==300);
}
void TestOffset()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r[TEST_NUM];
    F32 offset = 2;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=9;
        r[i]=0;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Offset(a, offset,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(r[i]==11);
    }
}

void TestScale()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r[TEST_NUM];
    F32 scale = 9;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=9;
        r[i]=0;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Scale(a, scale,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(r[i]==81);
    }
}

void TestMultiSum()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 r=0;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=2;
        b[i]=3;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->MultiSum(a,b,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    assert(r==1800);
}
void TestNormalization()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r[TEST_NUM];
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
        r[i]=0;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Normalization(a, TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert( GET_ABS(r[i]-0.0576171875)<0.01);
    }
}
void TestAbs()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r[TEST_NUM];
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=-1;
        r[i]=0;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Abs(a, TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(r[i]==1);
    }
}
void TestOpposite()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r[TEST_NUM];
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=-1;
        r[i]=0;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Opposite(a, TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(r[i]==1);
    }
}

void TestProduct()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r=0;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Product(a,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    assert(r==1);
}
void TestSet()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 set = 2;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Set(a, set,TEST_NUM);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(a[i]==2);
    }
}
void TestCompare()
{
    //Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 err =2;
    BOOL IsSame = true ;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
        b[i]=2;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Compare(a, b, err, TEST_NUM,&IsSame);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    assert(IsSame==true);
}


void TestMax()
{
//Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r=0;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=i;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Max(a,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    assert(r==TEST_NUM - 1);
}
void TestMin()
{
//Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM];
    F32 r=0;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=i;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Min(a,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    assert(r==0);
}
void TestSing_dis()
{
//Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM],b[TEST_NUM];
    F32 r=0;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=2;
        b[i]=1;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Single_dis(a,b,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    assert(r==TEST_NUM);
}
void TestDouble_dis()
{
//Time
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;
    //Data
    F32 a[TEST_NUM],b[TEST_NUM];
    F32 r=0;
    //Init
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=3;
        b[i]=1;
    }
    //Calc
    gettimeofday(&tpstart,NULL);
    for(S32 i=0;i<TEST_CYC;i++)
    {
        itr_math::CalculateObj->Double_dis(a,b,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    assert(r==4*TEST_NUM);
}
    //Multi             finished
    //Sub               finished
    //Add               finished
    //AddSum            finished
    //Div               undone!
    //Offset            finished
    //Scale             finished
    //MultiSum          finished
    //Normalization     finished
    //Abs               finished
    //Opposite          finished
    //Product           finished
    //Set               finished
    //Compare           finished
int main()
{



    //Add
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestAdd();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestAdd();
    itr_math::MathObjStandDeinit();

    //Sub
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestSub();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestSub();
    itr_math::MathObjStandDeinit();

    //Mul
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestMulti();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestMulti();
    itr_math::MathObjStandDeinit();

    //AddSum
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestAddSum();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestAddSum();
    itr_math::MathObjStandDeinit();

    //Offset
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestOffset();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestOffset();
    itr_math::MathObjStandDeinit();

    //Scale
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestScale();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestScale();
    itr_math::MathObjStandDeinit();

    //MultiSum
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestMultiSum();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestMultiSum();
    itr_math::MathObjStandDeinit();

    //Normalization
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestNormalization();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestNormalization();
    itr_math::MathObjStandDeinit();

    //Abs
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestAbs();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestAbs();
    itr_math::MathObjStandDeinit();

    //Opposite
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestOpposite();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestOpposite();
    itr_math::MathObjStandDeinit();

    //Product
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestProduct();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestProduct();
    itr_math::MathObjStandDeinit();

    //Set
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestSet();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestSet();
    itr_math::MathObjStandDeinit();

    //Compare
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestCompare();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestCompare();
    itr_math::MathObjStandDeinit();

    //Max
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestMax();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestMax();
    itr_math::MathObjStandDeinit();

    //Min
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestMin();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestMin();
    itr_math::MathObjStandDeinit();

    //Single_dis
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestSing_dis();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestSing_dis();
    itr_math::MathObjStandDeinit();

    //Double_dis
    PRINT_DEBUG("!!!Neon!!!");
    itr_math::MathNeonObjStandInit();
    TestDouble_dis();
    itr_math::MathNeonObjStandDeinit();
    PRINT_DEBUG("!!!C++!!!");
    itr_math::MathObjStandInit();
    TestDouble_dis();
    itr_math::MathObjStandDeinit();


    return 0;
}

