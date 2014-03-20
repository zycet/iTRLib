#include "ssptest.h"
#include "stdio.h"
#include "stdlib.h"

void SSPReceivefuc(itr_protocol::StandSerialProtocol* SSP, itr_protocol::StandSerialFrameStruct* SSFS,U8* Package,S32 PackageLength)
{
    for(S32 i=0; i<4; i++)
    {
        S32 j=1;
    }
}
void SSPTest()
{

    // get data
    FILE* fopen_p;
    fopen_p=fopen("fopen_p.raw","r");
    if(fopen_p==NULL)
    {
        exit(0);
    }
    U8 data[64];
    char tmp_u8;
    for(S32 i=0; i<64; i++)
    {
        fscanf(fopen_p,"%c",&tmp_u8);
        data[i]=(U8)tmp_u8;
    }
    fclose(fopen_p);

    itr_protocol::StandSerialProtocol ssp_obj;

    //ssp_obj.Init((U8)0x45,(U8)0x54,NULL);
    ssp_obj.Init(data[0],data[1],NULL);
    ssp_obj.ProcessFunction[0]=&SSPReceivefuc;
    ssp_obj.ProcessRawByte(data,64);
    S32 J=0;
}
