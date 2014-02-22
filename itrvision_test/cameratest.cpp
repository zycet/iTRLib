#include "cameratest.h"
#include "stdio.h"
#define end_of_pos1 780
#define end_of_pos2 1006

using namespace itr_vision;

void printMatrix(itr_math::Matrix a)
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

void printVector(itr_math::Vector a)
{
    printf("The Vector is\n");
    for(int i = 0; i<a.GetDim(); i++)
    {
        printf("%f ",a.GetData()[i]);
    }
    printf("\n");
    printf("\n");
}
void TestCamerain()
{
    CameraInterCalc cam_in;
    Vector PixelPoint(3),CameraPoint(4);
    cam_in.SetPara(0.03,0.0002,0.0002,150,150);
    printf("cam_in.MatP2C\n");
    printMatrix(cam_in.MatP2C);
    printf("cam_in.MatC2P\n");
    printMatrix(cam_in.MatC2P);

    TestCameraexternal(cam_in);
}
void TestCameraexternal(itr_vision::CameraInterCalc &camera_in)
{
    VectorFeaturePoint pointlist1[end_of_pos1];
    VectorFeaturePoint pointlist2[end_of_pos2];
    itr_math::Matrix Hstd(3,3);
    /// read data
    FILE *FP_pos1,*FP_pos2,*FP_desc1,*FP_desc2,*FP_sigma2,*FP_H;
    FP_pos1 = fopen("pos1.txt", "r");
    FP_pos2 = fopen("pos2.txt", "r");
    FP_desc1 = fopen("desc1.txt", "r");
    FP_desc2 = fopen("desc2.txt", "r");
    FP_sigma2 = fopen("sigmas2.txt", "r");
    FP_H = fopen("H.txt", "r");
    assert(FP_pos1!=NULL);
    assert(FP_pos2!=NULL);
    assert(FP_desc1!=NULL);
    assert(FP_desc2!=NULL);
    assert(FP_sigma2!=NULL);
    assert(FP_H!=NULL);

    for(S32 i=0; i<end_of_pos1; i++)
    {
        fscanf(FP_pos1,"%f %f",&(pointlist1[i].X),&(pointlist1[i].Y));
        for(S32 j=0; j<128; j++)
        {
            fscanf(FP_desc1,"%f",&pointlist1[i].Feature[j]);
        }
    }
    for(S32 i=0; i<end_of_pos2; i++)
    {
        fscanf(FP_pos2,"%f %f",&pointlist2[i].X,&pointlist2[i].Y);
        fscanf(FP_sigma2,"%f",&pointlist2[i].Quality);
        for(S32 j=0; j<128; j++)
        {
            fscanf(FP_desc2,"%f",&pointlist2[i].Feature[j]);
        }
    }
    for(S32 i=0; i<3; i++)
        for(S32 j=0; j<3; j++)
            fscanf(FP_H,"%f",&Hstd(i,j));
    fclose(FP_pos1);
    fclose(FP_pos2);
    fclose(FP_desc1);
    fclose(FP_desc2);
    fclose(FP_sigma2);
    fclose(FP_H);
///     qualify data
//    assert(pointlist1[779].X==739&&pointlist1[779].Y==644);
//    assert(pointlist2[1005].X==233&&pointlist2[1005].Y==673);
//    assert(GET_ABS(pointlist2[1005].Quality-2.8284)<0.0001);
//    assert(GET_ABS(pointlist1[779].Feature[125]-0.036629044)<0.001);
//    assert(GET_ABS(pointlist2[1005].Feature[125]-0.13691367)<0.001);
//    assert(GET_ABS(Hstd(2,2)+0.00485)<0.001);

    itr_vision::FeatureMatch domatch;
    S32 matched_num;
    domatch.FeatureMatchDo(pointlist1,end_of_pos1,pointlist2,end_of_pos1,matched_num);
    //printf("matched number: %d\n",matched_num);
    CameraExterCalc camera_out;
    camera_out.CalcH(pointlist1,end_of_pos1,pointlist2,end_of_pos1);

    printf("camera_out.H\n");
    printMatrix(camera_out.H);
    printf("Hstd\n");
    printMatrix(Hstd);

    camera_out.CalcMotion(camera_in,10);
}
void CameraTest()
{
    TestCamerain();

    TRACE_INFO("OK cameratest!!");
}
