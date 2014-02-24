#include "iopnm.h"

namespace itr_vision
{
    /*void IOpnm::ReadPPMFile(char *filename, ImageGray &img)
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
        {
            img.Init(input.GetHeight(),input.GetWidth());
        }
        ConvertFormat::ImageGray2Matrix(input,img);
    }

    void IOpnm::WritePPMFile(char *filename, Matrix &img)
    {
        ImageGray input(img.GetCol(),img.GetRow());
        ConvertFormat::Matrix2ImageGray(img,input);
        WritePPMFile(filename,input);
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
    }*/


    void ReadPGMHeader(FILE *file,int &magic,int &ncols,int &nrows,int &maxval)
    {
        fscanf(file,"P%d",magic);
        assert(magic==5);
        fscanf(file,"%d %d",&ncols,&nrows);
        assert(ncols>0);
        assert(nrows>0);
        fscanf(file,"%d",&maxval);
        assert(maxval>0);
    }

    void ReadPGM(FILE *file,int &ncols,int &nrows,Matrix &img)
    {
        unsigned char pixel;
        img.Init(nrows,ncols);
        int length=ncols*nrows;
        float *ptr=img.GetData();
        for(int i=0; i<length; ++i)
        {
            fscanf(file,"%c",&pixel);
            *ptr++=pixel;
        }
    }

    void IOpnm::ReadPGMFile(char *filename, Matrix &img)
    {
        //Read File
        FILE *file = fopen(filename, "r");
        int magic,maxval;
        int ncols,nrows;
        int i;

        fscanf(file,"P%d",&magic);
        assert(magic==5);
        fscanf(file,"%d %d",&ncols,&nrows);
        assert(ncols>0);
        assert(nrows>0);
        fscanf(file,"%d",&maxval);
        assert(maxval>0);

        unsigned char pixel;
        if(img.GetRow()==0 && img.GetCol()==0)
            img.Init(nrows,ncols);
        assert(img.GetCol()==ncols);
        assert(img.GetRow()==nrows);
        int length=ncols*nrows;
        F32 *ptr=img.GetData();
        for(i=0; i<length; ++i)
        {
            fscanf(file,"%c",&pixel);
            *ptr++=pixel;
        }
        fclose(file);
    }

    void IOpnm::WritePGMFile(char *filename, Matrix &img)
    {
        //Read File
        FILE *file = fopen(filename, "w");
        fprintf(file,"P5\n%d %d\n255\n",img.GetCol(),img.GetRow());
        int length=img.GetCol()*img.GetRow();
        unsigned char pixel;
        F32 *ptr=img.GetData();
        while(length--)
        {
            pixel=(unsigned char)*ptr++;
            fprintf(file,"%c",pixel);
        }
        fclose(file);

    }
}
