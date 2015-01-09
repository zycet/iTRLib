#ifndef SERIALPORT_H
#define SERIALPORT_H

namespace itr_system
{
    class SerialPort
    {
        private:
            int fd;
        public:
            SerialPort();

            int Init(char *name, int baudrate);
            void Close();
            int Send(unsigned char *Data, int length);
            int Read(unsigned char *Data, int length);
            int ReadLine(unsigned char *Data, int length);
//protected:
            //virtual void run();
    };
}
#endif
