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
        F32 Width = 10;
        F32 Height = 10;

        while(1)
        {
            JoyStickPro.Update();
            usleep(1000);
            axiscount=JoyStickPro.GetAxisCount();
            for(S32 i=0; i<axiscount; i++)
            {
                axisvalue[i]=JoyStickPro.GetAxisValue(i);
                if(axisvalue[4]>0.5||axisvalue[4]<-0.5)
                {
                    Width = Width*(1-axisvalue[4]*0.001);

                }

                if(axisvalue[3]>0.5||axisvalue[3]<-0.5)
                {
                    Height = Height*(1+axisvalue[3]*0.001);

                }
                printf("%f\n", Width);
                printf("%f\n", Height);
                /*if(axisvalue[4]>0.8)
                {
                    Width = 1.002*Width;
                    printf("%f\t", Width);
                }
                else if(axisvalue[4]>0.6&&axisvalue[4]<0.8)
                {
                    Width = 1.001*Width;
                    printf("%f\t", Width);
                }
                else if(axisvalue[4]>-0.8&&axisvalue[4]<-0.6)
                {
                    Width = 0.999*Width;
                    printf("%f\t", Width);
                }
                else if(axisvalue[4]<-0.8)
                {
                    Width = 0.998*Width;
                    printf("%f\t", Width);
                }
                else
                {
                    printf("%f\t", Width);
                }*/

                if(axisvalue[3]>0.8)
                {
                    Height = 1.002*Height;
                    printf("%f\t", 1.2*Height);
                }
                else if(axisvalue[3]>0.6&&axisvalue[3]<0.8)
                {
                    Height = 1.001*Height;
                    printf("%f\t", 1.1*Height);
                }
                else if(axisvalue[3]>-0.8&&axisvalue[3]<-0.6)
                {
                    Height = 0.999*Height;
                    printf("%f\t", 0.9*Height);
                }
                else if(axisvalue[3]<-0.8)
                {
                    Height = 0.998*Height;
                    printf("%f\t", 0.8*Height);
                }
                else
                {
                    printf("%f\t", Height);
                }
            }
            printf("\n");
        }
    }
}
