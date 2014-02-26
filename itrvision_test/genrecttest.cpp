#include"genrecttest.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>
#include"stdio.h"
#define num 20
void genrecttest()
{
    genrectintest();
    genrectouttest();
}
void genrectintest()
{

    RectangleS rect(100,100,300,300);
    RectangleS AAA[num]=RectangleS(100,100,300,300);

    itr_vision::GenRect::genrectin(rect,AAA,num);


    ImageGray Im1;
    IOHelper::ReadPGMFile("Debug/table1.pgm", Im1);
    Matrix gray(Im1.GetHeight(),Im1.GetWidth());
    ConvertFormat::ImageGray2Matrix(Im1,gray);
    for(S32 i=0;i<num;i++)
    {
        Draw::Rectangle(gray, *(AAA+i), 255);
    }
    Draw::Rectangle(gray, rect, 0);
    ConvertFormat::Matrix2ImageGray(gray,Im1);
    IOHelper::WritePGMFile("Debug/graygenrectin.pgm", Im1);

    TRACE_INFO("OK genrectin");
}
void genrectouttest()
{
    RectangleS rect(100,100,200,100);
    RectangleS AAA[num]=RectangleS(100,100,200,100);

    itr_vision::GenRect::genrectout(rect,AAA,num);

    ImageGray Im1;
    IOHelper::ReadPGMFile("Debug/table1.pgm", Im1);
    Matrix gray(Im1.GetHeight(),Im1.GetWidth());
    ConvertFormat::ImageGray2Matrix(Im1,gray);
    for(S32 i=0;i<num;i++)
    {
        Draw::Rectangle(gray, *(AAA+i), 255);
    }
    Draw::Rectangle(gray, rect, 0);
    ConvertFormat::Matrix2ImageGray(gray,Im1);
    IOHelper::WritePGMFile("Debug/graygenrectout.pgm", Im1);

    TRACE_INFO("OK genrectout");
}

