#include "cameratest.h"
#include "stdio.h"

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

}
void TestCameraexternal()
{
    //VectorFeaturePoint

}

void CameraTest()
{
    TestCamerain();



    TRACE_INFO("OK genrectout");
}
