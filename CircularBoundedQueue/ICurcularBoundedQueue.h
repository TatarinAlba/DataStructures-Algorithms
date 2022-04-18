//
// Created by Albert Avkhadeev on 2/9/2022.
//

#ifndef HOME_ASSINMENT_ICURCULARBOUNDEDQUEUE_H
#define HOME_ASSINMENT_ICURCULARBOUNDEDQUEUE_H
//Making interface for Circular Bounded Queue

template <class T> class ICircularBoundedQueue {
public: // Members function will be pure virtual for the future implementation
    virtual void offer(T value) = 0;  // Insert element to the rear of the queue, otherwise - the oldest element,
    // when queue is full
    virtual T poll() = 0; // remove an element from the front of the queue
    virtual T peek() = 0; // look at the element at the front of the queue
    virtual void flush() = 0; // remove all elements from the queue
    virtual bool isEmpty() = 0; // Checking is the queue empty
    virtual bool isFull() = 0;  // Checking is the queue full
    virtual int size () = 0; // maximum capacity of the queue
    virtual int capacity() = 0; // maximum capacity of the queue

};

#endif //HOME_ASSINMENT_ICURCULARBOUNDEDQUEUE_H
