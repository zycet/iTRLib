/*
	可随机访问的循环FIFO列队
	BUAA 张以成
	2012-8-23
*/
#include <stdlib.h>
#include ".\..\Basic\Basic.h"
#include "Queue.h"

//*****Queue of U8*****
//计数加一
void _BL_QueueU8StartAdd (BL_QueueU8Struct* Obj)
{
	Obj->_Start++;
	if (Obj->_Start >= Obj->Length)
	{
		Obj->_Start -= Obj->Length;
	}
}

//初始化列队
void BL_QueueU8Init (BL_QueueU8Struct* Obj, S32 Length)
{
	Obj->_Start = 0;
	Obj->Count = 0;
	Obj->Length = Length;
	Obj->_Data = Null;
	Obj->_Data = BL_MemAllocEx(Length * sizeof (U8));
	assert(Obj->_Data);
	BL_MemClear(Obj->_Data, Length * sizeof (U8));
}

//清除列队中的数据
void BL_QueueU8Clear (BL_QueueU8Struct* Obj)
{
	Obj->_Start = 0;
	Obj->Count = 0;
}

//释放列队所占用空间
void BL_QueueU8Free (BL_QueueU8Struct* Obj)
{
	Obj->Length = 0;
	free (Obj->_Data);
}

//返回值=TRUE时说明列队已满新插入的数据已挤占最老的数据的位置
U8 BL_QueueU8Insert (BL_QueueU8Struct* Obj, U8 C)
{
	U32 t = Obj->_Start + Obj->Count;
	if (t >= Obj->Length)
	{
		t -= Obj->Length;
	}
	Obj->_Data[t] = C;
	if (Obj->Count == Obj->Length)
	{
		_BL_QueueU8StartAdd (Obj);
		return True;
	}
	else
	{
		Obj->Count++;
		return False;
	}
}

//取出最早的数据，如果为空则返回0。
U8 BL_QueueU8Fetch (BL_QueueU8Struct* Obj)
{
	assert(Obj->Count > 0);
	if (Obj->Count > 0)
	{
		U8 c = Obj->_Data[Obj->_Start];
		_BL_QueueU8StartAdd (Obj);
		Obj->Count--;
		return c;
	}
	else
	{
		return 0;
	}
}

//按插入顺序读取数据，如果指定位不存在则返回0。
U8 BL_QueueU8Read (BL_QueueU8Struct* Obj, S32 Num)
{
	assert(Num < Obj->Count);
	if (Num < Obj->Count)
	{
		U32 t = Obj->_Start + Num;
		U8 c;
		if (t >= Obj->Length)
		{
			t -= Obj->Length;
		}
		c = Obj->_Data[t];
		return c;
	}
	return 0;
}

//*****Queue of F32*****
//计数加一
void _BL_QueueF32StartAdd (BL_QueueF32Struct* Obj)
{
	Obj->_Start++;
	if (Obj->_Start >= Obj->Length)
	{
		Obj->_Start -= Obj->Length;
	}
}

//初始化列队
void BL_QueueF32Init (BL_QueueF32Struct* Obj, S32 Length)
{
	Obj->_Start = 0;
	Obj->Count = 0;
	Obj->Length = Length;
	Obj->_Data = Null;
	Obj->_Data = (F32*)BL_MemAllocEx(Length * sizeof (F32) );
	assert(Obj->_Data);
	BL_MemClear(Obj->_Data, Length * sizeof (F32));
}

//清除列队中的数据
void BL_QueueF32Clear (BL_QueueF32Struct* Obj)
{
	Obj->_Start = 0;
	Obj->Count = 0;
}

//释放列队所占用空间
void BL_QueueF32Free (BL_QueueF32Struct* Obj)
{
	Obj->Length = 0;
	free (Obj->_Data);
}

//返回值=TRUE时说明列队已满新插入的数据已挤占最老的数据的位置
F32 BL_QueueF32Insert (BL_QueueF32Struct* Obj, F32 F)
{
	U32 t = Obj->_Start + Obj->Count;
	if (t >= Obj->Length)
	{
		t -= Obj->Length;
	}
	Obj->_Data[t] = F;
	if (Obj->Count == Obj->Length)
	{
		_BL_QueueF32StartAdd (Obj);
		return True;
	}
	else
	{
		Obj->Count++;
		return False;
	}
}

//取出最早的数据，如果为空则返回0。
F32 BL_QueueF32Fetch (BL_QueueF32Struct* Obj)
{
	assert(Obj->Count > 0);
	if (Obj->Count > 0)
	{
		F32 f = Obj->_Data[Obj->_Start];
		_BL_QueueF32StartAdd (Obj);
		Obj->Count--;
		return f;
	}
	else
	{
		return 0;
	}
}

//按插入顺序读取数据，如果指定位不存在则返回0。
F32 BL_QueueF32Read (BL_QueueF32Struct* Obj, S32 Num)
{
	assert(Num < Obj->Count);
	if (Num < Obj->Count)
	{
		U32 t = Obj->_Start + Num;
		F32 f;
		if (t >= Obj->Length)
		{
			t -= Obj->Length;
		}
		f = Obj->_Data[t];
		return f;
	}
	return 0;
}

//*****Queue of Any*****
//计数加一
void _BL_QueueAnyStartAdd (BL_QueueAnyStruct* Obj)
{
	Obj->_Start++;
	if (Obj->_Start >= Obj->Length)
	{
		Obj->_Start -= Obj->Length;
	}
}

void* _BL_QueueAnyGetData(BL_QueueAnyStruct* Obj, U32 Offset)
{
	assert(Obj->_Data);
	return &Obj->_Data[Offset*Obj->Size];
}

//初始化列队,Size=元素大小(字节)
void BL_QueueAnyInit (BL_QueueAnyStruct* Obj, S32 Length, S32 Size)
{
	Obj->_Start = 0;
	Obj->Count = 0;
	Obj->Length = Length;
	Obj->_Data = Null;
	Obj->Size = Size;

	Obj->_Data = (U8*)BL_MemAllocEx(Length * Size);
	assert(Obj->_Data);
	BL_MemClear(Obj->_Data, Length * Size);
}

//清除列队中的数据
void BL_QueueAnyClear (BL_QueueAnyStruct* Obj)
{
	Obj->_Start = 0;
	Obj->Count = 0;
}

//释放列队所占用空间
void BL_QueueAnyFree (BL_QueueAnyStruct* Obj)
{
	Obj->Length = 0;
	free (Obj->_Data);
}

//返回值=TRUE时说明列队已满新插入的数据已挤占最老的数据的位置
bool BL_QueueAnyInsert (BL_QueueAnyStruct* Obj, void* Data)
{
	U32 t = Obj->_Start + Obj->Count;
	assert(Obj->_Data);
	if (t >= Obj->Length)
	{
		t -= Obj->Length;
	}
	BL_MemCopy(_BL_QueueAnyGetData, Data, Obj->Size);
	if (Obj->Count == Obj->Length)
	{
		_BL_QueueAnyStartAdd (Obj);
		return True;
	}
	else
	{
		Obj->Count++;
		return False;
	}
}

//取出最早的数据，如果为空则返回0。
void* BL_QueueAnyFetch (BL_QueueAnyStruct* Obj)
{
	assert(Obj->Count > 0);
	if (Obj->Count > 0)
	{
		void* p = _BL_QueueAnyGetData(Obj, Obj->_Start);
		_BL_QueueAnyStartAdd (Obj);
		Obj->Count--;
		return p;
	}
	else
	{
		return Null;
	}
}

//按插入顺序读取数据，如果指定位不存在则返回0。
void* BL_QueueAnyRead (BL_QueueAnyStruct* Obj, S32 Num)
{
	assert(Num < Obj->Count);
	if (Num < Obj->Count)
	{
		U32 t = Obj->_Start + Num;
		if (t >= Obj->Length)
		{
			t -= Obj->Length;
		}
		return _BL_QueueAnyGetData(Obj, t);
	}
	return Null;
}

