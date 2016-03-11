/*
	ZTCPLite协议1.0支持软件包
	张以成BUAA
*/
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include ".\..\Basic\Basic.h"
#include ".\..\DataStruct\DataStruct.h"
#include "TCPLiteProtocol.h"

//初始化TCPLiteDataStruct结构体并分配指定空间给Data对象
bool TCPLiteDataInit(TCPLiteDataStruct* TCPLiteData, U8 DataCapacity)
{
	TCPLiteData->ID = 0;
	TCPLiteData->Port = 0;
	TCPLiteData->DataLength = 0;
	TCPLiteData->DataCapacity = 0;
	TCPLiteData->Data = BL_MemAllocEx(DataCapacity);
	if(TCPLiteData->Data == Null)
		return False;
	TCPLiteData->DataCapacity = DataCapacity;
	return True;
}

//向TCPLiteData中填充数据
bool TCPLiteDataFill(TCPLiteDataStruct* TCPLiteData, U8 Port, U8* Data, U8 Length)
{
	if(TCPLiteData->Data == Null)
		return False;
	if(TCPLiteData->DataCapacity < Length)
		return False;
	TCPLiteData->ID = 0;
	TCPLiteData->Port = Port;
	memcpy(TCPLiteData->Data, Data, Length);
	TCPLiteData->DataLength = Length;
	return True;
}

//使用缓冲区填充TCPLiteData
bool TCPLiteRAWDataFill(TCPLiteDataStruct* TCPLiteData, U8* Buffer, U8 Length)
{
	if(Length < 1)
		return False;
	TCPLiteData->Port = Buffer[0] & 0x03;
	TCPLiteData->ID = Buffer[0] >> 2;
	TCPLiteData->Data = Null;
	TCPLiteData->DataLength = Length - 1;
	TCPLiteData->DataCapacity = Length - 1;
	if(Length > 1)
	{
		TCPLiteData->Data = &Buffer[1];
	}
	return True;
}

//TCPLiteState状态清零
void TCPLiteStateClear(TCPLiteStateStruct* TCPLiteState)
{
	TCPLiteState->Done = False;
	TCPLiteState->Fail = False;
	TCPLiteState->Tick = 0;
	TCPLiteState->SendTime = 0;
}

//TCPLiteState状态初始化,并为其中的TCPLiteData分配空间
bool TCPLiteStateInit(TCPLiteStateStruct* TCPLiteState, U8 DataCapacity)
{
	TCPLiteStateClear(TCPLiteState);
	return TCPLiteDataInit(&TCPLiteState->TCPLiteData, DataCapacity);
}

//获得连接状态
TCPLiteStateEnum TCPLiteStateEnumGet(TCPLiteStateStruct* TCPLiteState)
{
	if(TCPLiteState->Done == True)
	{
		return Done;
	}
	else if(TCPLiteState->Fail == True)
	{
		return Fail;
	}
	else if(TCPLiteState->SendTime == 0)
	{
		return Waiting;
	}
	else if(TCPLiteState->SendTime == 1)
	{
		return Sended;
	}
	else
	{
		return ReSended;
	}
}

//初始化TCPLite并为发送列队分配空间
bool TCPLiteInit(TCPLiteStruct* TCPLite, U8 TCPDataLengthMax, GeneralSend TCPLiteDataSendFun)
{
	bool r;
	S32 i;

	TCPLite->TCPDataLengthMax = TCPDataLengthMax;
	TCPLite->TimeOut = 100;
	TCPLite->RetryTimes = 10;
	TCPLite->ResponseTimes = 2;

	TCPLite->TCPLiteDataSendFun = TCPLiteDataSendFun;
	for(i = 0; i < TCPLitePortMax; i++)
	{
		TCPLite->TCPLitePorts[i] = Null;
	}
	TCPLite->TCPLiteOnReceive = Null;
	TCPLite->TCPLiteOnConnectionStateChange = Null;

	BL_QueueU8Init(&TCPLite->ToSendQueue, TCPLiteQueueLength);
	for(i = 0; i < TCPLiteQueueLength; i++)
	{
		r = TCPLiteStateInit(&TCPLite->TCPLiteStates[i], TCPLite->TCPDataLengthMax);
		if(r == False)
			return False;
	}
	TCPLite->SendBuffer = BL_MemAllocEx(TCPLite->TCPDataLengthMax+1);
	if(TCPLite->SendBuffer == Null)
		return False;

	TCPLite->MainID = 0;
	TCPLite->Tick = 0;
	TCPLite->NeedResponse = False;
	TCPLite->IsConnected = False;

	return True;
}

//注册端口响应
bool TCPLitePortReg(TCPLiteStruct* TCPLite, U8 Port, TCPLiteFunctionData Fun)
{
	if(Port >= TCPLitePortMax)
		return False;
	TCPLite->TCPLitePorts[Port] = Fun;
	return True;
}

//检查发送列队是否有剩余空间
bool TCPLiteToSendAvailable(TCPLiteStruct* TCPLite)
{
	if(TCPLite->ToSendQueue.Length - TCPLite->ToSendQueue.Count >= 1)
		return True;
	return False;
}

//检查发送列队剩余空间
S32 TCPLiteToSendAvailableNum(TCPLiteStruct* TCPLite)
{
	return (TCPLite->ToSendQueue.Length - TCPLite->ToSendQueue.Count);
}

//获得一个空闲的发送空间
U8 TCPLiteGetToSendAvailable(TCPLiteStruct* TCPLite)
{
	U8 i, j, nouse;
	for(i = 0; i < TCPLiteQueueLength; i++)
	{
		nouse = True;
		for(j = 0; j < TCPLite->ToSendQueue.Count; j++)
		{
			if(BL_QueueU8Read(&TCPLite->ToSendQueue, j) == i)
			{
				nouse = False;
				break;
			}
		}
		if(nouse == True)
			return i;
	}
	return 0;
}

//按规定格式发送数据
bool TCPLiteSendRAW(TCPLiteStruct* TCPLite, U8 ID, U8 Port, U8* Data, U8 Length)
{
	U8 len = 0;
	if(TCPLite->TCPLiteDataSendFun == Null)
		return False;
	if(TCPLite->SendBuffer == Null)
		return False;
	TCPLite->SendBuffer[0] = (U8)((Port & 0x03) | ((ID & 0x3F) << 2));
	len += 1;
	if(Length != 0)
	{
		if(Data == Null)
			return False;
		memcpy(&TCPLite->SendBuffer[1], Data, Length);
		len += Length;
	}
	return TCPLite->TCPLiteDataSendFun(TCPLite->SendBuffer, len) == len;
}

//发送数据
bool TCPLiteSend(TCPLiteStruct* TCPLite, U8 Port, U8* Data, U8 Length)
{
	U8 r;
	U8 BufferID;
	if(TCPLiteToSendAvailable(TCPLite) == False)
		return False;
	if(TCPLite->IsConnected == False && TCPLite->ToSendQueue.Count == 0)
	{
		TCPLite->MainID = 0;
		r = TCPLiteSendRAW(TCPLite, 0, 0, Null, 0);
		if(r == False)
			return False;
	}
	BufferID = TCPLiteGetToSendAvailable(TCPLite);
	TCPLiteStateClear(&TCPLite->TCPLiteStates[BufferID]);
	r = TCPLiteDataFill(&TCPLite->TCPLiteStates[BufferID].TCPLiteData, Port, Data, Length);
	if(r == False)
		return False;
	BL_QueueU8Insert(&TCPLite->ToSendQueue, BufferID);
	//TCPLiteSendRAW(TCPLite,128,(U8)(0x30+TCPLite->ToSendQueue.Count),Null,0);//DEBUG
	return True;
}

S32 Add1(S32 ID)
{
	if (ID == 63)
		return 1;
	return ID + 1;
}

S32 Sub1(S32 ID)
{
	if (ID == 1)
		return 63;
	return ID - 1;
}

//更改连接状态
void ChangeConnectionState(TCPLiteStruct* TCPLite, bool NewState)
{
	if(NewState != TCPLite->IsConnected)
	{
		TCPLite->IsConnected = NewState;
		if(TCPLite->TCPLiteOnConnectionStateChange != Null)
		{
			TCPLite->TCPLiteOnConnectionStateChange(TCPLite);
		}
	}
}

//后台数据处理函数
void TCPLiteSendWorkFunation(TCPLiteStruct* TCPLite)
{
	if(TCPLite->ToSendQueue.Count > 0)
	{
		U8 ToSend0ID = BL_QueueU8Read(&TCPLite->ToSendQueue, 0);
		TCPLiteStateStruct* ToSend0 = &TCPLite->TCPLiteStates[ToSend0ID];
		if(ToSend0->SendTime > TCPLite->RetryTimes)
		{
			ToSend0->Fail = True;
			BL_QueueU8Clear(&TCPLite->ToSendQueue);
			ChangeConnectionState(TCPLite, False);
		}
		else if(ToSend0->Tick % TCPLite->TimeOut == 0)
		{
			if(ToSend0->TCPLiteData.ID == 0)
			{
				TCPLite->MainID = Add1(TCPLite->MainID);
				ToSend0->TCPLiteData.ID = (U8)TCPLite->MainID;
			}
			//TCPLiteSendRAW(TCPLite,128,3,Null,0);//Debug
			TCPLiteSendRAW(TCPLite, ToSend0->TCPLiteData.ID, ToSend0->TCPLiteData.Port, ToSend0->TCPLiteData.Data, ToSend0->TCPLiteData.DataLength);
			ToSend0->SendTime++;
			ToSend0->Tick++;
			TCPLite->NeedResponse = False;
		}
		else
		{
			ToSend0->Tick++;
		}
	}
	TCPLite->Tick++;
	//if (TCPLite->NeedResponse == True && TCPLite->Tick % TCPLite->ResponseTimes == 0)
	if (TCPLite->NeedResponse == True)
	{
		TCPLite->MainID = Add1(TCPLite->MainID);
		TCPLiteSendRAW(TCPLite, (U8)TCPLite->MainID, 0, Null, 0);
		TCPLite->NeedResponse = False;
	}
}

//清空发送列队并重置计数器
void TCPLiteClear(TCPLiteStruct* TCPLite)
{
	TCPLite->MainID = 0;
	TCPLite->Tick = 0;
	BL_QueueU8Clear(&TCPLite->ToSendQueue);
}

//数据接收处理
void TCPLiteReceiveProcess(TCPLiteStruct* TCPLite, TCPLiteDataStruct* TCPLiteData)
{
	//TCPLiteSendRAW(TCPLite,129,TCPLiteData->ID,Null,0);//Debug
	//TCPLiteSendRAW(TCPLite,130,(U8)TCPLite->MainID,Null,0);//Debug
	if(TCPLiteData->ID == 0)
	{
		TCPLiteClear(TCPLite);
		TCPLite->NeedResponse = True;
		ChangeConnectionState(TCPLite, True);
	}
	else if (TCPLiteData->ID == Sub1(TCPLite->MainID))
	{
		TCPLiteSendRAW(TCPLite, (U8)TCPLite->MainID, 0, Null, 0);
	}
	else if (TCPLiteData->ID == TCPLite->MainID)
	{
		TCPLite->NeedResponse = True;
	}
	else if (TCPLiteData->ID == Add1(TCPLite->MainID))
	{
		//TCPLiteSendRAW(TCPLite,128,1,Null,0);//Debug
		if(TCPLite->ToSendQueue.Count > 0)
		{
			U8 ToSend0ID = BL_QueueU8Read(&TCPLite->ToSendQueue, 0);
			TCPLiteStateStruct* ToSend0 = &TCPLite->TCPLiteStates[ToSend0ID];
			//TCPLiteSendRAW(TCPLite,132,ToSend0->TCPLiteData.ID,Null,0);//Debug
			if(ToSend0->TCPLiteData.ID == Sub1(TCPLiteData->ID))
			{
				ChangeConnectionState(TCPLite, True);
				ToSend0->Done = True;
				BL_QueueU8Fetch(&TCPLite->ToSendQueue);
				//TCPLiteSendRAW(TCPLite,128,2,Null,0);//Debug
			}
		}
		TCPLite->MainID = TCPLiteData->ID;
		//TCPLiteSendRAW(TCPLite,131,(U8)TCPLite->MainID,Null,0);//Debug
		if(TCPLiteData->DataLength > 0)
		{
			TCPLite->NeedResponse = True;
		}
		if(TCPLiteData->DataLength > 0 && TCPLiteData->Data != Null)
		{
			if(TCPLite->TCPLiteOnReceive != Null)
			{
				TCPLite->TCPLiteOnReceive(TCPLiteData);
			}
			if(TCPLiteData->Port < TCPLitePortMax)
			{
				if(TCPLite->TCPLitePorts[TCPLiteData->Port] != Null)
				{
					TCPLite->TCPLitePorts[TCPLiteData->Port](TCPLiteData);
				}
			}
		}

	}
	else {}
}

