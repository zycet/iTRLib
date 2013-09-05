#ifndef _BASEPROTOCOL_H
#define _BASEPROTOCOL_H

//*****Protocol Level 1*****
//****BaseProtocol(ProtocolID=0)****

struct _BaseProtocolStruct
{
	U8 Keyword;
	U8 Data;
};
typedef struct _BaseProtocolStruct BaseProtocolStruct;

//For BaseProtocolStruct
#define BPSAddress(SFMS) ((BaseProtocolStruct*)SFSPackageAddress(SFMS))
#define BPSLength(SFMS) (SFSPackageLength(SFMS))
#define BPSDataLength(SFMS) ((SFSPackageLength(SFMS))-1)
#define BPSDataAddress(SFMS) (&((BPSAddress(SFMS))->Data))

#endif

