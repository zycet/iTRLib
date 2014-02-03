#include "timeclock.h"

TimeClock::TimeClock()
{
    gettimeofday(&tpstart,0);
}

int TimeClock::Tick()
{
    gettimeofday(&tpend,0);
    int timeuse = 1000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    gettimeofday(&tpstart,0);
    return timeuse;
}
