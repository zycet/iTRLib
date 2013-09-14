/*
 C++循环列队
 BUAA 刘淼
 2013-9-8
 */

namespace itr_container
{
    template<typename T>
    class CycleQueue
    {
        public:
            CycleQueue(int init);
            void InsertCycleQueue(T e);
            bool FetchCycleQueue(T& Item);
            inline T operator[](int index);
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
        front = rear = 0;
    }

    template<typename T>
    int CycleQueue<T>::CycleQueueLength()
    {
        return ((rear - front + size + 1) % size);
    }

    template<typename T>
    void CycleQueue<T>::InsertCycleQueue(T e)
    {
        if ((rear + 1) % size == front)
        {
            front = (front + 1) % size;
            base[rear] = e;
            rear = (rear + 1) % size;
        }
        else
        {
            base[rear] = e;
            rear = (rear + 1) % size;
        }
    }

    template<typename T>
    bool CycleQueue<T>::FetchCycleQueue(T& Item)
    {
        if ((front - rear)%size==0)
        {
            return false;
        }
        else
        {
            Item=base[front % size];
            front = (front + 1) % size;
            return true;
        }
    }

    template<typename T>
    inline T CycleQueue<T>::operator[](int index)
    {
        return base[(front + index) % size];
    }
}
