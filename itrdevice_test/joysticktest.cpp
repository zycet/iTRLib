#include "joysticktest.h"

using namespace itr_device;

void JoyStickTest()
{
    StdJoyStick Joyst;
    char file_name[] ={"/dev/input/js0"};
    Joyst.Open(file_name);

}
