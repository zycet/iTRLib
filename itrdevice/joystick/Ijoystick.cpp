#include "Ijoystick.h"

namespace itr_device
{
IJoyStick::IJoyStick()
{}
IJoyStick::~IJoyStick()
{}

S32 IJoyStick::GetAxisCount()
{
    return 0;
}

S32 IJoyStick::GetButtonCount()
{
    return 0;
}

bool IJoyStick::GetButtonStatus(S32 index)
{
    return true;
}

F32 IJoyStick::GetAxisValue(S32 index)
{
    return 0;
}

void IJoyStick::Update()
{}

bool IJoyStick::Open(char *device)
{
    return true;
}

void IJoyStick::Close()
{}


}
