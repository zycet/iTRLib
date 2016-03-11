/*
	BlockDevice
	块设备标准操作函数库
	BUAA 20011-12-27
	张以成
*/
#include <stdlib.h>
#include <string.h>
#include ".\..\Basic\Basic.h"
#include ".\BlockDevice.h"

bool BlockDeviceInit(BlockDeviceStruct* BlockDevice,S32 BlockNum, S32 BlockSize, BlockDeviceFunctionVoid BlockReady,BlockDeviceFunction BlockRead,BlockDeviceFunctionID BlockReadToBuffer,BlockDeviceFunctionIDBuffer BlockWrite,BlockDeviceFunctionID BlockErase)
{
	BlockDevice->BlockNum=BlockNum;
	BlockDevice->BlockSize=BlockSize;
	BlockDevice->BlockReady=BlockReady;
	BlockDevice->BlockRead=BlockRead;
	BlockDevice->BlockReadToBuffer=BlockReadToBuffer;
	BlockDevice->BlockWrite=BlockWrite;
	BlockDevice->BlockErase=BlockErase;
	BlockDevice->OSLock=NULL;
	BlockDevice->OSUnlock=NULL;
	BlockDevice->IDReadBuffed=-1;
	return BlockDevice->BlockReady();
}

bool BlockDeviceCheck(BlockDeviceStruct* BlockDevice)
{
	return BlockDevice->BlockReady();
}

bool BlockOpsInit(BlockOpsStruct* BlockOps,BlockDeviceStruct* BlockDevice,S32 BlockWriteAutoWaitTime,bool AutoWriteOnChangeID,bool AutoWriteOnFull,bool AutoClearOnEmpty)
{
	BlockOps->BlockDevice=BlockDevice;
	BlockOps->BlockWriteAutoWaitTime=BlockWriteAutoWaitTime;
	BlockOps->AutoWriteOnChangeID=AutoWriteOnChangeID;
	BlockOps->AutoWriteOnFull=AutoWriteOnFull;
	BlockOps->AutoClearOnEmpty=AutoClearOnEmpty;
	//BlockOps->IDWriteBuffed=-1;
	//BlockOps->TimeAfterLastWrite=0;
	//BlockOps->Modifed=False;
	BlockOps->WriteBuffer=BL_MemAllocEx(BlockDevice->BlockSize);
	if(BlockOps->WriteBuffer==NULL)
		return False;
	BlockWriteBufferClear(BlockOps);
	return True;
}

#define OSLOCK if(Dev->OSLock!=NULL&&Dev->OSUnlock!=NULL){r=Dev->OSLock();}
#define OSUNLOCK if(Dev->OSLock!=NULL&&Dev->OSUnlock!=NULL){r=Dev->OSUnlock();}
#define RETURNCHECK if(r==False){OSUNLOCK return False;}
#define READYCHECK if(Dev->BlockReady!=NULL){r=Dev->BlockReady();RETURNCHECK;}

bool BlockRead(BlockOpsStruct* BlockOps,S32 ID,U32 Offset,U8* Buffer,U32 Length)
{
	bool r;
	BlockDeviceStruct* Dev=BlockOps->BlockDevice;
	if(ID<0||ID>=Dev->BlockNum||Offset+Length>Dev->BlockSize)
	{
		return False;
	}
	OSLOCK;
	READYCHECK;
	if(Dev->BlockReadToBuffer!=NULL)
	{
		if(Dev->IDReadBuffed!=ID)
		{
			r=Dev->BlockReadToBuffer(ID);
			RETURNCHECK;
			Dev->IDReadBuffed=ID;
		}
	}
	r=Dev->BlockRead(ID,Offset,Buffer,Length);
	OSUNLOCK;
	return r;
}

bool BlockWriteToBuffer(BlockOpsStruct* BlockOps,S32 ID,U32 Offset,U8* Buffer,U32 Length)
{
	bool r;
	BlockDeviceStruct* Dev=BlockOps->BlockDevice;
	if(ID<0||ID>=Dev->BlockNum||Offset+Length>Dev->BlockSize)
	{
		return False;
	}
	if(BlockOps->AutoWriteOnChangeID==True)
	{
		if(BlockOps->Modifed&&BlockOps->IDWriteBuffed!=ID)
		{
			r= BlockWriteForce(BlockOps);
			if(r==False)
				return False;
		}
	}
	if(BlockOps->AutoClearOnEmpty==True)
	{
		if(Offset==0)
		{
			BlockWriteBufferClear(BlockOps);
		}
	}
	memcpy(BlockOps->WriteBuffer+Offset,Buffer,Length);
	BlockOps->IDWriteBuffed=ID;
	BlockOps->TimeAfterLastWrite=0;
	BlockOps->Modifed=True;
	if(BlockOps->AutoWriteOnFull==True)
	{
		if(Offset+Length==Dev->BlockSize)
		{
			r= BlockWriteForce(BlockOps);
			if(r==False)
				return False;
		}
	}
	return True;
}

bool BlockWriteForce(BlockOpsStruct* BlockOps)
{
	bool r;
	BlockDeviceStruct* Dev=BlockOps->BlockDevice;
	if(BlockOps->Modifed==False)
		return False;
	if(BlockOps->IDWriteBuffed<0||BlockOps->IDWriteBuffed>=Dev->BlockNum)
		return False;
	OSLOCK;
	READYCHECK;
	r=Dev->BlockErase(BlockOps->IDWriteBuffed);
	RETURNCHECK;
	r=Dev->BlockWrite(BlockOps->IDWriteBuffed,BlockOps->WriteBuffer);
	RETURNCHECK;
	BlockOps->Modifed=False;
	BlockOps->TimeAfterLastWrite=0;
	if(Dev->IDReadBuffed==BlockOps->IDWriteBuffed)
	{
		Dev->IDReadBuffed=-1;
	}
	OSUNLOCK;
	return True;
}

bool BlockWriteAuto(BlockOpsStruct* BlockOps)
{
	bool r;
	if(BlockOps->Modifed==True)
	{
		if(BlockOps->TimeAfterLastWrite>BlockOps->BlockWriteAutoWaitTime)
		{
			r=BlockWriteForce(BlockOps);
			return r;
		}
		else
		{
			BlockOps->TimeAfterLastWrite++;
		}
	}
	return False;
}

bool BlockWriteBufferClear(BlockOpsStruct* BlockOps)
{
	BlockOps->Modifed=False;
	BlockOps->TimeAfterLastWrite=0;
	BlockOps->IDWriteBuffed=-1;
	memset(BlockOps->WriteBuffer,0xFF,BlockOps->BlockDevice->BlockSize);
	return True;
}

bool BlockReadPro(BlockOpsStruct* BlockOps,U32 Address,U8* Buffer,U32 Length)
{
	S32 ID;
	U32 Offset;
	U32 Readed;
	bool r;
	BlockDeviceStruct* Dev=BlockOps->BlockDevice;
	while(Length>0)
	{
		ID=Address/Dev->BlockSize;
		Offset=Address%Dev->BlockSize;
		if(Length>Dev->BlockSize-Offset)
		{
			Readed=Dev->BlockSize-Offset;
		}
		else
		{
			Readed=Length;
		}
		r=BlockRead(BlockOps, ID, Offset, Buffer,Readed);
		if(r==False)
			return False;
		Address+=Readed;
		Buffer+=Readed;
		Length-=Readed;
	}
	return True;
}

bool BlockWritePro(BlockOpsStruct* BlockOps,U32 Address,U8* Buffer,U32 Length)
{
	S32 ID;
	U32 Offset;
	U32 Writed;
	bool r;
	BlockDeviceStruct* Dev=BlockOps->BlockDevice;
	while(Length>0)
	{
		ID=Address/Dev->BlockSize;
		Offset=Address%Dev->BlockSize;
		if(Length>Dev->BlockSize-Offset)
		{
			Writed=Dev->BlockSize-Offset;
		}
		else
		{
			Writed=Length;
		}
		r=BlockWriteToBuffer(BlockOps, ID, Offset, Buffer,Writed);
		if(r==False)
			return False;
		Address+=Writed;
		Buffer+=Writed;
		Length-=Writed;
	}
	return True;
}

bool BlockErasePro(BlockOpsStruct* BlockOps,U32 Address,U32 BlockNum)
{
	U32 i;
	bool r=True;
	BlockDeviceStruct* Dev=BlockOps->BlockDevice;
	S32 ID=Address/Dev->BlockSize;
	OSLOCK;
	READYCHECK;
	for(i=0;i<BlockNum;i++)
	{
		if(ID+i>=Dev->BlockNum)
		{
			return False;
		}
		r=Dev->BlockErase((S32)ID+i);
		RETURNCHECK;
		if(ID+i==Dev->IDReadBuffed)
		{
			Dev->IDReadBuffed=-1;
		}
	}
	OSUNLOCK;
	return r;
}

