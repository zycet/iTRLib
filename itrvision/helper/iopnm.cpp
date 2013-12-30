#include "iopnm.h"
#include "../format/format.h"
#include "convertformat.h"
namespace itr_vision
{
    void IOpnm::ReadPPMFile(char *filename, ImageGray &img)
    {
        //Read File
        FILE *file = fopen(filename, "rb+");
        assert(file!=NULL);
        assert(fseek(file, 0, SEEK_END)==0);
        U32 length = ftell(file);
        assert(length>0);
        fseek(file, 0, SEEK_SET);
        U8 *bufferRead = new U8[length];
        MemoryClear(bufferRead, length);
        U32 len = fread(bufferRead, 1, length, file);
        assert(len==length);
        fclose(file);
        //Read Image
        itr_vision::FormatPPM FormatPPMObj;
        itr_vision::IFormat::ImageInfo imageInfo;
        assert(FormatPPMObj.GetInfo(bufferRead, length, imageInfo)==itr_vision::IFormat::Success);
        img.Allocate(imageInfo.Width, imageInfo.Height);
        assert(FormatPPMObj.ToImage(bufferRead,length,img)==itr_vision::IFormat::Success);
        delete[] bufferRead;
    }

    void IOpnm::WritePPMFile(char *filename, ImageGray &img)
    {
        S32 length2 = img.GetWidth() * img.GetHeight()*3 + 20;
        U8 *bufferWrite = new U8[length2];
        //Write Image

        itr_vision::FormatPPM FormatPPMObj;
        assert(FormatPPMObj.ToBinary(img, bufferWrite, length2)==itr_vision::IFormat::Success);
        //Write File
        FILE *file2 = fopen(filename, "wb+");
        assert(file2!=NULL);
        assert(fwrite(bufferWrite,1,length2,file2)==(U32)length2);
        fflush(file2);
        fclose(file2);
        delete[] bufferWrite;
    }
    void IOpnm::ReadPGMFile(char *filename, ImageGray &img)
    {
        //Read File
        FILE *file = fopen(filename, "rb+");
        assert(file!=NULL);
        assert(fseek(file, 0, SEEK_END)==0);
        U32 length = ftell(file);
        assert(length>0);
        fseek(file, 0, SEEK_SET);
        U8 *bufferRead = new U8[length];
        MemoryClear(bufferRead, length);
        U32 len = fread(bufferRead, 1, length, file);
        assert(len==length);
        fclose(file);
        //Read Image
        itr_vision::FormatPGM FormatPGMObj;
        itr_vision::IFormat::ImageInfo imageInfo;
        assert(FormatPGMObj.GetInfo(bufferRead, length, imageInfo)==itr_vision::IFormat::Success);
        img.Allocate(imageInfo.Width, imageInfo.Height);
        assert(FormatPGMObj.ToImage(bufferRead,length,img)==itr_vision::IFormat::Success);
        delete[] bufferRead;
    }

    void IOpnm::WritePGMFile(char *filename, ImageGray &img)
    {
        S32 length2 = img.GetWidth() * img.GetHeight() + 20;
        U8 *bufferWrite = new U8[length2];
        itr_vision::FormatPGM FormatPGMObj;
        assert(FormatPGMObj.ToBinary(img, bufferWrite, length2)==itr_vision::IFormat::Success);
        //Write File
        FILE *file2 = fopen(filename, "wb+");
        assert(file2!=NULL);
        assert(fwrite(bufferWrite,1,length2,file2)==(U32)length2);
        fflush(file2);
        fclose(file2);
        delete[] bufferWrite;
    }

    void IOpnm::ReadPPMFile(char *filename, Matrix &img)
    {
        ImageGray input;
        ReadPPMFile(filename,input);
        if(img.GetData()==NULL)
            img.Init(input.GetHeight(),input.GetWidth());
        ConvertFormat::ImageGray2Matrix(input,img);
    }

    void IOpnm::WritePPMFile(char *filename, Matrix &img)
    {
        ImageGray input(img.GetCol(),img.GetRow());
        ConvertFormat::Matrix2ImageGray(img,input);
        WritePPMFile(filename,input);
    }
    void IOpnm::ReadPGMFile(char *filename, Matrix &img)
    {
        ImageGray input;
        ReadPGMFile(filename,input);
        if(img.GetData()==NULL)
            img.Init(input.GetHeight(),input.GetWidth());
        ConvertFormat::ImageGray2Matrix(input,img);
    }

    void IOpnm::WritePGMFile(char *filename, Matrix &img)
    {
        ImageGray input(img.GetCol(),img.GetRow());
        ConvertFormat::Matrix2ImageGray(img,input);
        WritePGMFile(filename,input);
    }

    void IOpnm::ReadPPMFile(char *filename, ImageARGB &img)
    {
        //Read File
        FILE *file = fopen(filename, "rb+");
        assert(file!=NULL);
        assert(fseek(file, 0, SEEK_END)==0);
        U32 length = ftell(file);
        assert(length>0);
        fseek(file, 0, SEEK_SET);
        U8 *bufferRead = new U8[length];
        MemoryClear(bufferRead, length);
        U32 len = fread(bufferRead, 1, length, file);
        assert(len==length);
        fclose(file);
        //Read Image
        itr_vision::FormatPPM FormatPPMObj;
        itr_vision::IFormat::ImageInfo imageInfo;
        assert(FormatPPMObj.GetInfo(bufferRead, length, imageInfo)==itr_vision::IFormat::Success);
        img.Allocate(imageInfo.Width, imageInfo.Height);
        assert(FormatPPMObj.ToImage(bufferRead,length,img)==itr_vision::IFormat::Success);
        delete[] bufferRead;
    }

    void IOpnm::WritePPMFile(char *filename,ImageARGB &img)
    {
        S32 length2 = img.GetWidth() * img.GetHeight()*3 + 20;
        U8 *bufferWrite = new U8[length2];
        //Write Image

        itr_vision::FormatPPM FormatPPMObj;
        assert(FormatPPMObj.ToBinary(img, bufferWrite, length2)==itr_vision::IFormat::Success);
        //Write File
        FILE *file2 = fopen(filename, "wb+");
        assert(file2!=NULL);
        assert(fwrite(bufferWrite,1,length2,file2)==(U32)length2);
        fflush(file2);
        fclose(file2);
        delete[] bufferWrite;
    }
    void IOpnm::ReadPGMFile(char *filename, ImageARGB &img)
    {
        //Read File
        FILE *file = fopen(filename, "rb+");
        assert(file!=NULL);
        assert(fseek(file, 0, SEEK_END)==0);
        U32 length = ftell(file);
        assert(length>0);
        fseek(file, 0, SEEK_SET);
        U8 *bufferRead = new U8[length];
        MemoryClear(bufferRead, length);
        U32 len = fread(bufferRead, 1, length, file);
        assert(len==length);
        fclose(file);
        //Read Image
        itr_vision::FormatPGM FormatPGMObj;
        itr_vision::IFormat::ImageInfo imageInfo;
        assert(FormatPGMObj.GetInfo(bufferRead, length, imageInfo)==itr_vision::IFormat::Success);
        img.Allocate(imageInfo.Width, imageInfo.Height);
        assert(FormatPGMObj.ToImage(bufferRead,length,img)==itr_vision::IFormat::Success);
        delete[] bufferRead;
    }

    void IOpnm::WritePGMFile(char *filename, ImageARGB &img)
    {
        S32 length2 = img.GetWidth() * img.GetHeight() + 20;
        U8 *bufferWrite = new U8[length2];
        itr_vision::FormatPGM FormatPGMObj;
        assert(FormatPGMObj.ToBinary(img, bufferWrite, length2)==itr_vision::IFormat::Success);
        //Write File
        FILE *file2 = fopen(filename, "wb+");
        assert(file2!=NULL);
        assert(fwrite(bufferWrite,1,length2,file2)==(U32)length2);
        fflush(file2);
        fclose(file2);
        delete[] bufferWrite;
    }
}
