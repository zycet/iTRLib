#include "filetest.h"
#include "itrbase.h"
#include "itrvision.h"
using itr_math::Matrix;
using namespace itr_vision;

void filereadtest()
{

}
void filetest()
{
        Matrix img;
    IOpnm::ReadPGMFile("bin/debug/img00069.pgm",img);
    IOpnm::WritePGMFile("bin/debug/ou.pgm",img);
}
