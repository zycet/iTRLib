#ifndef TIMECLOCK_H
#define TIMECLOCK_H
#include <sys/time.h>

class TimeClock
{
    public:
        /** Default constructor */
        TimeClock();
        /**
        * \brief 手动计时一次
        * \return 从上一次Tick到现在的时间间隔
        */
        int Tick();
    protected:
    private:
        struct timeval tpstart;
        struct timeval tpend;
};

#endif // TIMECLOCK_H
