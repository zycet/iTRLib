/*
	基础宏定义
	BUAA 张以成
	2012-8-22
*/
#ifndef __MACRODEF_H
#define	__MACRODEF_H

#include ".\Config.h"
#include ".\TypeDef.h"

#define ASU8(ADDRESS) (*((U8*)ADDRESS))
#define ASS8(ADDRESS) (*((S8*)ADDRESS))
#define ASU16(ADDRESS) (*((U16*)ADDRESS))
#define ASS16(ADDRESS) (*((S16*)ADDRESS))
#define ASU32(ADDRESS) (*((U32*)ADDRESS))
#define ASS32(ADDRESS) (*((S32*)ADDRESS))
#define ASF32(ADDRESS) (*((F32*)ADDRESS))
#define ASF64(ADDRESS) (*((U64*)ADDRESS))

#if(ALIG_MACRO_USE==ALIG_MACRO_YES)
#if(COMPILER==COMPILER_GCC)
#define PACKTOU8 #pragma pack(1)
#elif(COMPILER==COMPILER_KIEL)
#define PACKTOU8 __packed
#elif(COMPILER==COMPILER_VC)
#define PACKTOU8 #pragma pack(1)
#endif
#endif

#endif

