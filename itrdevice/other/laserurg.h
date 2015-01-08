#ifndef LASERURG_H
#define LASERURG_H


class LaserUrg
{
    public:
        /** Default constructor */
        LaserUrg();
        /** Default destructor */
        virtual ~LaserUrg();

        ///初始化串口和波特率
        void Init(char* dev,int baudrate);

        ///获取数据，输入为数据缓冲区和缓冲区大小，返回为实际接收的长度
        ///如果没有数据就返回-1
        int GetData(U8* data, int Length);
        void Close();
    protected:
    private:
};

#endif // LASERURG_H
