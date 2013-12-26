#include"genrecttest.h"
#include "itrvision.h"

void genrectintest()
{
    RectangleS rect(100,100,200,100);
    RectangleS rectR[10];
    genrectin(rect,rectR[],10);

    Matrix gray;
    IOHelper::ReadPGMFile("Debug/img0.pgm", gray);
    for(S32 i=0;i<10;i++)
    {
        Draw::Rectangle(gray, rect[i], 255);
    }
    IOHelper::WritePGMFile("Debug/graygenrectin.pgm", gray);
    TRACE_INFO("OK genrectin");
}
void genrectouttest()
{
    RectangleS rect(100,100,200,100);
    RectangleS rectR[10];
    genrectout(rect,rectR[],10);

    Matrix gray;
    IOHelper::ReadPGMFile("Debug/img0.pgm", gray);
    for(S32 i=0;i<10;i++)
    {
        Draw::Rectangle(gray, rect[i], 255);
    }
    IOHelper::WritePGMFile("Debug/graygenrectout.pgm", gray);

    TRACE_INFO("OK genrectout");
}
void genrecttest()
{
    genrectintest();
    genrectouttest();
}
