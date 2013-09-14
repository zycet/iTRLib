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
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 * main.cc
 *  Created on: 2013-9-10
 *      Author: buaa
 */

#include "itrbase.h"

void TestAssistMacro()
{
    //AS Type
    U8 data[4] =
    { 0, 1, 2, 3 };
    U16 u16 = ASU16(&data[0]);
    assert(u16==(0*1+1*256));
    u16 = ASU16(&data[2]);
    assert(u16==(2*1+3*256));

    //Bit Test
    U32 bitTest = 0;
    assert(IS_BIT_TRUE(bitTest,0)==false);
    bitTest = SET_BIT_TRUE(bitTest,0);
    assert(IS_BIT_TRUE(bitTest,0)==true);
    bitTest = CLEAR_BIT_TRUE(bitTest,0);
    assert(IS_BIT_TRUE(bitTest,0)==false);

    //Range
    assert(IS_IN_RANGE(0,-1,1)==true);
    assert(IS_IN_RANGE(-1,-1,1)==true);
    assert(IS_IN_RANGE(1,-1,1)==true);
    assert(IS_IN_RANGE(2,-1,1)==false);
    assert(IS_IN_RANGE(-2,-1,1)==false);
    assert(GET_IN_RANGE(0,-1,1)==0);
    assert(GET_IN_RANGE(2,-1,1)==1);
    assert(GET_IN_RANGE(-2,-1,1)==-1);

    TRACE_INFO("TestAssistMacro() OK");
}

void TestDebugSupport()
{
    //Print
    int Print;
    Print = 0;
    PRINT_DEBUG(Print);
    Print = 1;
    PRINT_INFO(Print);
    Print = 2;
    PRINT_ERROR(Print);

    //TRACE
    TRACE_DEBUG("TRACE_DEBUG");
    TRACE_INFO("TRACE_INFO");
    TRACE_ERROR("TRACE_ERROR");

    TRACE_INFO("TestDebugSupport() OK");
}

void TestMemoryOperation()
{
    //ExMemoryAlloc
    void* m0 = ExMemoryAlloc(0);
    void* m1 = ExMemoryAlloc(EXMEMORY_Length + 1);
    assert(reinterpret_cast<U64>(m0)==EXMEMORY_ORIGINATE);
    assert(m1==NULL);

    //Memory Clear&Compare&Copy&Swap
    U8 buffer0[16] =
    { 0 };
    U8 buffer1[16] =
    { 0 };
    S32 length = sizeof(buffer1) / sizeof(U8);
    MemoryClear(buffer0, length);
    assert(MemoryCompare(buffer0,buffer1,length));
    for (S32 i = 0; i < length; i++)
    {
        buffer0[i] = static_cast<U8>(i);
    }
    MemoryCopy(buffer1, buffer0, length);
    assert(MemoryCompare(buffer0,buffer1,length));
    MemorySwap(&buffer0[0], &buffer0[length / 2], length / 2);
    for (S32 i = 0; i < length / 2; i++)
    {
        assert(buffer0[i]==i+length/2);
    }
    for (S32 i = length / 2; i < length; i++)
    {
        assert(buffer0[i]==i-length/2);
    }

    TRACE_INFO("TestMemoryOperation() OK");
}

void TestCycleQueue()
{
    S32 t;
    itr_container::CycleQueue<S32> cycleQueue = itr_container::CycleQueue<S32>(4);
    cycleQueue.Insert(1);
    cycleQueue.Insert(2);
    cycleQueue.Insert(3);
    cycleQueue.Insert(4);
    cycleQueue.Insert(5);
    cycleQueue.Insert(6);
    assert(cycleQueue[0]==3);
    assert(cycleQueue[1]==4);
    assert(cycleQueue[2]==5);
    assert(cycleQueue[3]==6);
    cycleQueue.Fetch(t);
    assert(t==3);
    cycleQueue.Fetch(t);
    assert(t==4);
    cycleQueue.Fetch(t);
    assert(t==5);
    cycleQueue.Fetch(t);
    assert(t==6);
    assert(cycleQueue.Fetch(t)==false);
}

int main()
{
    TestAssistMacro();
    TestDebugSupport();
    TestMemoryOperation();
    TestCycleQueue();

    return 0;
}

