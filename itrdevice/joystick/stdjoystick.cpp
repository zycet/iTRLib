#include "stdjoystick.h"

namespace itr_device
{
StdJoyStick::StdJoyStick()
{
    //ctor
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

 }
/**
 * \brief 获得摇杆按钮的数量
 */
 S32 StdJoyStick::GetButtonCount()
 {

 }
/**
 * \brief 获得指定按钮的状态
 * \param 按钮编号
 * \return 1/0 表示按钮是/否按下
 */
bool StdJoyStick::GetButtonStatus(S32 index)
{

}
/**
 * \brief 获得指定轴的杆量
 * \param 轴编号
 * \return [0,1],表示杆量
 */
F32 StdJoyStick::GetAxisValue(S32 index)
{

}
/**
 * \brief 更新手柄数据
 */
void StdJoyStick::Update()
{

}
/**
 * \brief 打开设备
 * \param 设备完整路径名称
 */
bool StdJoyStick::Open(char *device)
{

}
/**
 * \brief 关闭设备
 */
void StdJoyStick::Close()
{

}

}
