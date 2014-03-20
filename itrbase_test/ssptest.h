#ifndef SSPTEST_H
#define SSPTEST_H
#include "itrbase.h"
void SSPReceivefuc(itr_protocol::StandSerialProtocol* SSP, itr_protocol::StandSerialFrameStruct* SSFS,U8* Package,S32 PackageLength);
void SSPTest();

#endif // SSPTEST_H
