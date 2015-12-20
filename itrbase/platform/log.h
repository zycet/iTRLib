//
// Created by ghdawn on 15-12-20.
//

#ifndef ITRLIB_LOG_H
#define ITRLIB_LOG_H


#include <stddef.h>
#include "timeclock.h"

class Log
{
public:
    Log(){print = time = false;}
    void log(char* info=NULL);
    void enableTime();
    void disableTime();
    void enablePrint();
    void disablePrint();

private:
    bool print;
    bool time;
    TimeClock tc;
};


#endif //ITRLIB_LOG_H
