#include "lktrackertest.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include <math.h>
void drawtest()
{
    void drawImgGraytestCircle();
    void drawImgARGBtestCircle();
    void drawImgGraytestLineOffset();
    void drawImgARGBtestLineOffset();
    void drawImgGraytestLine();
    void drawImgARGBtestLine();
    void drawImgGraytestCross();
    void drawImgARGBtestCross();
    void drawImgGraytestRectangle();
    void drawImgARGBtestRectangle();
}
void drawImgGraytestCircle()
{
    ImageGray gray;
    IOHelper::ReadPGMFile("Debug/img0.pgm", gray);
    Draw::Circle(gray, 100, 80, 10, 255);
    IOHelper::WritePGMFile("Debug/gray1.ppm", gray);
}
/*
void drawImgARGBtestCircle()
{
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/draw/cap000.pgm", ARGB);
    Draw::Circle(ARGB, 100, 80, 10, 255);
    IOHelper::WritePGMFile(file, ARGB);
}
void drawImgGraytestLineOffset()
{
    ImageGray gray;
    IOHelper::ReadPGMFile("Debug/green/cap000.pgm", gray);
    Draw::LineOffset(gray, 100, 80, 200, 160, 255);
    IOHelper::WritePGMFile(file, gray);
}
void drawImgARGBtestLineOffset()
{
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/green/cap000.pgm", gray);
    Draw::LineOffset(ARGB, 100, 80, 200, 160, 255);
    IOHelper::WritePGMFile(file, ARGB);
}
void drawImgGraytestLine()
{
    ImageGray gray;
    IOHelper::ReadPGMFile("Debug/green/cap000.pgm", gray);
    Draw::Line(gray, 1600, 1800, 100, 120, 255);
    IOHelper::WritePGMFile(file, gray);
}
void drawImgARGBtestCross()
{
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/green/cap000.pgm", gray);
    Draw::Line(ARGB, 800, 600, 100, 120, 255);
    IOHelper::WritePGMFile(file, ARGB);
}
void drawImgGraytestRectangle()
{
    RectangleS rect(210, 240, 100, 150);
    ImageGray gray;
    IOHelper::ReadPGMFile("Debug/green/cap000.pgm", gray);
    Draw::Rectangle(gray, rect, 255);
    IOHelper::WritePGMFile(file, gray);
}
void drawImgARGBtestRectangle()
{
    RectangleS rect(410, 440, 100, 150);
    ImageGray ARGB;
    IOHelper::ReadPGMFile("Debug/green/cap000.pgm", gray);
    Draw::Rectangle(ARGB, rect, 255);
    IOHelper::WritePGMFile(file, ARGB);
}*/
