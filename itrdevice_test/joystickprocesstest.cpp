#include "joystickprocesstest.h"
#include <stdio.h>
void JoyStickProcessTest()
{
    itr_device::StdJoyStick JoyStickPro;
    char file_name[] ={"/dev/input/js1"};
    if(JoyStickPro.Open(file_name))
    {
        S32 axiscount=0;
        S32 buttoncount=0;
        F32 axisvalue[30]={0};
        S32 buttonstatus[30]={0};
        while(1)
        {
            JoyStickPro.Update();
            usleep(1000);
            axiscount=JoyStickPro.GetAxisCount();
            for(S32 i=0; i<axiscount; i++)
            {
                axisvalue[i]=JoyStickPro.GetAxisValue(i);
                printf("\naxis count :%d\naxis value:",axiscount);
                printf("%f\t",10+5*axisvalue[i]);
            }
        }
    }
}
