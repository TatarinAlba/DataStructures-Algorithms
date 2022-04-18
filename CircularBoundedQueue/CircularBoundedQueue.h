//
// Created by Albert Avkhadeev on 2/9/2022.
// All time complexities includes the worst case.
// For better performance were used smart pointers
// They can perform auto deletion for exclusion memory leaks

#ifndef HOME_ASSINMENT_CIRCULARBOUNDEDQUEUE_H
#define HOME_ASSINMENT_CIRCULARBOUNDEDQUEUE_H

#include "ICurcularBoundedQueue.h"
#include <stdexcept>
#include <memory>
//Implementation of the ICircularBoundenQueue class
template <class T> class CircularBoundedQueue : public ICircularBoundedQueue<T> {
    std::shared_ptr<T[]> cBQueue; //We declare pointer that will go through the array
    int lastEl = 0; //Position of the current last element in the array
    int firstEl = 0; //Position of the first element
    int numberOfElements = 0; //Current number of elements in the queue
    int capacityOfQueue; //Size of the queue (no more)

public:

    /**
     * Constructor that initialize array and also initialize capacityOfTheQueue
     * Time Complexity - O(1)
     * @param initialSize
     */
    CircularBoundedQueue(int initialSize) {
        cBQueue = std::shared_ptr<T[]> (new T[initialSize]); //Creating new array of T with current size
        capacityOfQueue = initialSize; // Capacity of the queue will be inserted by user
    }

    /**
     * Insert element to the rear of the queue, otherwise - the oldest element, when queue is full
     * Time Complexity - O(1)
     * @param value
     */
    void offer(T value) override {
        cBQueue[lastEl] = value; // Here we add the new element to the array
        if (lastEl == firstEl && numberOfElements != 0) { // If it will be the case when pointer to the last object
            // of the queue collided with the pointer to the first object, we should move firstEl pointer forward
            ++firstEl %= capacityOfQueue;
        }
        numberOfElements = numberOfElements == capacityOfQueue ? capacityOfQueue : numberOfElements += 1; // Increase
        // number of elements in array while it is not full, otherwise it will hold
        ++lastEl %= capacityOfQueue; // Firstly, we change our pointer from the last number to the new empty field
    };

    /**
     * Remove an element from the front of the queue and return it
     * Time Complexity - O(1)
     * @return
     */
    T poll() override {
        if (numberOfElements == 0) { //If it will be the case, when queue is Empty and user tries to remove first
            // object from the queue, we should return error
            throw std::range_error("The queue is empty!");
        }
        --numberOfElements; // We should decrease number of elements after polling
        T returnEl = cBQueue[firstEl]; //Firstly we should prepare value which will be removed from the queue
        ++firstEl %= capacityOfQueue; //We should change position of the first element after polling
        return returnEl;
    };


    /**
     * Look at the element at the front of the queue
     * Time complexity - O(1)
     * @return
     */
    T peek() override {
        if (numberOfElements == 0) { //If it will be the case, when queue is Empty and user tries to get first
            // object from the queue, we should return error
            throw std::range_error("The queue is empty!");
        }
        return cBQueue[firstEl]; //Otherwise, we give the first element from the queue
    };

    /**
     * Remove all elements from the queue
     * Time Complexity - O(1)
     */
    void flush() override {
        lastEl = 0; // Make pointer to the last element by default
        firstEl = 0; // Make pointer to the first element by default
        numberOfElements = 0; //Make number of elements in the queue by default
        cBQueue = std::shared_ptr<T[]>(new T[capacityOfQueue]); //We should allocate new memory cell for representing
        //array, therefore we use new keyword
    };

    /**
     * Checking is current queue empty
     * Time Complexity - O(1)
     * @return
     */
    bool isEmpty() override {
        return numberOfElements == 0; // If here will be at least one element, therefore the result will be true and
        // false otherwise
    };

    /**
     * Checking is the queue full
     * Time Complexity - O(1)
     * @return
     */
    bool isFull() override {
        return numberOfElements == capacityOfQueue; // This logical expression give true if the number of
        // elements equivalent to the size of the queue and false otherwise
    };

    /**
     * Shows current size of the queue
     * Time Complexity - O(1)
     * @return
     */
    int size() override {
        return numberOfElements;
    }

    /**
     * Shows maximum capacity of the queue
     * Time Complexity - O(1)
     * @return
     */
    int capacity() override{
        return capacityOfQueue;
    }

};
#endif //HOME_ASSINMENT_CIRCULARBOUNDEDQUEUE_H