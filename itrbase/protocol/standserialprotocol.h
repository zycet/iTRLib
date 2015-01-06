#ifndef STANDSERIALPROTOCOL_H
#define STANDSERIALPROTOCOL_H

#include "string.h"
#include "../platform/platform.h"
//#include "../math/math.h"
#include "../container/container.h"
#include "../encode/crc.h"

#define StandSerialProtocolMaxLength 255//帧最大长度
#define StandSerialProtocolHeadLength 2//桢头长度
#define StandSerialProtocolMateLength 2//附加信息长度
#define StandSerialProtocolCRCLength 2//CRC长度
#define StandSerialProtocolPlusLength (StandSerialProtocolHeadLength+StandSerialProtocolMateLength+StandSerialProtocolCRCLength)//帧附加信息总长
#define StandSerialProtocolKey1Length 16//密钥1长度
#define StandSerialProtocolKey2Length 4//密钥2长度

namespace itr_protocol
{

/**
* \brief 帧结构定义结构体
*/
typedef struct
{
    /**
    * \brief 命令字0
    */
    U8 S0;
    /**
    * \brief 命令字1
    */
    U8 S1;
    /**
    * \brief 帧结总长
    */
    U8 Length;
    /**
    * \brief 帧结属性
    */
    U8 Property;
    /**
    * \brief 帧数据起始
    */
    U8 Package;
    //U16 CRC;

} StandSerialFrameStruct;

/**
* \brief 标准串行协议支持库(SSP)
*/
class StandSerialProtocol
{
public:
    /**
    * \brief 帧接收回调函数模板
    * \param SSP 接收到数据的StandSerialProtocol对象
    * \param SSFS 接收到的帧结构体地址
    * \param Package 接收到数据包地址
    * \param PackageLength 接收到数据包长度
    */

    class SSPDataRecFun
    {
        public:
        virtual void Do(StandSerialProtocol* SSP, StandSerialFrameStruct* SSFS,U8* Package,S32 PackageLength){}
    };

     /**
    * \brief 帧发送回调函数模板
    * \param Data 待发送的数据，纯数据
    * \param Length 待发送的数据长度
    */
    class SSPDataSendFun
    {
        public:
        virtual S32 Do(U8* Data, S32 Length){}
    };


    /**
    * \brief 默认构造
    */
    StandSerialProtocol();
    /**
    * \brief 默认析构
    */
    virtual ~StandSerialProtocol();
    /**
    * \brief 默认复制
    */
    StandSerialProtocol(const StandSerialProtocol& other);
    /**
    * \brief 初始化并设定基本参数
    * \param S0 设定的命令字0
    * \param S1 设定的命令字1
    * \param DataSendFun 数据发送函数指针(此库会调用此函数用于发出数据)
    */
    void Init(U8 S0, U8 S1, SSPDataSendFun* DataSendFun);
    /**
    * \brief 处理原始数据流
    * \param Buffer 待处理缓冲区
    * \param BufferLength 待处理缓冲区长度
    */
    S32 ProcessRawByte(U8* Buffer, S32 BufferLength);
    /**
    * \brief 以SSP协议发送指定数据包
    * \param ProtocolID 协作ID
    * \param Package 待发送数据包
    * \param PackageLength 待发送数据包长度
    */
    void SSPSendPackage(U8 ProtocolID, U8* Package, U8 PackageLength);
    /**
    * \brief 获得帧总长
    * \param SSFS 数据帧
    * \return 帧总长
    */
    static U8 GetSSFSLength(StandSerialFrameStruct* SSFS);
    /**
    * \brief 获得帧属性
    * \param SSFS 数据帧
    * \return 帧属性
    */
    static U8 GetSSFSProperty(StandSerialFrameStruct* SSFS);
    /**
    * \brief 获得帧协议ID
    * \param SSFS 数据帧
    * \return 协议ID
    */
    static U8 GetSSFSProtocolID(StandSerialFrameStruct* SSFS);
    /**
    * \brief 获得帧是否加密
    * \param SSFS 数据帧
    * \return 帧是否加密
    */
    static U8 GetSSFSIsEncrypt(StandSerialFrameStruct* SSFS);
    /**
    * \brief 获得帧数据包
    * \param SSFS 数据帧
    * \return 帧数据包
    */
    static U8* GetSSFSPackage(StandSerialFrameStruct* SSFS);
    /**
    * \brief 获得帧数据包长度
    * \param SSFS 数据帧
    * \return 帧数据包长度
    */
    static U8 GetSSFSPackageLength(StandSerialFrameStruct* SSFS);
    /**
    * \brief 获得帧校验
    * \param SSFS 数据帧
    * \return 帧校验
    */
    static U16 GetSSFSCRC(StandSerialFrameStruct* SSFS);
    /**
    * \brief 密钥1
    */
    U8 Key1[StandSerialProtocolKey1Length];
    /**
    * \brief 密钥2
    */
    U8 Key2[StandSerialProtocolKey2Length];
    /**
    * \brief 命令字0
    */
    U8 S0;
    /**
    * \brief 命令字1
    */
    U8 S1;
    /**
    * \brief 是否自动解密
    */
    bool AutoDecrypt;
    /**
    * \brief 是否自动加密
    */
    bool AutoEncrypt;

    /**
    * \brief 设置数据发送函数
    * \param DataSendFun 当要发送数据时需要调用的函数对象
    * \return 是否设置成功
    */
    bool SetDataSendFunc(SSPDataSendFun* DataSendFun);

    /**
    * \brief 设置数据接收处理函数
    * \param ProcessFunc 当要收到数据时需要调用的处理对象
    * \param ID 该对象要处理的协议ID
    * \return 是否设置成功
    */
    bool AddDataRecFunc(SSPDataRecFun* ProcessFunc,S32 ID);

protected:
private:
    /**
    * \brief 加密编码(暂时不实现)
    */
    void SSPEncrypt(StandSerialFrameStruct* SSP, U8* Key1, U8* Key2);
    /**
    * \brief 解密编码(暂时不实现)
    */
    void SSPDecrypt(StandSerialFrameStruct* SSP, U8* Key1, U8* Key2);
    /**
    * \brief 检查长度和CRC是否合法
    */
    bool SSPFormatCheck(StandSerialFrameStruct* SSPF);
    /**
    * \brief 设置帧总长
    * \param SSFS 数据帧
    * \param Length 总长
    */
    static void SetSSFSLength(StandSerialFrameStruct* SSFS,U8 Length);
    /**
    * \brief 设置帧属性
    * \param SSFS 数据帧
    * \param Property 属性
    */
    static void SetSSFSProperty(StandSerialFrameStruct* SSFS,U8 Property);
    /**
    * \brief 设置帧协议ID
    * \param SSFS 数据帧
    * \param Property 协议ID
    */
    static void SetSSFSProtocolID(StandSerialFrameStruct* SSFS,U8 ProtocolID);
    /**
    * \brief 设置帧是否加密
    * \param SSFS 数据帧
    * \param Property 是否加密
    */
    static void SetSSFSIsEncrypt(StandSerialFrameStruct* SSFS,U8 IsEncrypt);
    /**
    * \brief 设置帧校验
    * \param SSFS 数据帧
    * \param Property 校验
    */
    static void SetSSFSCRC(StandSerialFrameStruct* SSFS,U16 CRC);
    /**
    * \brief 数据接收状态指示
    */
    S32 receiveBufferState;
    /**
    * \brief 数据接收缓冲区
    */
    U8 receiveBuffer[StandSerialProtocolMaxLength];
    /**
    * \brief 数据发送缓冲区
    */
    U8 sendBuffer[StandSerialProtocolMaxLength];

     /**
    * \brief 各协议ID对应的回调函数指针组(收到对应数据帧后自动调用)
    */
    SSPDataRecFun* ProcessFunction[16];
    /**
    * \brief 数据发送函数指针(此库会调用此函数用于发出数据)
    */
    SSPDataSendFun* DataSendFun;
};

}

#endif // STANDSERIALPROTOCOL_H
