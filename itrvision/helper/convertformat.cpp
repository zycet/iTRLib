#include "convertformat.h"

namespace itr_vision
{

    void ConvertFormat::ImageARGB2Matrix(const ImageARGB &input,Matrix &output)
    {
        S32 length=input.GetPixelsNumber();
        F32* matrixptr=output.GetData();
        U32* imageptr=input.GetPixels();
        U8 r,g,b;

        for(int i=0;i<length;++i)
            {
                b=*imageptr;
                g=(*imageptr)>>8;
                r=(*imageptr)>>16;
                *matrixptr=(0.299 * r + 0.587 * g + 0.114 * b);
            }
    }
    void ConvertFormat::ImageGray2Matrix(const ImageGray &input,Matrix &output)
    {
        S32 length=input.GetPixelsNumber();
        F32* matrixptr=output.GetData();
        S16* imageptr=input.GetPixels();
        for(int i=0;i<length;++i)
            *matrixptr++=*imageptr++;
    }

}
