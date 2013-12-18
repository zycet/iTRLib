#include "rotatetest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>
#include <stdio.h>

void rotatetest()
{
    rotateImgGraytest();
}

void rotateImgGraytest()
{
    S32 X=0;
    S32 Y=0;
    S32 width=685 ;
    S32 height=494;
    ImageGray grayI;
    ImageGray grayO(width,height);
    RectangleS rect(X, Y,width,height);

    IOHelper::ReadPGMFile("Debug/table1.pgm", grayI);

    Rotate::rotate(grayI, rect, 0, grayO);
    IOHelper::WritePGMFile("Debug/gray00.pgm", grayO);

    Rotate::rotate(grayI, rect, 90, grayO);
    IOHelper::WritePGMFile("Debug/gray90.pgm", grayO);

    Rotate::rotate(grayI, rect, 45, grayO);
    IOHelper::WritePGMFile("Debug/gray45.pgm", grayO);

    Rotate::rotate(grayI, rect, 10, grayO);
    IOHelper::WritePGMFile("Debug/gray10.pgm", grayO);
    Rotate::rotate(grayI, rect, 130, grayO);
    IOHelper::WritePGMFile("Debug/gray130.pgm", grayO);
    Rotate::rotate(grayI, rect, 180, grayO);
    IOHelper::WritePGMFile("Debug/gray180.pgm", grayO);
    Rotate::rotate(grayI, rect, 360, grayO);
    IOHelper::WritePGMFile("Debug/gray360.pgm", grayO);

    TRACE_INFO("OK Rotate");
}
