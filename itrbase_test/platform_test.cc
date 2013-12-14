/*
 * platform_test.cc
 *
 *  Created on: 2013��9��15��
 *      Author: ZYC
 */

#include "itrbase.h"

void TestAssistMacro()
{
    //AS Type
    U8 data[4] =
    { 0, 1, 2, 3 };
    U16 u16 = ASU16(&data[0]);
    assert(u16 == (0 * 1 + 1 * 256));
    u16 = ASU16(&data[2]);
    assert(u16 == (2 * 1 + 3 * 256));

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

    TRACE_INFO("OK TestAssistMacro()");
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

    TRACE_INFO("OK TestDebugSupport()");
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
    assert(MemoryCompare(buffer0, buffer1, length));
    for (S32 i = 0; i < length; i++)
    {
        buffer0[i] = static_cast<U8>(i);
    }
    MemoryCopy(buffer1, buffer0, length);
    assert(MemoryCompare(buffer0, buffer1, length));
    MemorySwap(&buffer0[0], &buffer0[length / 2], length / 2);
    for (S32 i = 0; i < length / 2; i++)
    {
        assert(buffer0[i] == i + length / 2);
    }
    for (S32 i = length / 2; i < length; i++)
    {
        assert(buffer0[i] == i - length / 2);
    }

    TRACE_INFO("OK TestMemoryOperation()");
}

void TestTypedef()
{
    assert(sizeof(U8) == 1);
    assert(sizeof(S8) == 1);
    assert(sizeof(U16) == 2);
    assert(sizeof(S16) == 2);
    assert(sizeof(U32) == 4);
    assert(sizeof(S32) == 4);
    assert(sizeof(F32) == 4);
    assert(sizeof(S64) == 8);
    assert(sizeof(U64) == 8);
    assert(sizeof(BOOL) == 1);
    TRACE_INFO("OK TestTypedef()");
}
