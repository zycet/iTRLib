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
            CycleQueue(S32 Capacity);
            void Insert(T Item);
            BOOL Fetch(T& Item);
            inline T operator[](S32 Index);
            S32 GetLength();
            S32 GetCapacity();

        private:
            S32 capacity;
            S32 front;
            S32 length;
            T *base;
            void AddOne();
    };

    template<typename T>
    CycleQueue<T>::CycleQueue(S32 Capacity)
    {
        base = new T[Capacity];
        capacity = Capacity;
        length = 0;
        front = 0;
    }

    template<typename T>
    S32 CycleQueue<T>::GetLength()
    {
        return length;
    }

    template<typename T>
    S32 CycleQueue<T>::GetCapacity()
    {
        return capacity;
    }

    template<typename T>
    void CycleQueue<T>::AddOne()
    {
        front++;
        front=front%capacity;
    }

    template<typename T>
    void CycleQueue<T>::Insert(T Item)
    {
        S32 t=(front+length)%capacity;
        base[t]=Item;
        if(length==capacity)
        {
            AddOne();
        }
        else
        {
            length++;
        }
    }

    template<typename T>
    BOOL CycleQueue<T>::Fetch(T& Item)
    {
        if (length>0)
        {
            Item = base[front];
            AddOne();
            length--;
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename T>
    inline T CycleQueue<T>::operator[](S32 Index)
    {
        return base[(front + Index) % capacity];
    }
}
