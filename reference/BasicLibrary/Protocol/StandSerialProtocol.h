#ifndef STANDSERIALPROTOCOL
#define STANDSERIALPROTOCOL

#include ".\..\Basic\Basic.h"
#include ".\..\DataStruct\DataStruct.h"

//*****Protocol Level 0*****

#define StandSerialProtocolMaxLength 255
#define StandSerialProtocolHeadLength 2
#define StandSerialProtocolMateLength 2
#define StandSerialProtocolCRCLength 2
#define StandSerialProtocolPlusLength StandSerialProtocolHeadLength+StandSerialProtocolMateLength+StandSerialProtocolCRCLength
#define StandSerialProtocolKey1Length 16
#define StandSerialProtocolKey2Length 4

struct _StandFrameStruct
{
	U8 S0, S1;
	U8 Length;
	U8 Property;
	U8 Package;
	//U16 CRC;
};
typedef struct _StandFrameStruct StandFrameStruct;

struct _StandFrameMapStruct
{
	U8* BaseAddress;
	U8 PackageLength;
};
typedef struct _StandFrameMapStruct StandFrameMapStruct;

//For StandFrameStruct
#define SFSAddress(SFMS) ((StandFrameStruct*)((SFMS)->BaseAddress))
#define SFSLength(SFMS) ((SFSAddress(SFMS))->Length)
#define SFSProperty(SFMS) ((SFSAddress(SFMS))->Property)
#define SFSProtocolID(SFMS) ((SFSProperty(SFMS))&0x0F)
#define SFSIsEncrypt(SFMS) (((SFSProperty(SFMS))&0x10)==0x10)
#define SFSPackageAddress(SFMS) (&((SFSAddress(SFMS))->Package))
#define SFSPackageLength(SFMS) ((SFMS)->PackageLength)
#define SFSCRC(SFMS) (*((U16*)((SFSPackageAddress(SFMS))+(SFSPackageLength(SFMS)))))

typedef void (*SSPReceive)(void* SSPTObj, StandFrameMapStruct* SFMS);

struct _StandSerialProtocolStruct
{
	U8 DefaultS0, DefaultS1;
	bool AutoDecrypt, AutoEncrypt;
	U8 Key1[StandSerialProtocolKey1Length];
	U8 Key2[StandSerialProtocolKey2Length];
	bool IsHaveNewFrame;
	StandFrameMapStruct SFMS;
	SSPReceive ProcessFunction[16];
	GeneralSend DataSendFun;
	S32 receiveBufferState;
	U8 receiveBuffer[StandSerialProtocolMaxLength];
	U8 sendBuffer[StandSerialProtocolMaxLength];
};
typedef struct _StandSerialProtocolStruct StandSerialProtocolStruct;

//初始化协议栈
//StandSerialProtocolObj=内部待初始化协议堆栈对象
//DefaultS0=协议帧命令字0
//DefaultS1=协议帧命令字1
//SendQueue=数据发送接口对象
void SSPStructInit(StandSerialProtocolStruct* SSPTObj, U8 DefaultS0, U8 DefaultS1, GeneralSend DataSendFun);
//处理接收到的串行数据，从中解析协议帧。
//StandSerialProtocolObj=协议堆栈对象
//Buffer=数据接收接口对象
S32 SSPProcessRAWByte(StandSerialProtocolStruct* SSPTObj, U8* Buffer, S32 Length);
//数据帧CRC16检查
//SFMS=待检查帧
//bool SSPFormatCheck(StandFrameMapStruct *SFMS);
//void SSPEncrypt(StandFrameMapStruct *SFMS, U8 *Key1, U8 *Key2);
//void SSPDecrypt(StandFrameMapStruct *SFMS, U8 *Key1, U8 *Key2);
//初始化帧对象
//SFMS=内部待初始化帧对象
//BaseAddress=数据基地址(此地址的空间应该为已分配)
//PackageLength=数据包长度
//void SSPInitSFMS(StandFrameMapStruct *SFMS, U8 *BaseAddress, U8 PackageLength);
//填充帧内容(包长度已确定)
//StandSerialProtocolObj=协议堆栈对象
//SFMS=待填充帧
//ProtocolID=协议ID
//Package=数据包数组
//S32 SSPFillSFMS(StandSerialProtocolStruct *SSPTObj, StandFrameMapStruct *SFMS, U8 ProtocolID, U8 *Package);
//发送帧
//StandSerialProtocolObj=协议堆栈对象
//SFMS=待发送帧
//void SSPSendSFMSRAW(StandSerialProtocolStruct *SSPTObj, StandFrameMapStruct *SFMS);
//发送帧(使用发送缓冲区)
//StandSerialProtocolObj=协议堆栈对象
//ProtocolID=协议ID
//Package=数据包数组
//PackageLength=数据包长度
void SSPSendPackage(StandSerialProtocolStruct* SSPTObj, U8 ProtocolID, U8* Package, U8 PackageLength);

#endif

