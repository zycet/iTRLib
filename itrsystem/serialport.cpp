#include"serialport.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>    //串口用到的
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>


//#define RS_DEVICE "/dev/ttyACM0"       //串口0

namespace itr_system
{
    SerialPort::SerialPort()
    {

    }                                                 //析构

    void SerialPort::Init(char *name, int baudrate)
    {
        int BAUDRATE;
        struct termios oldtio,newtio;     //termios结构是用来保存波特率、字符大小等
        fd=open(name,O_RDWR|O_NOCTTY);     //以读写方式打开串口。不控制TTY
        if(fd<0)
        {
            perror("error");
            exit(1);                             //失败退出
        }

        tcgetattr(fd,&oldtio);             //保存当前设置到oldtio
        bzero(&newtio,sizeof(newtio));     //清除newtio结构，并重新对它的成员设置如下

        if (baudrate = 115200)
        {
            BAUDRATE = B115200;
        }
        else if (baudrate = 9600)
        {
            BAUDRATE = B9600;
        }
        else if (baudrate = 19200)
        {
            BAUDRATE =B19200;
        }
        newtio.c_cflag=BAUDRATE|CS8|CLOCAL|CREAD;  //9600、8位、忽略DCD信号、启用接收装置
        newtio.c_iflag|=IGNPAR;                    //忽略奇偶
        newtio.c_oflag=0;
        newtio.c_lflag=0;

        newtio.c_cc[VMIN]=0;
        newtio.c_cc[VTIME]=100;                   //在规定时间(VTIME)内读取(VMIN)个字符;
        tcflush(fd,TCIFLUSH);                    //清除所有队列在串口的输入与输出；
        tcsetattr(fd,TCSANOW,&newtio);           //把我们的设置写入termios
    }

    void SerialPort::Close()
    {
        close(fd);
    }

    int SerialPort::Send(unsigned char *Data, int length)
    {
        return write(fd,Data,length);
    }

    int SerialPort::Receive(unsigned char *Data, int length)
    {
        return read(fd,Data,length);
    }
}
