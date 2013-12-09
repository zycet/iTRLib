#include "rotatetest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>

void rotatetest()
{
    rotateImgGraytest();
}

void pickImgGraytest()
{
    ImageGray grayI;
    ImageGray grayO(100, 150);
    RectangleS rect(100, 40, 100, 150);
    F32 ang = 90;
    IOHelper::ReadPGMFile("Debug/table1.pgm", grayI);
    grayO = Rotate::rotate(grayI, rect, ang);
    IOHelper::WritePGMFile("Debug/grayO.pgm", grayO);
}
