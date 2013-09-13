/*
 * CycleQueue.cpp
 *
 *  Created on: 2013-9-5
 *      Author: buaa
 */
/*
    C++循环列队
    BUAA 刘淼
    2013-9-8
*/
#include <iostream>
using namespace std;

template <typename T>
class CycleQueue
{
public:
  CycleQueue(int init);
  bool CycleQueueEmpty() const;
  void CycleQueueTraverse() const;
  int CycleQueueLength() const;

  bool InsertCycleQueue(T e);
  bool DelCycleQueue();

private:
  int size;
  int front;
  int rear;
  T *base;
};

template <typename T>
CycleQueue<T>::CycleQueue(int init)
{
  size = init;
  std::cin >> init;
  base = new T[size];
  if(!base)return(1);
  front = rear = 0;
}

template <typename T>
int CycleQueue<T>::CycleQueueLength() const
{
  return ((rear-front+size)%size);
}

template <typename T>
void CycleQueue<T>::CycleQueueTraverse() const
{
  int length = (rear-front+size)%size;
  cout<<"Frome the start to the end："<<endl;
  while(length--)
  {
    cout<<base[front+length]<<" ";
  }
  cout<<endl;
}
template <typename T>
bool CycleQueue<T>::InsertCycleQueue(T e)
{
  if((rear+1)%size==front)
  {
   cout<<"Full!"<<endl;
    return false;
  }
  else
  {
    base[rear] = e;
    rear = (rear+1)%size;
    return true;
  }
}

template <typename T>
bool CycleQueue<T>::DelCycleQueue()
{
  if(front==rear)
  {
    return false;
  }
  front = (front+1)%size;
  return true;
}

int main()
{
  CycleQueue<int> *cq = new CycleQueue<int>;
  int input;
  cout<<"PLease insert another member："<<endl;
  while(cin>>input)
  {
    cq->InsertCycleQueue(input);
  }

  cout<<"Start length:"<<cq->CycleQueueLength()<<endl;
  cq->CycleQueueTraverse();
  cout<<"Delete a member"<<endl;
  cq->DelCycleQueue();
  cout<<"Now length:"<<cq->CycleQueueLength()<<endl;
  cq->CycleQueueTraverse();
  return 0;

}


