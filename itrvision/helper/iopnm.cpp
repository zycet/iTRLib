#include "iopnm.h"

namespace itr_vision
{
    void ReadPGMHeader(FILE *file,int &magic,int &ncols,int &nrows,int &maxval)
    {
        fscanf(file,"P%d",&magic);
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
