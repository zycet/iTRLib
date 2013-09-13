/*
 C++循环列队
 BUAA 刘淼
 2013-9-8
 */
#include <iostream>
using namespace std;

template<typename T>
class CycleQueue
{
    public:
        CycleQueue(int init);
        bool CycleQueueEmpty() const;
        void CycleQueueTraverse() const;

        bool InsertCycleQueue(T e);
        bool DelCycleQueue();
        int CycleQueueLength();

    private:
        int size;
        int front;
        int rear;
        T *base;
};

template<typename T>
CycleQueue<T>::CycleQueue(int init)
{
    size = init;
    base = new T[size];
    if (!base)
        return (1);
    front = rear = 0;
}

template<typename T>
int CycleQueue<T>::CycleQueueLength()
{
    return ((rear - front + size) % size);
}

template<typename T>
bool CycleQueue<T>::InsertCycleQueue(T e)
{
    if ((rear + 1) % size == front)
    {
        return false;
    }
    else
    {
        base[rear] = e;
        rear = (rear + 1) % size;
        return true;
    }
}

template<typename T>
bool CycleQueue<T>::DelCycleQueue()
{
    if (front == rear)
    {
        return false;
    }
    front = (front + 1) % size;
    return true;
}

