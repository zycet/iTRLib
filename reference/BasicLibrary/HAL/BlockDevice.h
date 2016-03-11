/*
	块设备抽象操作函数库
*/
#ifndef _BLOCKDEVICE_H
#define _BLOCKDEVICE_H

#include ".\..\Basic\Basic.h"

typedef bool (*BlockDeviceFunctionVoid)(void);
typedef bool (*BlockDeviceFunctionID)(S32 ID);
typedef bool (*BlockDeviceFunctionIDBuffer)(S32 ID,U8* Buffer);
typedef bool (*BlockDeviceFunction)(S32 ID,U32 Offset,U8* Buffer,U32 Length);

typedef struct
{
	S32 BlockNum;
	S32 BlockSize;

	BlockDeviceFunctionVoid BlockReady;
	BlockDeviceFunction BlockRead;
	BlockDeviceFunctionID BlockReadToBuffer;
	BlockDeviceFunctionIDBuffer BlockWrite;
	BlockDeviceFunctionID BlockErase;
	BlockDeviceFunctionVoid OSLock;
	BlockDeviceFunctionVoid OSUnlock;

	S32 IDReadBuffed;
}BlockDeviceStruct;

typedef struct
{
	BlockDeviceStruct* BlockDevice;
	S32 BlockWriteAutoWaitTime;
	bool AutoWriteOnChangeID;
	bool AutoWriteOnFull;
	bool AutoClearOnEmpty;
	
	U8* WriteBuffer;
	S32 IDWriteBuffed;
	S32 TimeAfterLastWrite;
	bool Modifed;
}BlockOpsStruct;

extern bool BlockDeviceInit(BlockDeviceStruct* BlockDevice,S32 BlockNum, S32 BlockSize, BlockDeviceFunctionVoid BlockReady,BlockDeviceFunction BlockRead,BlockDeviceFunctionID BlockReadToBuffer,BlockDeviceFunctionIDBuffer BlockWrite,BlockDeviceFunctionID BlockErase);
extern bool BlockDeviceCheck(BlockDeviceStruct* BlockDevice);
extern bool BlockOpsInit(BlockOpsStruct* BlockOps,BlockDeviceStruct* BlockDevice,S32 BlockWriteAutoWaitTime,bool AutoWriteOnChangeID,bool AutoWriteOnFull,bool AutoClearOnEmpty);
extern bool BlockRead(BlockOpsStruct* BlockOps,S32 ID,U32 Offset,U8* Buffer,U32 Length);
extern bool BlockWriteToBuffer(BlockOpsStruct* BlockOps,S32 ID,U32 Offset,U8* Buffer,U32 Length);
extern bool BlockWriteForce(BlockOpsStruct* BlockOps);
extern bool BlockWriteAuto(BlockOpsStruct* BlockOps);
extern bool BlockWriteBufferClear(BlockOpsStruct* BlockOps);
extern bool BlockReadPro(BlockOpsStruct* BlockOps,U32 Address,U8* Buffer,U32 Length);
extern bool BlockWritePro(BlockOpsStruct* BlockOps,U32 Address,U8* Buffer,U32 Length);
extern bool BlockErasePro(BlockOpsStruct* BlockOps,U32 Address,U32 BlockNum);

#endif

