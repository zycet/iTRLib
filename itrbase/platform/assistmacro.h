/*
 *
 *   Copyright (C) 2013 BUAA iTR Research Center. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * assistmacro.h
 *  Created on: 2013年9月9日
 *      Author: ZYC
 */

#ifndef ASSISTMACRO_H_
#define ASSISTMACRO_H_

#include "typedef.h"

#define ASU8(ADDRESS) (*((U8*)ADDRESS))
#define ASS8(ADDRESS) (*((S8*)ADDRESS))
#define ASU16(ADDRESS) (*((U16*)ADDRESS))
#define ASS16(ADDRESS) (*((S16*)ADDRESS))
#define ASU32(ADDRESS) (*((U32*)ADDRESS))
#define ASS32(ADDRESS) (*((S32*)ADDRESS))
#define ASF32(ADDRESS) (*((F32*)ADDRESS))
#define ASF64(ADDRESS) (*((U64*)ADDRESS))

typedef void (*StandlVoidFun)(void);
typedef void* (*StandMemAllocFun)(S32 Length);
typedef S32 (*StandDataSendFun)(U8* Data, S32 Length);
typedef S32 (*StandMessageSendFun)(const char*);

#define IS_BIT_TRUE(X,n) (((X)&(1<<(n)))==(1<<(n)))
#define SET_BIT_TRUE(X,n) ((X)|(1<<(n)))
#define CLEAR_BIT_TRUE(X,n) ((X)&(~(1<<(n))))

#define GET_SQUARE(X) ((X)*(X))//计算平方
#define GET_CUBE(X) ((X)*(X)*(X))//计算立方
#define GET_MAX(V1,V2) ((V1)>(V2)?(V1):(V2))//取最大值
#define GET_MIN(V1,V2) ((V1)<(V2)?(V1):(V2))//取最小值
#define GET_ABS(X) ((X)>=0?(X):(-(X)))//计算绝对值
#define IS_SAME_SIGN(X1,X2) (((X1)>=0&&(X2)>=0)||((X1)<0&&(X2)<0))
#define IS_LEGAL_FLOAT(X) ((X)==(X))
#define IS_ODD(X) ((X&1)==1)
#define IS_EVEN(X) ((X&1)==0)

#define IS_IN_RANGE(X,MIN,MAX) ((X>=MIN)&&(X<=MAX))
#define GET_IN_RANGE(X,MIN,MAX) ((((X)>=(MIN)?(X):(MIN))<=(MAX))?((X)>=(MIN)?(X):(MIN)):(MAX))

#define GET_SIGN(X) ((X)>0)?1:(((X)<0?-1:0))

#endif // ASSISTMACRO_H_
