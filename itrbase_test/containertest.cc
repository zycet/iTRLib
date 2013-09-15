/*
 * containertest.cc
 *
 *  Created on: 2013Äê9ÔÂ15ÈÕ
 *      Author: ZYC
 */

#include "containertest.h"
#include "itrbase.h"

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

