#include "ix264.h"
#include "itrbase.h"
#include "itrvision.h"
#include "types.h"
#include <stdio.h>
#include "itrsystem.h"
#include "basestruct.h"

#include "vcompress.h"
S32 width=640;
S32 height=480;
S32 _size=width*height;


const int MaxSendLength=65535;
const int MaxRecLength=25;
const int ListenPort=9031,SendPort=9032;
//数据发送长度
int SendLength;
//压缩后的图像数据指针
const void *imgCompressData;
//压缩后的图像长度
int imgLength;
//UDP发送接收缓冲区
char RecBuf[MaxRecLength];
char SendBuf[MaxSendLength];

itr_system::Udp _udp(ListenPort,false);
itr_system::Udp::UdpPackage udpPackage;
itr_system::SerialPort uart;
bool uartOK=false;
itr_protocol::StandSerialProtocol sspUdp;
///SSP接受数据，进行命令解析
U8 mode=0;
Config config;
void SSPReceivefuc(itr_protocol::StandSerialProtocol *SSP, itr_protocol::StandSerialFrameStruct *SSFS,U8 *Package,S32 PackageLength)
{
    // F32 *kpx,*kdx,*kpy,*kdy;
    switch(Package[0])
    {
    case 0x41:
        mode=Package[1];
//        if(mode!=2)
//        {
//            GimbalStop(&controlData,controlLength);
//            if(uartOK)
//                uart.Send((unsigned char*)controlData,controlLength);
//        }
        break;
    case 0x42:
        MemoryCopy(Package,Package+1,16);
        // kpx=(F32*)(Package);
        // kdx=(F32*)(Package+4);
        // kpy=(F32*)(Package+8);
        // kdy=(F32*)(Package+12);
        // GimbalUpdatePID(*kpx,*kdx,*kpy,*kdy);
        break;
    case 0x44:
        config.color=Package[1];
        break;
    case 0x43:
        config.fps=Package[1];
        config.pixel=Package[2];
        break;
    case 0x45:

    //直接转发
    default:
        if(uartOK)
            uart.Send((U8*)SSFS,SSP->GetSSFSLength(SSFS));
        break;
    }
}
//准备要发送的数据
S32 SSPSend(U8* Buffer,S32 Length)
{
    for (int i = 0; i < Length; ++i)
    {
        printf("%X ",Buffer[i]);
    }
    printf("\n");
    memcpy(SendBuf,Buffer,Length);

    // U8* img=compressBuffer.GetBufferToRead();
    // while(img==NULL)
    // {
    //      img=compressBuffer.GetBufferToRead();
    // }
    memcpy(SendBuf+Length,imgCompressData,imgLength);
    SendLength=Length+imgLength;

    // compressBuffer.SetBufferToWrite(img);
    return SendLength;
}
//初始化参数
void Init()
{
    config.color=0;
    config.pixel=0;
    config.fps=30;

    // udpPackage.IP="192.168.199.187";
    udpPackage.IP="192.168.199.159";
    udpPackage.port=SendPort;

    itr_math::MathObjStandInit();

    sspUdp.Init(0xA5 ,0x5A ,SSPSend);//串口发送函数 代替 NULL
    sspUdp.ProcessFunction[0]=&SSPReceivefuc;
    uartOK=(uart.Init("/dev/ttyUSB0",115200)==0);
}
int main()
{
    Picture pic;
    itrx264::ix264 ix264obj;
    FILE* fp;
    fp=fopen("outpgm11.pgm","r");
    if(fp==NULL)
    {
        printf("Fail to open Picture!\n");
        exit(1);
    }
    fscanf(fp, "P6\n%d %d 255\n",&width,&height);
    _size=width*height;
    U8 Y[_size];
    U8 U[_size/4];
    U8 V[_size/4];
    U8 imgcomped[_size*3];

    printf("Picture opened !\n");
    fread(Y,1,_size,fp);
    fread(U,1,_size/4,fp);
    fread(V,1,_size/4,fp);
    pic.data[0]=Y;
    pic.data[1]=U;
    pic.data[2]=V;

    void *encoder = vc_open(width, height, 30.00);
    if (!encoder) {
        fprintf(stderr, "ERR: can't open x264 encoder\n");
        exit(-1);
    }
    int rc = vc_compress(encoder, pic.data, pic.stride, &imgCompressData, &imgLength);

    // void encoder=ix264obj.vc_open(width, height, 30.00);
    printf("ix264 oened!\n");

    // int rc = ix264obj.vc_compress(pic.data, pic.stride,&imgCompressData , & imgLength);
    if(rc>0)
    {
        printf("compress succeed!\n");
    }
    else
    {
        printf("compress failed !\n");
    }

    S32 offset=0;
    U8 tempbuff[8];
    for(;;)
    {
        if(_udp.Receive(RecBuf,MaxRecLength))
        {
            //使用SSP进行解包
            sspUdp.ProcessRawByte((U8 *)RecBuf,MaxRecLength);
        }
        //用SSP封装，包括图像和跟踪结果
        SendLength=0;
        offset=0;
        memset(tempbuff,0,sizeof(tempbuff));
        tempbuff[offset++]=0x40;
        tempbuff[offset++]=mode;

        sspUdp.SSPSendPackage(0,tempbuff,offset);
        // 发送结果
        udpPackage.pbuffer=SendBuf;
        udpPackage.len=SendLength;
        _udp.Send(udpPackage);

        printf("Send OK\n");
    }
    ix264obj.vc_close();
    fclose(fp);
    return 0;
}
