#ifndef LASERURG_H
#define LASERURG_H

#include "iostream"
#include "itrsystem.h"

#define MAX_DATALENGTH      769

using namespace std;
namespace itr_device
{
class LaserUrg
{
    public:
    int StepA;
    int StepB;
    int StepC;
    class OnReceiveData
    {
    public:
        virtual void Process(int* data,int length){}
    };

        ///初始化串口和波特率
        static void Init(char* dev,int baudrate);
        static void SetProcess(OnReceiveData *OnRec);
        static void Start();
        static void Stop();
    protected:
    private:
    static void* WorkThread(void*);
    static OnReceiveData *onRec;
    pthread_t tid;

    static itr_system::SerialPort _sp;
    static int  _data1[ MAX_DATALENGTH];
    static int _data2[ MAX_DATALENGTH];
    static int _length1;
    static int _length2;
    static int* _data;
    static int* _length;

    static bool _data_which;

};
}
#endif // LASERURG_H
