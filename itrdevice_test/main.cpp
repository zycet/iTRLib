#include <iostream>
#include <stdio.h>
#include "itrbase.h"
#include "joysticktest.h"
#include "stdcameratest.h"

#include "itrdevice.h"
int main()
{
    JoyStickTest();
    stdcamera_test();
    return 0;
}
