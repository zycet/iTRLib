#ifndef IOPNM_H
#define IOPNM_H
#include "itrbase.h"
#include "../image/image.h"
using itr_math::Matrix;
namespace itr_vision
{
class IOpnm
{
public:
    static void ReadPPMFile(char *filename, ImageGray &img);
    static void WritePPMFile(char *filename, ImageGray &img);
    static void ReadPGMFile(char *filename, ImageGray &img);
    static void WritePGMFile(char *filename, ImageGray &img);
    static void ReadPPMFile(char *filename, Matrix &img);
    static void WritePPMFile(char *filename, Matrix &img);
    static void ReadPGMFile(char *filename, Matrix &img);
    static void WritePGMFile(char *filename, Matrix &img);
    static void ReadPPMFile(char *filename, ImageARGB &img);
    static void WritePPMFile(char *filename, ImageARGB &img);
    static void ReadPGMFile(char *filename, ImageARGB &img);
    static void WritePGMFile(char *filename, ImageARGB &img);
protected:
private:
};
}
#endif // IOPNM_H
