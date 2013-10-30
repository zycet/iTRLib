#include "picktest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>

void picktest()
{
    pickImgGraytest();
    /*pickImgARGBtest();*/
}
void pickImgGraytest()
{
    ImageGray grayI;
    ImageGray grayO;
    RectangleS rect(10, 40, 100, 150);
    IOHelper::ReadPGMFile("Debug/img0.pgm", grayI);
    Pick::Rectangle(grayI, rect, grayO);
    IOHelper::WritePGMFile("Debug/grayO.pgm", grayO);
}
/*void pickImgARGBtest()
{
    ImageARGB ARGBI;
    ImageARGB ARGBO;
    RectangleS rect(10, 40, 100, 150);
    IOHelper::ReadPGMFile("Debug/img0.pgm", ARGBI);
    Pick::Rectangle(ARGBI, rect, ARGBO);
    IOHelper::WritePGMFile("Debug/ARGBO.pgm", ARGBO);
}*/

