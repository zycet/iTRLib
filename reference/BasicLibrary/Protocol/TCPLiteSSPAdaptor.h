/*
	TCPLite与SSP适配文件
	BUAA 张以成
	2013-1-4
*/
#ifndef _TCPLITESSPADAPTOR_H
#define _TCPLITESSPADAPTOR_H

#include ".\..\Basic\Basic.h"
#include ".\Protocol.h"

#define TCPLiteSSPID 1

void TCPLiteSSPHook(TCPLiteStruct* TCPLite,StandSerialProtocolStruct* SSPTObj);

#endif

