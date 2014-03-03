#include "stdjoystick.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

//#define JOYSTICK_DEVNAME "/dev/input/js0"
#define JS_EVENT_BUTTON         0x01    // button pressed/released
#define JS_EVENT_AXIS           0x02    // joystick moved
#define JS_EVENT_INIT           0x80    // initial state of device

namespace itr_device
{
StdJoyStick::StdJoyStick()
{
    //ctor
    joystick_fd=-1;
}

StdJoyStick::~StdJoyStick()
{
    //dtor
}
/**
 * \brief 获得摇杆轴的数量
 */
S32 StdJoyStick::GetAxisCount()
{
    return AxisCount;
}
/**
 * \brief 获得摇杆按钮的数量
 */
S32 StdJoyStick::GetButtonCount()
{
    return ButtonCount;
}
/**
 * \brief 获得指定按钮的状态
 * \param 按钮编号
 * \return 1/0 表示按钮是/否按下
 */
bool StdJoyStick::GetButtonStatus(S32 index)
{
    return wjse.button[index];
}
/**
 * \brief 获得指定轴的杆量
 * \param 轴编号
 * \return [0,1],表示杆量
 */
F32 StdJoyStick::GetAxisValue(S32 index)
{
    return wjse.stick[index];
}
/**
 * \brief 更新手柄数据
 */
void StdJoyStick::Update()
{
    S32 bytes;
    int rc;
	//struct js_event ;
    //struct wwvi_js_event ;

	bytes = read(joystick_fd, &jse, sizeof(jse));

	if (bytes <0)
    {
        printf( "Couldn't open joystick\n" );
		exit(0);
    }
    else
    {
        ioctl( joystick_fd, JSIOCGBUTTONS, &ButtonCount );
        ioctl( joystick_fd, JSIOCGAXES, &AxisCount );
        fcntl( joystick_fd, F_SETFL, O_NONBLOCK );   /* use non-blocking mode */
        while ((rc = bytes == 1))
        {
            jse.type &= ~JS_EVENT_INIT;     /* ignore synthetic events */
            if (jse.type == JS_EVENT_AXIS)
            {
                switch (jse.number)
                {
                    case 0: wjse.stick[0] = jse.value;
                        break;
                    case 1: wjse.stick[1] = jse.value;
                        break;
                    case 2: wjse.stick[2] = jse.value;
                        break;
                    case 3: wjse.stick[3] = jse.value;
                        break;
                    default:
                        break;
                }
            } else if (jse.type == JS_EVENT_BUTTON)
            {
                if (jse.number < 10)
                {
                    switch (jse.value)
                    {
                        case 0:
                        case 1: wjse.button[jse.number] = jse.value;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}
/**
 * \brief 打开设备
 * \param 设备完整路径名称
 */
bool StdJoyStick::Open(char *device)
{
    joystick_fd=open(device,O_RDONLY | O_NONBLOCK); /// read write for force feedback ?
    return (joystick_fd!=-1);
}
/**
 * \brief 关闭设备
 */
void StdJoyStick::Close()
{
    close(joystick_fd);
}

}
