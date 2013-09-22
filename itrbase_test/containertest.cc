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
    cycleQueue.Insert(11);
    cycleQueue.Insert(12);
    cycleQueue.Insert(13);
    cycleQueue.Insert(14);
    cycleQueue.Insert(15);
    cycleQueue.Fetch(t);
    assert(t == 11);
    cycleQueue.Fetch(t);
    assert(t == 12);
    cycleQueue.Fetch(t);
    assert(t == 13);
    cycleQueue.Fetch(t);
    assert(t == 14);
    cycleQueue.Fetch(t);
    assert(t == 15);
    cycleQueue.Insert(16);
    cycleQueue.Insert(17);
    cycleQueue.Insert(18);
    cycleQueue.Insert(19);
    cycleQueue.Insert(20);
    cycleQueue.Insert(21);
    cycleQueue.Insert(22);
    cycleQueue.Insert(23);
    cycleQueue.Insert(24);
    cycleQueue.Insert(25);
    cycleQueue.Insert(26);
    cycleQueue.Insert(27);
    cycleQueue.Insert(28);
    cycleQueue.Insert(29);
    cycleQueue.Insert(30);
    cycleQueue.Fetch(t);
    assert(t == 26);
    cycleQueue.Fetch(t);
    assert(t == 27);
    cycleQueue.Fetch(t);
    assert(t == 28);
    cycleQueue.Fetch(t);
    assert(t == 29);
    cycleQueue.Fetch(t);
    assert(t == 30);
    assert(cycleQueue.Fetch(t) == false);

    TRACE_INFO("OK TestCycleQueue()");
}
