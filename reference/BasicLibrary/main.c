#include <stdio.h>
#include <stdlib.h>
#include "BasicLibrary.h"
/*
void TestMemory()
{
    U8* m1= BL_Malloc(10);
    U8* m2= BL_Malloc(10);
    U8* m3=malloc(10);
}

void TestFormat()
{
    BL_Printf("ABC %d,%f END",10,10.5);
}

void TestQueue()
{
    BL_QueueU8Struct QU8;
    BL_QueueU8Init(&QU8,10);
    BL_QueueU8Insert(&QU8,1);
}
*/

void TestXXTEA()
{
	U32 buff[128];
	U8 i = 0;
	U32 key[4] = {1, 2, 3, 4};
	S32 n = 0;
	for(i = 0; i < 128; i++)
	{
		buff[i] = i;
	}
	BL_XXTEA(buff, 128, key);
	BL_XXTEA(buff, -128, key);
	for(i = 0; i < 128; i++)
	{
		if(buff[i] != i)
			n++;
	}
	printf("XXTEA Error:%d\n", n);
}

void TestTD()
{
	int i=0;
	TDFilterStruct TD;
	TDFilterInit(&TD);
	TD.Cycle=0.01;
	TD.Tr=10;
	TD.Aim=1;
	for(i=0;i<200;i++)
	{
	    float v=TD.V1;
		TDFilter(&TD);
		printf("%f ",v);
	}
	TD.Aim=1;
	getchar();
}

int main()
{
	printf("Hello world!\n");
	//TestMemory();
	//TestFormat();
	//TestQueue();
	//TestXXTEA();
	TestTD();
	return 0;
}

