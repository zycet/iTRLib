#include "matrixdraw.h"

#include "itrvision.h"
#include "itrbase.h"
#include "stdio.h"
#include "math.h"

void MatrixDraw(S32 W,S32 H,F32* Data)
{
    F32 resultM;
    F32 resultm;
    Matrix Img(H,W,Data);
    itr_math::CalculateObj->Min(Img.GetData(),H*W, resultm);
    Img.AllAdd(-resultm);
    itr_math::CalculateObj->Max(Img.GetData(),H*W, resultM);
    Img.AllMul(1/resultM*255);

    itr_vision::IOpnm::WritePGMFile("graylm.pgm", Img);
}
