#ifndef SERIALPORT_H
#define SERIALPORT_H

namespace itr_system
{
    class SerialPort
    {

        public:
            SerialPort();
            int fd;
            void Init(char *name, int baudrate);
            void Close();
            int Send(unsigned char *Data, int length);
            int Receive(unsigned char *Data, int length);
//protected:
            //virtual void run();
    };
}
#endif
