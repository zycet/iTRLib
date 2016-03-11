/*
	数据类型定义
	BUAA 张以成
	2012-8-22
*/
#ifndef __TYPEDEF_H
#define __TYPEDEF_H

#include ".\Config.h"

#if (CORE==CORE_X86||CORE==CORE_CONTEX_M3||CORE==CORE_CONTEX_M4)

typedef	unsigned char U8;
typedef	signed char S8;
typedef	unsigned int U32;
typedef	signed int S32;
typedef	float F32;
typedef	double F64;
typedef	unsigned short U16;
typedef	signed short S16;
typedef	unsigned long long U64;
typedef	signed long long S64;

#endif

#ifndef bool
typedef	U8 bool;
#endif

/*
#ifndef Bool
typedef	U8 Bool;
#endif
*/

/*
#ifndef BOOL
typedef	U8 BOOL;
#endif
*/


#ifndef True
#define True 1
#endif

#ifndef False
#define False 0
#endif


#ifndef Null
#define Null 0
#endif
  
#endif

