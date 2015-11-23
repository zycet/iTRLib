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
 * memoryoperation.cc
 *  Created on: 2013-9-13
 *      Author: buaa
 */

#include "typedef.h"
#include "memoryoperation.h"
#include <stddef.h>

U8* exMomoryOffset = NULL;

void* ExMemoryAlloc(S32 Length)
{
    if (exMomoryOffset + Length > EXMEMORY_Length)
    {
        return NULL;
    }
    else
    {
        U8* temp = exMomoryOffset;
        exMomoryOffset += Length;
        return static_cast<void*>(temp + EXMEMORY_ORIGINATE);
    }
}

void MemoryCopy(void* Destination, void* Source, S32 Length)
{
    U8* dst = static_cast<U8*>(Destination);
    U8* sou = static_cast<U8*>(Source);
    while(Length--)
    {
        *dst = *sou;
        ++dst;
        ++sou;
    }
}

bool MemoryCompare(void* SourceA, void* SourceB, S32 Length)
{
    U8* souA = static_cast<U8*>(SourceA);
    U8* souB = static_cast<U8*>(SourceB);
    while(Length--)
    {
        if(*souA != *souB)
            return false;
        ++souA;
        ++souB;
    }
    return true;
}

void MemoryClear(void* Destination, S32 Length)
{
    U8* dst = static_cast<U8*>(Destination);
    for (int i = 0; i < Length; i++)
    {
        dst[i] = 0;
    }
}

void MemorySwap(void* SourceA, void* SourceB, S32 Length)
{
    U8* souA = static_cast<U8*>(SourceA);
    U8* souB = static_cast<U8*>(SourceB);
    U8 temp;
    while (Length--)
    {
        temp = *souA;
        *souA = *souB;
        *souB = temp;
        ++souA;
        ++souB;
    }
}

