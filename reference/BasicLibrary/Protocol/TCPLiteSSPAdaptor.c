#include ".\..\Basic\Basic.h"
#include ".\..\DataStruct\DataStruct.h"
#include ".\Protocol.h"
#include ".\TCPLiteSSPAdaptor.h"

StandSerialProtocolStruct* SSPForTCPLite;
TCPLiteStruct* SSPTCPLite;

void TCPLiteReceiveFormSSP(void* SSPTObj, StandFrameMapStruct* SFMS)
{
	U8* p=SFSPackageAddress(SFMS);
	TCPLiteDataStruct TCPLiteData;
	TCPLiteData.Port=((*p)&0x03);
	TCPLiteData.ID=((*p)>>2);
	TCPLiteData.Data=p+1;
	TCPLiteData.DataLength=SFSPackageLength(SFMS)-1;
	TCPLiteData.DataCapacity=SFSPackageLength(SFMS)-1;
	TCPLiteReceiveProcess(SSPTCPLite, &TCPLiteData);
}

S32 TCPLiteSendToSSP(U8* Buffer,S32 Length)
{
	SSPSendPackage(SSPForTCPLite,TCPLiteSSPID,Buffer,(U8)Length);
	return Length;
}

void TCPLiteSSPHook(TCPLiteStruct* TCPLite,StandSerialProtocolStruct* SSPObj)
{
	SSPTCPLite=TCPLite;
	SSPForTCPLite=SSPObj;
	TCPLite->TCPLiteDataSendFun=TCPLiteSendToSSP;
	SSPObj->ProcessFunction[TCPLiteSSPID]=TCPLiteReceiveFormSSP;
}
