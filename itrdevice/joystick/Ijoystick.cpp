#include "Ijoystick.h"

namespace itr_device
{
        IJoyStick::IJoyStick()
        {}
         IJoyStick::~IJoyStick()
        {}
            /**
            * \brief 获得摇杆轴的数量
            */
             S32 IJoyStick::GetAxisCount()
            {return 0;}
            /**
            * \brief 获得摇杆按钮的数量
            */
             S32 IJoyStick::GetButtonCount()
            {return 0;}
            /**
            * \brief 获得指定按钮的状态
            * \param index 按钮编号
            * \return 1/0 表示按钮是/否按下
            */
             bool IJoyStick::GetButtonStatus(S32 index)
            {return true;}
            /**
            * \brief 获得指定轴的杆量
            * \param index 轴编号
            * \return [0,1],表示杆量
            */
             F32 IJoyStick::GetAxisValue(S32 index)
            {return 0;}
            /**
            * \brief 更新手柄数据
            */
             void IJoyStick::Update()
            {}
            /**
            * \brief 打开设备
            * \param device 设备完整路径名称
            */
             bool IJoyStick::Open(char *device)
            {return true;}
            /**
            * \brief 关闭设备
            */
             void IJoyStick::Close()
            {}


}
