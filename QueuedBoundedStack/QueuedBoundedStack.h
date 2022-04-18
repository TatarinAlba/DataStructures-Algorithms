//
// Created by alber on 2/9/2022->
// All time complexities includes the worst case.
// For better performance were used smart pointers
// They can perform auto deletion for exclusion memory leaks

#ifndef HOME_ASSINMENT_BOUNDEDSTACK_H
#define HOME_ASSINMENT_BOUNDEDSTACK_H

#include "IBoundedStack.h"
#include "../Task1/CircularBoundedQueue.h"

template <class T> class QueuedBoundedStack : public IBoundedStack<T> {
    CircularBoundedQueue<T> firstQueue = CircularBoundedQueue<T>(0); //This two commands creates two queues for
    // implementing stack
    CircularBoundedQueue<T> secondQueue = CircularBoundedQueue<T>(0);

public:
    /**
     * Constructor that take information about size of the stack
     * Time Complexity - O(1)
     * @param initialSize
     */
    QueuedBoundedStack(int initialSize) {
        firstQueue = CircularBoundedQueue<T>(initialSize); // Initializing first queue by default
        secondQueue = CircularBoundedQueue<T>(initialSize); // Initializing second queue by default
    }

    /**
     * Pushing element onto the stack
     * Time Complexity - O(n)
     * @param value
     */
    void push(T value) override {
        if (firstQueue.size() == 0) { // We consider where to insert the input, if the first queue is empty, we should
            // insert it into it and to the second otherwise
            firstQueue.offer(value); // In that example we insert new element to the first queue
            while (!firstQueue.isFull() && !secondQueue.isEmpty()) { // After insertion input element to the
                // first queue, we should insert other elements from the second queue
                // into the first one
                firstQueue.offer(secondQueue.poll());
            }
            if (!secondQueue.isEmpty()) {
                secondQueue.flush();
            }
        } else { // Another brunch of this condition include everything that was in the first branch but instead of
            // using firstQueue as a queue for insertion the current input we use secondQueue.
            secondQueue.offer(value);
            while (!secondQueue.isFull() && !firstQueue.isEmpty()) {
                secondQueue.offer(firstQueue.poll());
            }
            if (!firstQueue . isEmpty()) {
                firstQueue.flush();
            }
        }
    }

    /**
     * Remove an element from the top of the stack
     * Time Complexity - O(1)
     * @return
     */
    T pop() override {
        if (isEmpty()) { // If the stack is empty we should through an exception
            throw std::range_error("The stack is empty!");
        }
        return firstQueue.isEmpty() ? secondQueue.poll() : firstQueue.poll(); // Ternary expression that will remove
        // First element of the first queue if
        // The second one is empty and from the
        // second queue otherwise
    }

    /**
     * Look at the element at the top of the stack
     * Time Complexity - O(1)
     * @return
     */
    T top() override {
        if (isEmpty()) { // If the stack is empty we should through an exception
            throw std::range_error("The stack is empty!");
        }
        return firstQueue.isEmpty() ? secondQueue.peek() : firstQueue.peek(); // Ternary expression that will return
        // First element of the first queue if
        // The second one is empty and from the
        // second queue otherwise
    }

    /**
     * Remove all elements from the stack
     * Time Complexity - O(1)
     */
    void flush() override {
        firstQueue.isEmpty() ? secondQueue.flush() : firstQueue.flush(); // If the first queue is empty we will try to
        // clean the second one but if it is empty
        // too, then program just relocate the second
        // one
    }


    /**
     * Checking if the current stack is empty
     * Time Complexity - O(1)
     * @return
     */
    bool isEmpty() override {
        return firstQueue.isEmpty() && secondQueue.size() == 0; // The stack will be empty iff both queues will be
        // empty
    }

    /**
     * Checking if the current stack is full
     * Time Complexity - O(1)
     * @return
     */
    bool isFull() override {
        return firstQueue.isFull() || secondQueue.isFull(); // The stack will be full iff one of the queues will be full
    }

    /**
     * Returning number of elements in the stack
     * Time Complexity - O(1)
     * @return
     */
    int size() override {
        return firstQueue.isEmpty() ? secondQueue.size() : firstQueue.size(); // If the first queue is empty we will
        // return size of the second one and
        // otherwise
    }

    /**
     * Returning capacity of the stack
     * Time Complexity - O(1)
     * @return
     */
    int capacity() override {
        return firstQueue.capacity(); // Capacity of the both queues will be the same
    }
};

#endif //HOME_ASSINMENT_BOUNDEDSTACK_H
