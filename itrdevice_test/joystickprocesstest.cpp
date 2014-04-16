#include "joystickprocesstest.h"
#include <stdio.h>
void JoyStickProcessTest()
{
    itr_device::StdJoyStick JoyStickPro;
    char file_name[] ={"/dev/input/js1"};
    if(JoyStickPro.Open(file_name))
    {
        S32 axiscount=0;
        F32 axisvalue[30]={0};
        S32 Width = 10;
        S32 Height = 10;

        while(1)
        {
            JoyStickPro.Update();
            usleep(1000);
            axiscount=JoyStickPro.GetAxisCount();
            for(S32 i=0; i<axiscount; i++)
            {
                axisvalue[i]=JoyStickPro.GetAxisValue(i);
                if(axisvalue[2]>0.8)
                {
                    printf("%f\t", 1.2*Width);
                }
                else if(axisvalue[2]>0.6&&axisvalue[2]<0.8)
                {
                    printf("%f\t", 1.1*Width);
                }
                else if(axisvalue[2]>-0.8&&axisvalue[2]<-0.6)
                {
                    printf("%f\t", 0.9*Width);
                }
                else if(axisvalue[2]<-0.8)
                {
                    printf("%f\t", 0.8*Width);
                }

                if(axisvalue[3]>0.8)
                {
                    printf("%f\t", 1.2*Height);
                }
                else if(axisvalue[3]>0.6&&axisvalue[3]<0.8)
                {
                    printf("%f\t", 1.1*Height);
                }
                else if(axisvalue[3]>-0.8&&axisvalue[3]<-0.6)
                {
                    printf("%f\t", 0.9*Height);
                }
                else if(axisvalue[3]<-0.8)
                {
                    printf("%f\t", 0.8*Height);
                }
            }
        }
    }
}
