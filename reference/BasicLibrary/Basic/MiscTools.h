/*
	杂项
	BUAA 张以成
	2012-9-23
*/

#ifndef __MISC_H
#define __MISC_H

#include "TypeDef.h"

#define FORMATBUFFMAX 128

typedef void* (*StandMemAlloc)(S32);
typedef void* (*StandMemAllocEx)(S32,bool);
typedef S32 (*StandMessageSend)(const char*);
typedef S32 (*GeneralSend)(U8* Data, S32 Length);
typedef void (*GeneralVoid)(void);

extern StandMemAllocEx ExMemAllocFun;
extern StandMessageSend DebugMessageSendFun;

#define IsBitTrue(X,n) ((X&(1<<n))==(1<<n))
#define SetBitTrue(X,n) (X|(1<<n))
#define ClearBitTrue(X,n) (X&(~(1<<n)))

#define BL_Square(X) ((X)*(X))//计算平方
#define BL_Cube(X) ((X)*(X)*(X))//计算立方
#define BL_Max(V1,V2) (V1>V2?V1:V2)//取最大值
#define BL_Min(V1,V2) (V1<V2?V1:V2)//取最小值
#define BL_ABS(X) (X>=0?X:-X)//计算绝对值
#define BL_SameSign(X1,X2) ((X1>=0&&X2>=0)||(X1<0&&X2<0))

void BL_SwapF32(F32* A,F32* B);
void BL_SwapU8(U8* A,U8* B);
void BL_SwapU8S(U8* A,U8* B,S32 Length);
U8* BL_FormatString(const char* format, ...);
S32 BL_SendDebugString(const char* format, ...);
bool BL_MemComp(void* A, void* B, S32 Length);
S32 BL_MemCopy(void* Dst, void* Src, S32 Length);
S32 BL_MemClear(void* Dst, S32 Length);
void* BL_MemAlloc(S32 Length);
void* BL_MemAllocEx(S32 Length);
U8 BL_CalcSumU8(U8* Data, U32 Length);
U16 BL_CalcSumU16(U8* Data, U32 Length);
void BL_XOR(U8* Buffer, S32 BufferLen, U8* Key, S32 KeyLen);
U16 BL_CRC16Encode(U8* Data, S32 BufferLen);
U32 BL_CRC32Encode(U32 CRC, U8* Buffer, S32 BufferLen);
void BL_XXTEA(U32* Buffer, S32 BufferLen, U32* Key);
void BL_BaseDelay(S32 N);
F32 BL_LimitF32(F32 Value,F32 Min,F32 Max);
F32 BL_CheckF32(F32 Value);
bool BL_InRange(F32 Value,F32 Min,F32 Max);
F32 BL_ABSAdject(F32 Value,F32 Adject);

#endif

