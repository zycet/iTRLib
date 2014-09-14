#ifndef ASYNCBUFFER_INCLUDED
#define ASYNCBUFFER_INCLUDED
#include "itrbase.h"
#include <vector>
#include <pthread.h>

using itr_container::CycleQueue;
using std::vector;

namespace itr_system
{
template<class T>
class AsyncBuffer
{
private:

    CycleQueue<T> BufferToRead;
    CycleQueue<T> BufferToWrite;

    pthread_mutex_t mutexRead;
    pthread_mutex_t mutexWrite;

public:

    vector<T> BufferList;

    AsyncBuffer()
    {
        pthread_mutex_init(&mutexRead,NULL);
        pthread_mutex_init(&mutexWrite,NULL);
    }
    void Init(S32 Capacity)
    {
        BufferToRead.Init(Capacity);
        BufferToWrite.Init(Capacity);
    }
    void AddBufferToList(T obj)
    {
        BufferList.push_back(obj);
        SetBufferToWrite(obj);
    }

    void SetBufferToWrite(T buffer)
    {
        pthread_mutex_lock(&mutexWrite);
        BufferToWrite.Insert(buffer);
        pthread_mutex_unlock(&mutexWrite);
    }

    T GetBufferToWrite()
    {
        pthread_mutex_lock(&mutexWrite);
        T obj=NULL;
        BufferToWrite.Fetch(obj);
        pthread_mutex_unlock(&mutexWrite);
        return obj;
    }
    T GetBufferToRead()
    {
        pthread_mutex_lock(&mutexRead);
        T obj=NULL;
        BufferToRead.Fetch(obj);
        pthread_mutex_unlock(&mutexRead);
        return obj;
    }
    void SetBufferToRead(T buffer)
    {
        pthread_mutex_lock(&mutexRead);
        BufferToRead.Insert(buffer);
        pthread_mutex_unlock(&mutexRead);
    }
};

}
#endif // ASYNCBUFFER_INCLUDED
