#include <iostream>
#include <stdio.h>
#include "itrbase.h"
#include "itrvision.h"
#include "joysticktest.h"
#include "asicameratest.h"
#include "V4Ltest.h"
#include "joystickprocesstest.h"
#include "v4ltestbygqp.h"
#include "itrdevice.h"

 int stepa=0;
 int stepb=0;
 int stepc=0;

    class Laser:public itr_device::LaserUrg::OnReceiveData
    {
    public:
        void Process(int* data,int length)
        {
            printf("right:\t %d\tmiddle:\t %d\tleft: \t%d\n",data[stepa],data[stepb],data[stepc]);
        }
    };

int main()
{
    //JoyStickTest();
    //asicamera_test();
//    JoyStickProcessTest();
    itr_math::MathObjStandInit();
    //F4Ltest();
     //v4ltestguan();

     itr_device::LaserUrg lurg;
    lurg.Init("/dev/ttyACM0",115200);
    stepa=lurg.StepA;
    stepb=lurg.StepB;
    stepc=lurg.StepC;
    lurg.SetProcess(new Laser);
    lurg.Start();
    while(1)
    {
    ;
    }
    return 0;
}
