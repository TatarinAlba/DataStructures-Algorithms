//
// Created by alber on 2/9/2022.
//

#ifndef HOME_ASSINMENT_IBOUNDEDSTACK_H
#define HOME_ASSINMENT_IBOUNDEDSTACK_H
/**
 * Abstract class IBoundedStack
 * @tparam T
 */
template <class T> class IBoundedStack {
public:
    virtual void push (T value) = 0; // Push an element onto the stack remove the oldest element
    virtual T pop() = 0; // remove an element from the top of the stack
    virtual T top() = 0; // look at the element at the top of the stack (without removing it)
    virtual void flush() = 0; // remove all elements from the stack
    virtual bool isEmpty() = 0; // is the stack empty?
    virtual bool isFull() = 0; // is the stack full?
    virtual int size() = 0; // number of elements
    virtual int capacity() = 0; // maximum capacity
};
#endif //HOME_ASSINMENT_IBOUNDEDSTACK_H
