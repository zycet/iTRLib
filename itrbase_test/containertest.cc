/*
 * containertest.cc
 *
 *  Created on: 2013��9��15��
 *      Author: ZYC
 */

#include "containertest.h"
#include "itrbase.h"

void TestCycleQueue()
{
    S32 t;
    itr_container::CycleQueue<S32> cycleQueue(5);
    cycleQueue.Insert(1);
    cycleQueue.Insert(2);
    cycleQueue.Insert(3);
    cycleQueue.Insert(4);
    cycleQueue.Insert(5);
    cycleQueue.Insert(6);
    cycleQueue.Insert(7);
    cycleQueue.Insert(8);
    cycleQueue.Insert(9);
    cycleQueue.Insert(10);
    assert(cycleQueue[0] == 6);
    assert(cycleQueue[1] == 7);
    assert(cycleQueue[2] == 8);
    assert(cycleQueue[3] == 9);
    assert(cycleQueue[4] == 10);
    cycleQueue.Fetch(t);
    assert(t == 6);
    cycleQueue.Fetch(t);
    assert(t == 7);
    cycleQueue.Fetch(t);
    assert(t == 8);
    cycleQueue.Fetch(t);
    assert(t == 9);
    cycleQueue.Fetch(t);
    assert(t == 10);
    assert(cycleQueue.Fetch(t) == false);

    TRACE_INFO("OK TestCycleQueue()");
}

