#include "stdjoystick.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#define JS_EVENT_BUTTON         0x01    // button pressed/released
#define JS_EVENT_AXIS           0x02    // joystick moved
#define JS_EVENT_INIT           0x80    // initial state of device

namespace itr_device
{
StdJoyStick::StdJoyStick()
{
    for(S32 i=0; i<30; i++)
        wjse.stick[i]=0;
    for(S32 i=0; i<30; i++)
        wjse.button[i]=0;

}

StdJoyStick::~StdJoyStick()
{
    //dtor
}

S32 StdJoyStick::GetAxisCount()
{
    return AxisCount;
}

S32 StdJoyStick::GetButtonCount()
{
    return ButtonCount;
}

bool StdJoyStick::GetButtonStatus(S32 index)
{
    return wjse.button[index];
}

F32 StdJoyStick::GetAxisValue(S32 index)
{
    return ((F32)wjse.stick[index]/32767.0);
}

void StdJoyStick::Update()
{
    S32 bytes;
    AxisCount=0;
    ButtonCount=0;
    ioctl( joystick_fd, JSIOCGBUTTONS, &ButtonCount );
    ioctl( joystick_fd, JSIOCGAXES, &AxisCount );
    fcntl( joystick_fd, F_SETFL, O_NONBLOCK );
    while ( (bytes= read (joystick_fd, &jse , sizeof(struct js_event)))>=0)
    {
        switch(jse.type & ~ JS_EVENT_INIT)
        {
        case JS_EVENT_AXIS :

            wjse.stick[jse.number]=jse.value;
            break;

        case JS_EVENT_BUTTON :

            wjse.button[jse.number]=jse.value;
            break;
        }
    }
}

bool StdJoyStick::Open(char *device)
{
    joystick_fd=-1;
    joystick_fd=open(device,O_RDONLY | O_NONBLOCK); /// read write for force feedback ?| O_NONBLOCK
    return (joystick_fd!=-1);
}

void StdJoyStick::Close()
{
    close(joystick_fd);
}

}
