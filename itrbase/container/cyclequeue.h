
namespace itr_container
{
template<typename T>
class CycleQueue
{
public:
    CycleQueue(S32 Capacity);
    virtual ~CycleQueue();
    void Insert(T Item);
    BOOL Fetch(T& Item);
    void Clear();
    inline T operator[](S32 Index);
    inline S32 GetLength();
    inline S32 GetCapacity();

private:
    S32 capacity;
    S32 front;
    S32 length;
    T* base;
    inline void AddOne();
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
CycleQueue<T>::~CycleQueue()
{
    delete base;
}

template<typename T>
void CycleQueue<T>::Insert(T Item)
{
    S32 t = (front + length) % capacity;
    base[t] = Item;
    if (length == capacity)
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
    if (length > 0)
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
void CycleQueue<T>::Clear()
{
    length=0;
    front=0;
}

template<typename T>
T CycleQueue<T>::operator[](S32 Index)
{
    assert(Index < length);
    return base[(front + Index) % capacity];
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
    front = front % capacity;
}
}
