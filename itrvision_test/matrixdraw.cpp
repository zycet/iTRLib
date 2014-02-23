#include "matrixdraw.h"
#include "iohelper.h"
#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include "math.h"

void MatrixDraw(S32 W,S32 H,F32* Data)
{
    F32 result;
    Matrix Img(H,W,Data);
    itr_math::CalculateObj->Max(Img.GetData(),H*W, result);
    Img.AllMul(1/result*255);
    IOpnm::WritePGMFile("graylm.pgm", Img);
}
