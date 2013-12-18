#ifndef IOPNM_H
#define IOPNM_H

#include "../image/image.h"
namespace itr_vision
{
class IOpnm
{
    public:
        static void ReadPPMFile(char* filename, ImageGray& img);
        static void WritePPMFile(char* filename, ImageGray& img);
        static void ReadPGMFile(char* filename, ImageGray& img);
        static void WritePGMFile(char* filename, ImageGray& img);
    protected:
    private:
};
}
#endif // IOPNM_H
