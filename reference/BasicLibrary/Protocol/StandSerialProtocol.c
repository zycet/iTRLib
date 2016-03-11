#include <string.h>
#include ".\..\Basic\Basic.h"
#include ".\..\DataStruct\DataStruct.h"
#include "StandSerialProtocol.h"

void SSPStructInit(StandSerialProtocolStruct* SSPTObj, U8 DefaultS0, U8 DefaultS1, GeneralSend DataSendFun);
S32 SSPProcessRAWByte(StandSerialProtocolStruct* SSPTObj, U8* Buffer, S32 Length);
bool SSPFormatCheck(StandFrameMapStruct* SFMS);
void SSPEncrypt(StandFrameMapStruct* SFMS, U8* Key1, U8* Key2);
void SSPDecrypt(StandFrameMapStruct* SFMS, U8* Key1, U8* Key2);
void SSPInitSFMS(StandFrameMapStruct* SFMS, U8* BaseAddress, U8 PackageLength);
S32 SSPFillSFMS(StandSerialProtocolStruct* SSPTObj, StandFrameMapStruct* SFMS, U8 ProtocolID, U8* Package);
void SSPSendSFMSRAW(StandSerialProtocolStruct* SSPTObj, StandFrameMapStruct* SFMS);
void SSPSendPackage(StandSerialProtocolStruct* SSPTObj, U8 ProtocolID, U8* Package, U8 PackageLength);

//初始化协议栈
//StandSerialProtocolObj=内部待初始化协议堆栈对象
//DefaultS0=协议帧命令字0
//DefaultS1=协议帧命令字1
//SendQueue=数据发送接口对象
void SSPStructInit(StandSerialProtocolStruct* SSPTObj, U8 DefaultS0, U8 DefaultS1, GeneralSend DataSendFun)
{
	SSPTObj->DefaultS0 = DefaultS0;
	SSPTObj->DefaultS1 = DefaultS1;
	SSPTObj->AutoDecrypt = False;
	SSPTObj->AutoEncrypt = False;
	memset(SSPTObj->Key1, 0, sizeof(SSPTObj->Key1));
	memset(SSPTObj->Key2, 0, sizeof(SSPTObj->Key2));
	SSPTObj->IsHaveNewFrame = False;
	SSPTObj->SFMS.BaseAddress = SSPTObj->receiveBuffer;
	SSPTObj->SFMS.PackageLength = 0;
	SSPTObj->receiveBufferState = 0;
	memset(SSPTObj->ProcessFunction, 0, sizeof(SSPTObj->ProcessFunction));
	SSPTObj->DataSendFun = DataSendFun;
}

//处理接收到的串行数据，从中解析协议帧。
//StandSerialProtocolObj=协议堆栈对象
//Buffer=数据接收接口对象
S32 SSPProcessRAWByte(StandSerialProtocolStruct* SSPTObj, U8* Buffer, S32 Length)
{
	S32 receiveFrameNum = 0;
	S32 len;
	S32 i = 0;
	U8 b;
	for(i = 0; i < Length; i++)
	{
		b = Buffer[i];
		if (SSPTObj->receiveBufferState == 0)//S0
		{
			if (b == SSPTObj->DefaultS0)
			{
				SSPTObj->receiveBuffer[SSPTObj->receiveBufferState] = b;
				SSPTObj->receiveBufferState = 1;
			}
		}
		else if (SSPTObj->receiveBufferState == 1)//S1
		{
			if (b == SSPTObj->DefaultS1)
			{
				SSPTObj->receiveBuffer[SSPTObj->receiveBufferState] = b;
				SSPTObj->receiveBufferState = 2;
			}
			else
			{
				SSPTObj->receiveBufferState = 0;
			}
		}
		else if (SSPTObj->receiveBufferState == 2)//Length
		{
			if (b >= 6)
			{
				SSPTObj->receiveBuffer[SSPTObj->receiveBufferState] = b;
				SSPTObj->receiveBufferState = 3;
			}
			else
			{
				SSPTObj->receiveBufferState = 0;
			}
		}
		else if (SSPTObj->receiveBufferState >= 3)//Property+Data+CRC
		{
			SSPTObj->receiveBuffer[SSPTObj->receiveBufferState] = b;
			SSPTObj->receiveBufferState++;
			len = SSPTObj->receiveBuffer[2];
			if(len > StandSerialProtocolMaxLength)
			{
				SSPTObj->receiveBufferState = 0;
			}
			else if (SSPTObj->receiveBufferState >= len)
			{
				if(SSPFormatCheck(&SSPTObj->SFMS))
				{
					SSPTObj->SFMS.PackageLength=SFSLength(&SSPTObj->SFMS)-StandSerialProtocolHeadLength-StandSerialProtocolMateLength-StandSerialProtocolCRCLength;
					if (SSPTObj->AutoDecrypt && SFSIsEncrypt(&SSPTObj->SFMS))
						SSPDecrypt(&SSPTObj->SFMS, SSPTObj->Key1, SSPTObj->Key2);
					SSPTObj->IsHaveNewFrame = True;
					receiveFrameNum++;
					if(SSPTObj->ProcessFunction[SFSProtocolID(&SSPTObj->SFMS)] != Null)
					{
						SSPTObj->ProcessFunction[SFSProtocolID(&SSPTObj->SFMS)](SSPTObj, &SSPTObj->SFMS);
					}
				}
				else
				{
					//UNDONE:Error Sum
				}
				SSPTObj->receiveBufferState = 0;
			}
		}
	}
	return receiveFrameNum;
}

//数据帧CRC16检查
//SFMS=待检查帧
bool SSPFormatCheck(StandFrameMapStruct* SFMS)
{
	if(!(SFSLength(SFMS) >= StandSerialProtocolPlusLength))
		return False;
	if(BL_CRC16Encode((U8*)SFSAddress(SFMS), SFSLength(SFMS)) != 0)
		return False;
	return True;
}

void SSPEncrypt(StandFrameMapStruct* SFMS, U8* Key1, U8* Key2)
{

}

void SSPDecrypt(StandFrameMapStruct* SFMS, U8* Key1, U8* Key2)
{

}

//初始化帧对象
//SFMS=内部待初始化帧对象
//BaseAddress=数据基地址(此地址的空间应该为已分配)
//PackageLength=数据包长度
void SSPInitSFMS(StandFrameMapStruct* SFMS, U8* BaseAddress, U8 PackageLength)
{
	SFMS->BaseAddress = BaseAddress;
	SFMS->PackageLength = PackageLength;
}

//填充帧内容(包长度已确定)
//StandSerialProtocolObj=协议堆栈对象
//SFMS=待填充帧
//ProtocolID=协议ID
//Package=数据包数组
S32 SSPFillSFMS(StandSerialProtocolStruct* SSPTObj, StandFrameMapStruct* SFMS, U8 ProtocolID, U8* Package)
{
	U16 crc;
	SFSAddress(SFMS)->S0 = SSPTObj->DefaultS0;
	SFSAddress(SFMS)->S1 = SSPTObj->DefaultS1;
	SFSLength(SFMS) = SFSPackageLength(SFMS) + StandSerialProtocolPlusLength;
	SFSProperty(SFMS) = ProtocolID & 0x0F;
	memcpy(SFSPackageAddress(SFMS), Package, SFSPackageLength(SFMS));
	if(SSPTObj->AutoEncrypt)
	{
		SSPEncrypt(SFMS, SSPTObj->Key1, SSPTObj->Key2);
	}
	crc = BL_CRC16Encode((U8*)SFSAddress(SFMS), SFSLength(SFMS) - StandSerialProtocolCRCLength);
	SFSCRC(SFMS) = crc;
	return SFSLength(SFMS);
}

//发送帧
//StandSerialProtocolObj=协议堆栈对象
//SFMS=待发送帧
void SSPSendSFMSRAW(StandSerialProtocolStruct* SSPTObj, StandFrameMapStruct* SFMS)
{
	U8* p = SFMS->BaseAddress;
	if(SSPTObj->DataSendFun != Null)
	{
		SSPTObj->DataSendFun(p, SFSLength(SFMS));
	}
}

//发送帧(使用发送缓冲区)
//StandSerialProtocolObj=协议堆栈对象
//ProtocolID=协议ID
//Package=数据包数组
//PackageLength=数据包长度
void SSPSendPackage(StandSerialProtocolStruct* SSPTObj, U8 ProtocolID, U8* Package, U8 PackageLength)
{
	StandFrameMapStruct SFMS;
	SSPInitSFMS(&SFMS, SSPTObj->sendBuffer, PackageLength);
	SSPFillSFMS(SSPTObj, &SFMS, ProtocolID, Package);
	SSPSendSFMSRAW(SSPTObj, &SFMS);
}

