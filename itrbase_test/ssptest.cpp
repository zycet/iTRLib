#include "ssptest.h"
#include <vector>

#include "stdio.h"
#include "stdlib.h"

using std::vector;

/*
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
 */
class onReceive : public itr_protocol::OnReceiveAction
{
    S32 Do(const itr_protocol::StandardExchangePackage &Package)
    {
        printf("keyword:%d\n", Package.keyword);
        printf("data:");
        for (int i = 0; i < Package.getDataLen(); ++i)
        {
            printf("%d ", Package.data[i]);
        }
        printf("\n");
    }
};

void SEPTest()
{
    printf("=============SEP Test Begin================\n");
    vector<U8> data;
    U8 buffer[300];
    for (int i = 0; i < 5; ++i)
    {
        data.push_back(i);
    }
    itr_protocol::StandardExchangePackage sep(0x01, data);
    itr_protocol::StandardExchangePackageSerial seps(sep);

    for (int j = 0; j < 5; ++j)
    {
        printf("%d ", sep.data[j]);
    }
    printf("\n");
    itr_protocol::StandardExchangeProtocolSerial protocolSerial;
    int len = protocolSerial.fillBuffer(sep, buffer);
    for (int j = 0; j < len; ++j)
    {
        printf("%d ", buffer[j]);
    }
    printf("\n");
    protocolSerial.addReceiveFun(new onReceive);
    int n = protocolSerial.processByte(buffer, 0, 300);
    printf("%d\n", n);
    printf("=============SEP Test end================\n");
}