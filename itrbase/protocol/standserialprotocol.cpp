#include "../platform/platform.h"
//#include "../math/math.h"
#include "../container/container.h"
#include "standserialprotocol.h"

namespace itr_protocol
{

StandSerialProtocol::StandSerialProtocol()
{
    //ctor
}

StandSerialProtocol::~StandSerialProtocol()
{
    //dtor
}

StandSerialProtocol::StandSerialProtocol(const StandSerialProtocol& other)
{
    //copy ctor
}

/**
   * \brief 初始化并设定基本参数
   * \param S0 设定的命令字0
   * \param S1 设定的命令字1
   * \param DataSendFun 数据发送函数指针(此库会调用此函数用于发出数据)
   */
void StandSerialProtocol::Init(U8 S0, U8 S1, StandDataSendFun DataSendFun)
{
    this->S0=S0;
    this->S1=S1;
    this->AutoDecrypt=false;
    this->AutoEncrypt=false;
    memset(this->Key1, 0, sizeof(this->Key1));
    memset(this->Key2, 0, sizeof(this->Key2));
    memset(this->ProcessFunction, 0, sizeof(this->ProcessFunction));
    this->DataSendFun=DataSendFun;
    this->receiveBufferState=0;
}

bool StandSerialProtocol::SSPFormatCheck(StandSerialFrameStruct* SSPF)
{
    if(!(GetSSFSLength(SSPF) >= StandSerialProtocolPlusLength))
        return false;
    CRC crc_this;
    if(crc_this.BL_CRC16Encode((U8*)SSPF,GetSSFSLength(SSPF)) != 0)
        return false;
    return true;
}
void StandSerialProtocol::SSPEncrypt(StandSerialFrameStruct* SSP, U8* Key1, U8* Key2)
{}
void StandSerialProtocol::SSPDecrypt(StandSerialFrameStruct* SSP, U8* Key1, U8* Key2)
{}
/**
* \brief 处理原始数据流
* \param Buffer 待处理缓冲区
* \param BufferLength 待处理缓冲区长度
*/
S32 StandSerialProtocol::ProcessRawByte(U8* Buffer, S32 BufferLength)
{
    S32 receiveFrameNum = 0;
    S32 len;
    S32 i = 0;
    U8 b;
    for( i=0; i<BufferLength; i++)
    {
        b = Buffer[i];
        if (this->receiveBufferState == 0)//S0
        {
            if (b == this->S0)
            {
                this->receiveBuffer[this->receiveBufferState] = b;
                this->receiveBufferState = 1;
            }
        }
        else if (this->receiveBufferState == 1)//S1
        {
            if (b == this->S1)
            {
                this->receiveBuffer[this->receiveBufferState] = b;
                this->receiveBufferState = 2;
            }
            else
            {
                this->receiveBufferState = 0;
            }
        }
        else if (this->receiveBufferState == 2)//Length
        {
            if (b >= 6)
            {
                this->receiveBuffer[this->receiveBufferState] = b;
                this->receiveBufferState = 3;
            }
            else
            {
                this->receiveBufferState = 0;
            }
        }
        else if (this->receiveBufferState >= 3)//Property+Data+CRC
        {
            this->receiveBuffer[this->receiveBufferState] = b;
            this->receiveBufferState++;
            len = this->receiveBuffer[2];
            if(len > StandSerialProtocolMaxLength)
            {
                this->receiveBufferState = 0;
            }
            else if (this->receiveBufferState >= len)
            {
                if(SSPFormatCheck((StandSerialFrameStruct*)Buffer))
                {
                    if (this->AutoDecrypt && this->AutoEncrypt)
                        SSPDecrypt((StandSerialFrameStruct*)Buffer, this->Key1, this->Key2);
                    receiveFrameNum++;
                    if(this->ProcessFunction[GetSSFSProtocolID((StandSerialFrameStruct*)Buffer)] != NULL)
                    {
                        this->ProcessFunction[GetSSFSProtocolID((StandSerialFrameStruct*)Buffer)](this, (StandSerialFrameStruct*)Buffer,(U8*)(Buffer+4),BufferLength);
                    }
                }
                else
                {
                    //UNDONE:Error Sum
                }
                this->receiveBufferState = 0;
            }
        }
    }
    return receiveFrameNum;
}

/**
* \brief 以SSP协议发送指定数据包
* \param ProtocolID 协作ID
* \param Package 待发送数据包
* \param PackageLength 待发送数据包长度
*/
void StandSerialProtocol::SSPSendPackage(U8 ProtocolID, U8* Package, U8 PackageLength)
{
    this->sendBuffer[0]=0xA5;
    this->sendBuffer[1]=0x5A;
    SetSSFSLength((StandSerialFrameStruct*)sendBuffer,PackageLength);
    SetSSFSProperty((StandSerialFrameStruct*)sendBuffer,ProtocolID&0x0F);

    memcpy(sendBuffer+4, Package, PackageLength);
    if(this->AutoEncrypt)
    {
        SSPEncrypt((StandSerialFrameStruct*)sendBuffer, this->Key1, this->Key2);
    }
    U16 cr;
    CRC _crcthis;
    cr = _crcthis.BL_CRC16Encode(sendBuffer,GetSSFSLength((StandSerialFrameStruct*)sendBuffer) - StandSerialProtocolCRCLength);
    SetSSFSCRC((StandSerialFrameStruct*)sendBuffer,cr);
    //send
    if(this->DataSendFun!=NULL)
    {
        this->DataSendFun(sendBuffer,GetSSFSPackageLength((StandSerialFrameStruct*)sendBuffer));
    }
}

/**
* \brief 获得帧总长
* \param SSFS 数据帧
* \return 帧总长
*/
U8 StandSerialProtocol::GetSSFSLength(StandSerialFrameStruct* SSFS)
{
    return(SSFS->Length);
}

/**
* \brief 获得帧属性
* \param SSFS 数据帧
* \return 帧属性
*/
U8 StandSerialProtocol::GetSSFSProperty(StandSerialFrameStruct* SSFS)
{
    return(SSFS->Property);
}

/**
* \brief 获得帧协议ID
* \param SSFS 数据帧
* \return 协议ID
*/
U8 StandSerialProtocol::GetSSFSProtocolID(StandSerialFrameStruct* SSFS)
{
    return(SSFS->Property&0x0f);
}

/**
* \brief 获得帧是否加密
* \param SSFS 数据帧
* \return 帧是否加密
*/
U8 StandSerialProtocol::GetSSFSIsEncrypt(StandSerialFrameStruct* SSFS)
{
    return IS_BIT_TRUE(SSFS->Property,4);
}

/**
* \brief 获得帧数据包
* \param SSFS 数据帧
* \return 帧数据包
*/
U8* StandSerialProtocol::GetSSFSPackage(StandSerialFrameStruct* SSFS)
{
    return(&SSFS->Package);
}

/**
* \brief 获得帧数据包长度
* \param SSFS 数据帧
* \return 帧数据包长度
*/
U8 StandSerialProtocol::GetSSFSPackageLength(StandSerialFrameStruct* SSFS)
{
    return(SSFS->Length-StandSerialProtocolPlusLength);
}

/**
* \brief 获得帧校验
* \param SSFS 数据帧
* \return 帧校验
*/
U16 StandSerialProtocol::GetSSFSCRC(StandSerialFrameStruct* SSFS)
{
    S32 len;
    len=GetSSFSLength(SSFS);
    U16* temp;
    temp=(U16*)(((U8*)SSFS)+len-2);
    return(*temp);
}

/**
* \brief 设置帧总长
* \param SSFS 数据帧
* \param Length 总长
*/
void StandSerialProtocol::SetSSFSLength(StandSerialFrameStruct* SSFS,U8 Length)
{
    SSFS->Length=Length;
}

/**
* \brief 设置帧属性
* \param SSFS 数据帧
* \param Property 属性
*/
void StandSerialProtocol::SetSSFSProperty(StandSerialFrameStruct* SSFS,U8 Property)
{
    SSFS->Property=Property;
}

/**
* \brief 设置帧协议ID
* \param SSFS 数据帧
* \param Property 协议ID
*/
void StandSerialProtocol::SetSSFSProtocolID(StandSerialFrameStruct* SSFS,U8 ProtocolID)
{
    SSFS->Property=ProtocolID&0x0f;
}

/**
* \brief 设置帧是否加密
* \param SSFS 数据帧
* \param Property 是否加密
*/
void StandSerialProtocol::SetSSFSIsEncrypt(StandSerialFrameStruct* SSFS,U8 IsEncrypt)
{
    if(IsEncrypt)
        SET_BIT_TRUE(SSFS->Property,4);
    else
        CLEAR_BIT_TRUE(SSFS->Property,4);
}

/**
* \brief 设置帧校验
* \param SSFS 数据帧
* \param Property 校验
*/
void StandSerialProtocol::SetSSFSCRC(StandSerialFrameStruct* SSFS,U16 CRC)
{
    U8 len;
    len=GetSSFSLength(SSFS);
    *(U16*)(((U8*)SSFS)+len-2)=CRC;
}
}
