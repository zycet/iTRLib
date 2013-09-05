#ifndef _TCPLITEPROTOCOL_H
#define _TCPLITEPROTOCOL_H

#include ".\..\Basic\Basic.h"
#include ".\..\DataStruct\DataStruct.h"

//#define ZTCPDataLengthMax 64
#define TCPLiteQueueLength 8
#define TCPLitePortMax 4

typedef enum
{
	Waiting = 0, Sended = 1, ReSended = 2, Done = 3, Fail = 4
} TCPLiteStateEnum;

typedef struct
{
	U8 Port;
	U8 ID;
	U8* Data;
	U8 DataLength;
	U8 DataCapacity;
} TCPLiteDataStruct;

typedef struct
{
	TCPLiteDataStruct TCPLiteData;
	bool Done, Fail;
	S32 Tick, SendTime;
} TCPLiteStateStruct;

typedef void (*TCPLiteFunctionData)(TCPLiteDataStruct* TCPLiteData);
typedef void (*TCPLiteFunction)(void* TCPLite);

typedef struct
{
	U8 TCPDataLengthMax;
	S32 TimeOut;
	S32 RetryTimes;
	S32 ResponseTimes;

	GeneralSend TCPLiteDataSendFun;
	TCPLiteFunctionData TCPLitePorts[TCPLitePortMax];
	TCPLiteFunctionData TCPLiteOnReceive;
	TCPLiteFunction TCPLiteOnConnectionStateChange;

	BL_QueueU8Struct ToSendQueue;
	TCPLiteStateStruct TCPLiteStates[TCPLiteQueueLength];
	U8* SendBuffer;

	S32 MainID;
	S32 Tick;
	bool NeedResponse;
	bool IsConnected;
} TCPLiteStruct;

//初始化TCPLiteDataStruct结构体并分配指定空间给Data对象
//bool TCPLiteDataInit(TCPLiteDataStruct* TCPLiteData, U8 DataCapacity);
//向TCPLiteData中填充数据
//bool TCPLiteDataFill(TCPLiteDataStruct* TCPLiteData,U8 Port,U8* Data,U8 Length);
//使用缓冲区填充TCPLiteData
bool TCPLiteRAWDataFill(TCPLiteDataStruct* TCPLiteData, U8* Buffer, U8 Length);
//TCPLiteState状态清零
//void TCPLiteStateClear(TCPLiteStateStruct* TCPLiteState);
//TCPLiteState状态初始化,并为其中的TCPLiteData分配空间
//bool TCPLiteStateInit(TCPLiteStateStruct* TCPLiteState,U8 DataCapacity);
//获得连接状态
TCPLiteStateEnum TCPLiteStateEnumGet(TCPLiteStateStruct* TCPLiteState);
//初始化TCPLite并为发送列队分配空间
bool TCPLiteInit(TCPLiteStruct* TCPLite, U8 ZTCPDataLengthMax, GeneralSend TCPLiteDataSendFun);
//注册端口响应
bool TCPLitePortReg(TCPLiteStruct* TCPLite, U8 Port, TCPLiteFunctionData Fun);
//检查发送列队是否有剩余空间
bool TCPLiteToSendAvailable(TCPLiteStruct* TCPLite);
//检查发送列队剩余空间
S32 TCPLiteToSendAvailableNum(TCPLiteStruct* TCPLite);
//获得一个空闲的发送空间
//U8 TCPLiteGetToSendAvailable(TCPLiteStruct* TCPLite);
//按规定格式发送数据
//bool TCPLiteSendRAW(TCPLiteStruct* TCPLite,U8 ID,U8 Port,U8* Data,U8 Length);
//发送数据
bool TCPLiteSend(TCPLiteStruct* TCPLite, U8 Port, U8* Data, U8 Length);
//S32 Add1(S32 ID);
//S32 Sub1(S32 ID);
//更改连接状态
//void ChangeConnectionState(TCPLiteStruct* TCPLite,bool NewState);
//后台数据处理函数
void TCPLiteSendWorkFunation(TCPLiteStruct* TCPLite);
//清空发送列队并重置计数器
//void TCPLiteClear(TCPLiteStruct* TCPLite)
//数据接收处理
void TCPLiteReceiveProcess(TCPLiteStruct* TCPLite, TCPLiteDataStruct* TCPLiteData);

#endif

