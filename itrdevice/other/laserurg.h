#ifndef LASERURG_H
#define LASERURG_H

#include "iostream"
using namespace std;

class LaserUrg
{
    public:
    class OnReceiveData
    {
        virtual void Process(int data,int length){}
    };
        /** Default constructor */
        LaserUrg();
        /** Default destructor */
        virtual ~LaserUrg();

        ///初始化串口和波特率
        void Init(char* dev,int baudrate);
        void SetProcess(OnReceiveData *OnRec);
        void Start();
        void Stop();
    protected:
    private:
    static void* WorkThread(void*);
    OnReceiveData *onRec;
    pthread_t tid;
};

#endif // LASERURG_H
