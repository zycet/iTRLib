//
// Created by ghdawn on 15-12-20.
//

#include <stdio.h>
#include "log.h"

void Log::log(char *info)
{
    if(!print)
        return ;
    if (time)
    {
        printf("Debug Info:%s cost Time %d\n",info,tc.Tick());
    }
    else
    {
        printf("Debug Info:%s",info);
    }

}
void Log::enableTime()
{
    time = true;
    tc.Tick();
}

void Log::disableTime()
{
    time = false;
}

void Log::enablePrint()
{
    print = true;
}

void Log::disablePrint()
{
    print = false;
}

