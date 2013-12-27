#include "drawtest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>
using namespace itr_vision;
void drawtest()
{
    drawImgGraytestCircle();
    drawImgARGBtestCircle();
    drawImgGraytestLineOffset();
    drawImgARGBtestLineOffset();
    drawImgGraytestLine();
    drawImgARGBtestLine();
    drawImgGraytestCross();
    drawImgARGBtestCross();
    drawImgGraytestRectangle();
    drawImgARGBtestRectangle();
}
void drawImgGraytestCircle()
{
    Matrix gray;
    IOpnm::ReadPGMFile("Debug/table1.pgm", gray);
    Draw::Circle(gray, 200, 100, 50, 255);
    IOpnm::WritePGMFile("Debug/gray1.pgm", gray);
}
void drawImgARGBtestCircle()
{/*
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/img0.pgm", ARGB);
    Draw::Circle(ARGB, 100, 80, 10, 255);
    IOHelper::WritePGMFile("Debug/gray2.pgm", ARGB);
    */
}
void drawImgGraytestLineOffset()
{
    Matrix gray;
    IOpnm::ReadPGMFile("Debug/table1.pgm", gray);
    Draw::LineOffset(gray, 100, 80, -50, 200, 255);
    IOpnm::WritePGMFile("Debug/gray3.pgm", gray);
}
void drawImgARGBtestLineOffset()
{/*
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/img0.pgm", ARGB);
    Draw::LineOffset(ARGB, 100, 200, 200, 200, 255);
    IOHelper::WritePGMFile("Debug/gray4.pgm", ARGB);
    */
}
void drawImgGraytestLine()
{
    Matrix gray;
    IOpnm::ReadPGMFile("Debug/table1.pgm", gray);
    Draw::Line(gray, 3, 3, 50, 60, 255);
    IOpnm::WritePGMFile("Debug/gray5.pgm", gray);
}
void drawImgARGBtestLine()
{/*
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/img0.pgm", ARGB);
    Draw::Line(ARGB, 3, 3, 50, 60, 255);
    IOHelper::WritePGMFile("Debug/gray6.pgm", ARGB);
    */
}
void drawImgGraytestCross()
{
    Matrix gray;
    IOpnm::ReadPGMFile("Debug/table1.pgm", gray);
    Draw::Cross(gray, 200, 200, 100, 255);
    IOpnm::WritePGMFile("Debug/gray7.pgm", gray);
}
void drawImgARGBtestCross()
{/*
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/img0.pgm", ARGB);
    Draw::Cross(ARGB, 200, 200, 100, 255);
    IOHelper::WritePGMFile("Debug/gray8.pgm", ARGB);
    */
}
void drawImgGraytestRectangle()
{
    RectangleS rect(100, 100, 300, 300);
    Matrix gray;
    IOpnm::ReadPGMFile("Debug/table1.pgm", gray);
    Draw::Rectangle(gray, rect, 255);
    IOpnm::WritePGMFile("Debug/gray9.pgm", gray);
}
void drawImgARGBtestRectangle()
{/*
    RectangleS rect(410, 440, 100, 150);
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/img0.pgm", ARGB);
    Draw::Rectangle(ARGB, rect, 255);
    IOHelper::WritePGMFile("Debug/gray10.pgm", ARGB);
    */
}

