#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include <exception>

using namespace std;

class EmptyQueueException: public exception {
  public:
    EmptyQueueException(){
      //constructor
    }
};

template <class T>
struct QueueItem
{
  T item;
  QueueItem<T> *prev, *next;
};

template <class T>
class Queue {
  public:
    Queue();

    ~Queue();

    void enqueue (const T & item);
      /* adds the item to the end of the queue.
         The same item may be added many times. */

    void dequeue (); 
      /* removes the front element of the queue. 
         Throws an EmptyQueueException when called on an empty queue.
         EmptyQueueException should inherit from std::exception. */

    const T & peekFront ();
      /* returns the front element of the queue. 
         Throws an EmptyQueueException when called on an empty queue.
         EmptyQueueException should inherit from std::exception. */

    bool isEmpty ();
      /* returns whether the queue is empty. */

    int getSize();

  private:
    QueueItem<T> *head, *tail;
    int size;

};

/******************* Implementation *********************/

template <class T>
Queue<T>::Queue(){
  head = 0;
  tail = 0;
  size = 0;
}

template <class T>
Queue<T>::~Queue(){
  if(head !=0){
    QueueItem<T>* tempHead = head;
    QueueItem<T>* tempNext = head->next;

    while(tempHead != 0){
      tempNext = tempHead->next;
      delete tempHead;
      tempHead = tempNext;
    }
  } 
}
  
template <class T>
void Queue<T>::enqueue (const T & item){

    QueueItem<T>* newItem = new QueueItem<T>;

    if(head == 0){

      head = newItem;
      tail = newItem;
      head->prev = 0;
      head->next = 0;
      tail->prev = 0;
      tail->next = 0;

    } else {

      tail->next = newItem;
      newItem->prev = tail;
      newItem->next = 0;
      tail = newItem;

    }

    tail->item = item;
    size++;

}
/* adds the item to the end of the queue.
The same item may be added many times. */

template <class T>
void Queue<T>::dequeue (){

    if(head != 0){

      QueueItem<T>* toRemove = head;
      head = head->next;

      if(head != 0){
        head->prev = 0;
      }

      //delete toRemove;
      size--;

    } else {

      throw EmptyQueueException();

    }

}
/* removes the front element of the queue. 
Throws an EmptyQueueException when called on an empty queue.
EmptyQueueException should inherit from std::exception. */

template <class T>
const T & Queue<T>::peekFront (){

  if(head != 0){
    return head->item;
  } else {
    throw EmptyQueueException();
  }

}
/* returns the front element of the queue. 
Throws an EmptyQueueException when called on an empty queue.
EmptyQueueException should inherit from std::exception. */

template <class T>
bool Queue<T>::isEmpty (){

  if(head == 0){
    return true;
  } else {
    return false;
  }

}
/* returns whether the queue is empty. */

template <class T>
int Queue<T>::getSize(){
  return size;
}

#endif