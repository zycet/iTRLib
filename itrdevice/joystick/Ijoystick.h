#ifndef IJOYSTICK_H
#define IJOYSTICK_H

#include "itrbase.h"

namespace itr_device
{

    class IJoyStick
    {
        public:
            /**
            * \brief 获得摇杆轴的数量
            */
            virtual S32 GetAxisCount()=0;
            /**
            * \brief 获得摇杆按钮的数量
            */
            virtual S32 GetButtonCount()=0;
            /**
            * \brief 获得指定按钮的状态
            * \param 按钮编号
            * \return 1/0 表示按钮是/否按下
            */
            virtual bool GetButtonStatus(S32 index)=0;
            /**
            * \brief 获得指定轴的杆量
            * \param 轴编号
            * \return [0,1],表示杆量
            */
            virtual F32 GetAxisValue(S32 index)=0;
            /**
            * \brief 更新手柄数据
            */
            virtual void Update()=0;
            /**
            * \brief 打开设备
            * \param 设备完整路径名称
            */
            virtual bool Open(char *device)=0;
            /**
            * \brief 关闭设备
            */
            virtual void Close();
        protected:
        private:

    };

}

#endif // IJOYSTICK_H
