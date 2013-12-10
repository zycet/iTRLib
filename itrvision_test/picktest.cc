#include "picktest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>

void picktest()
{
    pickImgGraytest();
    pickImgARGBtest();
}
void pickImgGraytest()
{
    ImageGray grayI;
    ImageGray grayO(100, 150);
    RectangleS rect(100, 40, 100, 150);
    IOHelper::ReadPGMFile("Debug/table1.pgm", grayI);
    Pick::Rectangle(grayI, rect, grayO);
    IOHelper::WritePGMFile("Debug/grayO.pgm", grayO);
}
void pickImgARGBtest()
{
    ImageARGB ARGBI;
    ImageARGB ARGBO;
    RectangleS rect(10, 40, 100, 150);
    //IOHelper::ReadPPMFile("Debug/table1.ppm", ARGBI);
    //Pick::Rectangle(ARGBI, rect, ARGBO);
    //IOHelper::WritePPMFile("Debug/ta.ppm", ARGBO);
}

