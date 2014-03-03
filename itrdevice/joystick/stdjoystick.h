#ifndef STDJOYSTICK_H
#define STDJOYSTICK_H
#include "Ijoystick.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

namespace itr_device
{
class StdJoyStick:public IJoyStick
{
    public:
        StdJoyStick();
        virtual ~StdJoyStick();

       /**
        * \brief 获得摇杆轴的数量
        */
         S32 GetAxisCount();
        /**
        * \brief 获得摇杆按钮的数量

        */
         S32 GetButtonCount();
        /**
        * \brief 获得指定按钮的状态
        * \param 按钮编号
        * \return 1/0 表示按钮是/否按下
        */
         bool GetButtonStatus(S32 index);
        /**
        * \brief 获得指定轴的杆量
        * \param 轴编号
        * \return [0,1],表示杆量
        */
        F32 GetAxisValue(S32 index);
        /**
        * \brief 更新手柄数据
        */
        void Update();
        /**
        * \brief 打开设备
        * \param 设备完整路径名称
        */
         bool Open(char *device);
        /**
        * \brief 关闭设备
        */
        void Close();
    protected:
    private:

   S16 joystick_fd;
   S32 AxisCount;
    S32 ButtonCount;

    struct js_event {
        U32 time;	    /* event timestamp in milliseconds */
        S16 value;              /* value */
        unsigned char type;     /* event type */
        unsigned char number;   /* axis/button number */
    }jse;
    struct wwvi_js_event {
        S32 button[11];
        S32 stick[10];
//        S32 stick_y[10];
    }wjse;

};//class
}//namespace
#endif // STDJOYSTICK_H
