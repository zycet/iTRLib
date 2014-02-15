#include "integralimgtest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include <iostream>

void IntegralImgTest()
{
    Testnormal();
    Testsquare();
}
void Testnormal()
{
    Matrix InputImg;
    Matrix OutputImg;
    IOpnm::ReadPGMFile("table1.pgm", InputImg);
    IntegralImg::Normal(InputImg,OutputImg);
    IOpnm::WritePGMFile("gray1.pgm", OutputImg);
}

void Testsquare()
{
    Matrix InputImg;
    Matrix OutputImg;
    IOpnm::ReadPGMFile("table1.pgm", InputImg);
    IntegralImg::Square(InputImg,OutputImg);
    IOpnm::WritePGMFile("gray1.pgm", OutputImg);
}
