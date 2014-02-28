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

void printmatrix(Matrix a)
{
    printf("The Matrix is:\n");
    for (int i = 0; i < a.GetRow(); ++i)
    {
        for (int j = 0; j < a.GetCol(); ++j)
        {
            printf("%f ", a(i, j));
        }
        printf("\n");
    }
    printf("\n");
}

void TestIpts()
{
    struct timeval tpstart;
    struct timeval tpend;
    F32 timeuse = 0 ;

    itr_math::MathObjStandInit();

    Matrix gray_matrix_in;
    Matrix gray_matrix_in2;
    IOpnm::ReadPGMFile("img3.pgm", gray_matrix_in);
    IOpnm::ReadPGMFile("img2.pgm", gray_matrix_in2);
    S32 w=gray_matrix_in.GetCol();
    S32 h=gray_matrix_in.GetRow();
    S32 w2=gray_matrix_in2.GetCol();
    S32 h2=gray_matrix_in2.GetRow();
    gray_matrix_in.AllMul(1/255.f);
    gray_matrix_in2.AllMul(1/255.f);

    SURF surf;
    SURF surf2;
    surf.Init(w,h,5,4,2,0.0004f);
    surf2.Init(w2,h2,5,4,2,0.0004f);
    std::vector<VectorFeaturePoint> FeaturePointList;
    std::vector<VectorFeaturePoint> FeaturePointList2;
    gettimeofday(&tpstart,NULL);
    surf.ProcessAll(gray_matrix_in, FeaturePointList);

    //MatrixDraw(surf.OctaveList[0]->GetCol(),surf.OctaveList[0]->GetRow(),surf.OctaveList[0]->Hessian);

    gettimeofday(&tpend,NULL);
    timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse*=0.0001f;
    PRINT_DEBUG(timeuse);
    surf2.ProcessAll(gray_matrix_in2, FeaturePointList2);
//    for(S32 i=0; i<FeaturePointList.size(); i++ )
//    {
//        VectorFeaturePoint p=FeaturePointList[i];
//        PRINT_DEBUG(p.X);
//        PRINT_DEBUG(p.Y);
//        PRINT_DEBUG(p.Dir);
//        PRINT_DEBUG(p.Quality);
//        PRINT_DEBUG(p.Value);
//        PRINT_DEBUG(p.LevelNo);
//        PRINT_DEBUG(p.Scale);
//        for(S32 j=0; j<64; j++)
//        {
//            PRINT_DEBUG(p.Feature[j]);
//        }
//    }

/**
    *\ matche test.
    */

    FeatureMatch Match;
    S32 matchnum;
    Match.FeatureMatchDo(FeaturePointList,FeaturePointList2,matchnum);
    CameraExterCalc camera_out;
    camera_out.CalcH(FeaturePointList,FeaturePointList2,matchnum);
    printf("matched num : %d \n",matchnum);
    printf("\nMatrix of H :\n");
    printmatrix(camera_out.H);

   for(S32 i=0; i<FeaturePointList.size(); i++ )
   {
        VectorFeaturePoint p=FeaturePointList[i];
        if(p.ID!=-1)
        {    printf("pos%d : %f\t%f\t",i,p.X,p.Y);
            VectorFeaturePoint pp=FeaturePointList2[p.ID];
            printf("pos matched:%f\t%f\n",pp.X,pp.Y);
        }
   }
    Vector pos(3),pos1(3),posstd(2);

    pos[0]=72;
    pos[1]=184;
    pos[2]=1;
    pos1=camera_out.H*pos;
    pos1.Mul(1/pos1[2]);
    printf("pos : %f\t%f\t",pos[0],pos[1]);
    printf("pos1: %f\t%f\t%f\n",pos1[0],pos1[1],pos1[2]);

    CameraInterCalc cam_in;
   // Vector PixelPoint(3),CameraPoint(4);
    cam_in.SetPara(0.03,0.0002,0.0002,150,150);

    camera_out.CalcMotion(cam_in,20);
    printmatrix(camera_out.R);
    printmatrix(camera_out.V);
    printmatrix(camera_out.t);
    for(S32 i=0; i<2; i++)
        ;
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
