#include <iostream>
#include "itrbase.h"
#include "itrneon.h"
#include <sys/time.h>

using namespace std;
using namespace itr_math;

#define TEST_CYC 100
#define TEST_NUM 300

/*void CalculateNeonTest()
{

    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 r[TEST_NUM];
    F32 k=0;
    BOOL IsSame;
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
        b[i]=2;
        r[i]=0;
    }
    itr_math::CalculateObj->Compare(a, b, 1,TEST_NUM,&IsSame);
    for(S32 i=0;i<TEST_NUM;i++)
    {
        if(r[i]!=-1)
        {
            a[i]=1;
        }
    }
}*/
/*void CalculateNeonTestAdd()
{

    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 r[TEST_NUM];
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
        b[i]=2;
        r[i]=0;
    }
    itr_math::CalculateObj->Add(a, b,TEST_NUM,r);
    for(S32 i=0;i<TEST_NUM;i++)
    {
        if(r[i]!=3)
        {
            a[i]=1;
        }
    }
}*/
/*void CalculateNeonTestAdd()
{

    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 r[TEST_NUM];
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
        b[i]=2;
        r[i]=0;
    }
    itr_math::CalculateObj->Add(a, b,TEST_NUM,r);
    for(S32 i=0;i<TEST_NUM;i++)
    {
        if(r[i]!=3)
        {
            a[i]=1;
        }
    }
}*/
/*void CalculateNeonTestSub()
{

    F32 a[TEST_NUM];
    F32 b[TEST_NUM];
    F32 r[TEST_NUM];
    for(S32 i=0;i<TEST_NUM;i++)
    {
        a[i]=1;
        b[i]=2;
        r[i]=0;
    }
    itr_math::CalculateObj->Sub(a, b,TEST_NUM,r);
    for(S32 i=0;i<TEST_NUM;i++)
    {
        if(r[i]!=-1)
        {
            a[i]=1;
        }
    }
}*/


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
        a[i]=1;
        b[i]=2;
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
        assert(r[i]==3);
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
        a[i]=1;
        b[i]=2;
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
        assert(r[i]==-1);
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
        a[i]=1;
        b[i]=2;
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
        assert(r[i]==2);
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
        a[i]=1;
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
        assert(r[i]==3);
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
    F32 scale = 2;
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
        itr_math::CalculateObj->Scale(a, scale,TEST_NUM,r);
    }
    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse /= 1000;
    TRACE_DEBUG(timeuse);
    //Verify
    for(S32 i=0;i<TEST_NUM;i++)
    {
        assert(r[i]==2);
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
        a[i]=1;
        b[i]=1;
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
    assert(r==300);
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

    F32 SoulthAA[10];
    F32 max_result;
    for(S32 i = 0; i<10; i++)
    {
        SoulthAA[i] = i;
    }
    itr_math::CalculateObj->Max(SoulthAA, 10,max_result);
    assert(max_result==9);
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
    itr_math::MathNeonObjStandInit();
    TestMax();
    /*
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
    */
    return 0;
}

