#include "rotatetest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>
#include <stdio.h>

void rotatetest()
{
   // rotateImgGraytest();
    TRACE_INFO("OK Rotate");
}


void rotateImgGraytest()
{
   /* S32 X=100;
    S32 Y=110;
    S32 width=200 ;
    S32 height=100;
    ImageGray grayI;

    ImageGray grayO(width,height);
    RectangleS rect(X, Y,width,height);

    IOHelper::ReadPGMFile("Debug/table1.pgm", grayI);
    Matrix graym(grayI.GetHeight(),grayI.GetWidth());
    Matrix graym1(rect.Height,rect.Width);
    ConvertFormat::ImageGray2Matrix(grayI,graym);


    Rotate::rotate(graym, rect, 0, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray00.pgm", grayO);

    Rotate::rotate(graym, rect, 20, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray20.pgm", grayO);

    Rotate::rotate(graym, rect, 50, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray50.pgm", grayO);

    Rotate::rotate(graym, rect, 90, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray90.pgm", grayO);

    Rotate::rotate(graym, rect, 135, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray135.pgm", grayO);

    Rotate::rotate(graym, rect, 180, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray180.pgm", grayO);

    Rotate::rotate(graym, rect, 250, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray250.pgm", grayO);

    Rotate::rotate(graym, rect, 300, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray300.pgm", grayO);

    Rotate::rotate(graym, rect, 360, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray360.pgm", grayO);

    Rotate::rotate(graym, rect, -20, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/graym20.pgm", grayO);

    Rotate::rotate(graym, rect, -90, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/gray-90.pgm", grayO);

    Rotate::rotate(graym, rect, -145, graym1);
    ConvertFormat::Matrix2ImageGray(graym1,grayO);
    IOHelper::WritePGMFile("Debug/graym145.pgm", grayO);
*/
}
