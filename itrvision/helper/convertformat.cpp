#include "convertformat.h"

namespace itr_vision
{

    void ConvertFormat::ImageARGB2Matrix(const ImageARGB &input,Matrix &output)
    {
        S32 length=input.GetPixelsNumber();
        F32 *matrixptr=output.GetData();
        U32 *imageptr=input.GetPixels();
        U8 r,g,b;

        for(int i=0; i<length; ++i)
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
        F32 *matrixptr=output.GetData();
        S16 *imageptr=input.GetPixels();
        for(int i=0; i<length; ++i)
        {
            *matrixptr++=*imageptr++;
        }
    }
    void ConvertFormat::Matrix2ImageARGB(const Matrix &input, ImageARGB &output)
    {
        S32 length=input.GetCol()*input.GetRow();
        F32 *matrixptr=input.GetData();
        U32 *imageptr=output.GetPixels();
        U8 data;
        while(length--)
        {
            data=(U8)(*matrixptr++);
            *imageptr++=(data<<16)|(data<<8)|data;
        }
    }
    void ConvertFormat::Matrix2ImageGray(const Matrix &input, ImageGray &output)
    {
        S32 length=input.GetCol()*input.GetRow();
        F32 *matrixptr=input.GetData();
        S16 *imageptr=output.GetPixels();
        while(length--)
        {
            *imageptr++=(U8)(*matrixptr++);
        }
    }
}
