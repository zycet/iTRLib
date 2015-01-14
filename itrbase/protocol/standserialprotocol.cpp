#include "../platform/platform.h"
//#include "../math/math.h"
#include "../container/container.h"
#include "standserialprotocol.h"

namespace itr_protocol
{

    StandSerialProtocol::StandSerialProtocol()
    {
        for(int i=0; i<16; i++)
        {
            ProcessFunction[i]=NULL;
        }
        DataSendFun=NULL;
    }

    StandSerialProtocol::~StandSerialProtocol()
    {
        //dtor
    }

    StandSerialProtocol::StandSerialProtocol(const StandSerialProtocol &other)
    {
        //copy ctor

        for(S32 i=0; i<StandSerialProtocolKey1Length; i++)
        {
            this->Key1[i]=other.Key1[i];
        }
        for(S32 i=0; i<StandSerialProtocolKey2Length; i++)
        {
            this->Key2[i]=other.Key2[i];
        }
        this->S0=other.S0;
        this->S1=other.S1;
        this->AutoDecrypt=other.AutoDecrypt;
        this->AutoEncrypt=other.AutoEncrypt;
        for(S32 i=0; i<16; i++)
        {
            this->ProcessFunction[i]=other.ProcessFunction[i];
        }
        this->DataSendFun=other.DataSendFun;
        for(S32 i=0; i<StandSerialProtocolMaxLength; i++)
        {
            this->receiveBuffer[i]=other.receiveBuffer[i];
            this->sendBuffer[i]=other.sendBuffer[i];
        }
    }

    /**
       * \brief 初始化并设定基本参数
       * \param S0 设定的命令字0
       * \param S1 设定的命令字1
       * \param DataSendFun 数据发送函数指针(此库会调用此函数用于发出数据)
       */
    void StandSerialProtocol::Init(U8 S0, U8 S1, SSPDataSendFun* DataSendFun)
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

    bool StandSerialProtocol::SSPFormatCheck(StandSerialFrameStruct *SSPF)
    {
        if(!(GetSSFSLength(SSPF) >= StandSerialProtocolPlusLength))
        {
            return false;
        }
        CRC crc_this;
        if(crc_this.BL_CRC16Encode((U8 *)SSPF,GetSSFSLength(SSPF)) != 0)
        {
            return false;
        }
        return true;
    }
    void StandSerialProtocol::SSPEncrypt(StandSerialFrameStruct *SSP, U8 *Key1, U8 *Key2)
    {}
    void StandSerialProtocol::SSPDecrypt(StandSerialFrameStruct *SSP, U8 *Key1, U8 *Key2)
    {}

    S32 StandSerialProtocol::ProcessRawByte(U8 *Buffer, S32 BufferLength)
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
                    StandSerialFrameStruct *SSFS=(StandSerialFrameStruct *)receiveBuffer;
                    if(SSPFormatCheck(SSFS))
                    {

                        if (this->AutoDecrypt && this->AutoEncrypt)
                        {
                            SSPDecrypt(SSFS, this->Key1, this->Key2);
                        }
                        receiveFrameNum++;
                        if(this->ProcessFunction[GetSSFSProtocolID(SSFS)] != NULL)
                        {
                            this->ProcessFunction[GetSSFSProtocolID(SSFS)]->Do(this, SSFS,GetSSFSPackage(SSFS),GetSSFSPackageLength(SSFS));
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

    void StandSerialProtocol::SSPSendPackage(U8 ProtocolID, U8 *Package, S32 PackageLength)
    {
        this->sendBuffer[0]=S0;
        this->sendBuffer[1]=S1;
        SetSSFSLength((StandSerialFrameStruct *)sendBuffer,PackageLength);
        SetSSFSProperty((StandSerialFrameStruct *)sendBuffer,ProtocolID&0x0F);

        memcpy(sendBuffer+4, Package, PackageLength);
        if(this->AutoEncrypt)
        {
            SSPEncrypt((StandSerialFrameStruct *)sendBuffer, this->Key1, this->Key2);
        }
        U16 cr;
        CRC _crcthis;
        cr = _crcthis.BL_CRC16Encode(sendBuffer,GetSSFSLength((StandSerialFrameStruct *)sendBuffer) - StandSerialProtocolCRCLength);
        SetSSFSCRC((StandSerialFrameStruct *)sendBuffer,cr);
        //send
        if(this->DataSendFun!=NULL)
        {
            this->DataSendFun->Do(sendBuffer,GetSSFSLength((StandSerialFrameStruct *)sendBuffer));
        }
    }

    U8 StandSerialProtocol::GetSSFSLength(StandSerialFrameStruct *SSFS)
    {
        return(SSFS->Length);
    }


    U8 StandSerialProtocol::GetSSFSProperty(StandSerialFrameStruct *SSFS)
    {
        return(SSFS->Property);
    }


    U8 StandSerialProtocol::GetSSFSProtocolID(StandSerialFrameStruct *SSFS)
    {
        return(SSFS->Property&0x0f);
    }


    U8 StandSerialProtocol::GetSSFSIsEncrypt(StandSerialFrameStruct *SSFS)
    {
        return IS_BIT_TRUE(SSFS->Property,4);
    }


    U8 *StandSerialProtocol::GetSSFSPackage(StandSerialFrameStruct *SSFS)
    {
        return(&SSFS->Package);
    }


    U8 StandSerialProtocol::GetSSFSPackageLength(StandSerialFrameStruct *SSFS)
    {
        return(SSFS->Length-StandSerialProtocolPlusLength);
    }


    U16 StandSerialProtocol::GetSSFSCRC(StandSerialFrameStruct *SSFS)
    {
        S32 len;
        len=GetSSFSLength(SSFS);
        U16 *temp;
        temp=(U16 *)(((U8 *)SSFS)+len-2);
        return(*temp);
    }


    void StandSerialProtocol::SetSSFSLength(StandSerialFrameStruct *SSFS,U8 Length)
    {
        SSFS->Length=Length+StandSerialProtocolPlusLength;
    }


    void StandSerialProtocol::SetSSFSProperty(StandSerialFrameStruct *SSFS,U8 Property)
    {
        SSFS->Property=Property;
    }


    void StandSerialProtocol::SetSSFSProtocolID(StandSerialFrameStruct *SSFS,U8 ProtocolID)
    {
        SSFS->Property=ProtocolID&0x0f;
    }


    void StandSerialProtocol::SetSSFSIsEncrypt(StandSerialFrameStruct *SSFS,U8 IsEncrypt)
    {
        if(IsEncrypt)
        {
            SET_BIT_TRUE(SSFS->Property,4);
        }
        else
        {
            CLEAR_BIT_TRUE(SSFS->Property,4);
        }
    }


    void StandSerialProtocol::SetSSFSCRC(StandSerialFrameStruct *SSFS,U16 CRC)
    {
        U8 len;
        len=GetSSFSLength(SSFS);
        *(U16 *)(((U8 *)SSFS)+len-2)=CRC;
    }

    bool StandSerialProtocol::SetDataSendFunc(SSPDataSendFun *DataSendFun)
    {
        DataSendFun=DataSendFun;
    }


    bool StandSerialProtocol::AddDataRecFunc(SSPDataRecFun *ProcessFunc, S32 ID)
    {
        ProcessFunction[ID]=ProcessFunc;
    }
}
