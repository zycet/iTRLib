#include <iostream>
#include <stdio.h>
#include "itrsystem.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    itr_system::AsyncBuffer<char*> buffer;
    char *a=new char[15];
    char *b=new char[15];
    buffer.Init(2);
    buffer.AddBufferToList(a);
    buffer.AddBufferToList(b);
    delete[] a;
    delete[] b;
    return 0;
}
