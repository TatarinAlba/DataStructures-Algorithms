//
// Created by Albert Avkhadeev on 2/10/2022.
// All time complexities includes the worst case.
// For better performance were used smart pointers
// They can perform auto deletion for exclusion memory leaks
#ifndef HOME_ASSINMENT_DOUBLEHASHSET_H
#define HOME_ASSINMENT_DOUBLEHASHSET_H

#include "ISet.h"
#include <stdexcept>
#include <functional>
#include <cmath>
#include <iostream>
#include <memory>

/**
* DoubleHashSet class
* @tparam T
*/
template<class T>
class DoubleHashSet : public ISet<T> {
    std::shared_ptr<T[]> hashTable{}; // Fundament for future array (pointer)
    std::hash<T> commonHash; // Declaring hash function
    int sizeOf = 0; // Size of the set
    int capacity{}; // Capacity of the set
    int primeNumber{}; // Prime number for hash1 (capacity)
    int primeNumber2{}; // Second prime number for hash2
    T cusZer; // Variable for representing custom zero
    T defunct; // Variable for representing defunct object

    /**
    * Algorithm which evaluate near prime number
    * Time Complexity - O(n)
    * @param x
    * @return
    */
    int nearPrimeNumber(int x) {
        for (int i = x; i > -1; i--) {
            if (isPrime(i)) {
                return i;
            }
        }
        return 0;
    }


    /**
     * Consider, if the value is prime
     * Time Complexity - O(sqrt(n))
     * @param x
     * @return
     */
    bool isPrime(int x) {
        for (int i = 2; i <= ceil(sqrt(x)); i++) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    }

public:

    /**
     * Copy constructor for double hash set
     * Time complexity - O(n)
     * @param obj
     */
    DoubleHashSet(const DoubleHashSet<T>& obj) {
        sizeOf = obj.sizeOf; // Copying size of the object
        capacity = obj.capacity; // Copying capacity of the object
        primeNumber = obj.primeNumber; // Prime number from the second object
        primeNumber2 = obj.primeNumber2; // Second prime number from the second object
        cusZer = obj.cusZer; // Variable for representing custom null from the second object
        defunct = obj.defunct; // Variable for representing defunct object from the second object
        commonHash = obj.commonHash; // Hash function from the second object
        hashTable = std::shared_ptr<T[]>(new T[capacity]); // Creating new array of the T type (by using shared pointer's)
        for (int i = 0; i < capacity; i++) { // By this loop we insert all values from the second object to the first one
            hashTable[i] = obj.hashTable[i];
        }
    }

    /**
     * Default constructor with no parameters
     */
    DoubleHashSet() = default;

    /**
     * Constructor that initialize array after invoking
     * Time Complexity - O(n)
     * @param initialSize
     */
    DoubleHashSet(int initialSize, T defunct, T customNull) {
        primeNumber = nearPrimeNumber(initialSize); // Finding prime number under given
        capacity = primeNumber; // Initialize capacity of the Set
        primeNumber2 = nearPrimeNumber(primeNumber - 1); //Second prime number
        hashTable = std::shared_ptr<T[]>(new T[primeNumber]); // Make all object inside the array by default
        for (int i = 0; i < primeNumber; i++) { //Insert nulls to the array for make it default
            hashTable[i] = customNull;
        }
        this->defunct = defunct; // Initialize custom defunct object
        this->cusZer = customNull; // Initialize custom zero object
    }

    /**
     * Add item in the set
     * Time Complexity - Θ(1)
     * @param item
     */
    void add(T item) override {
        if (capacity == sizeOf) { // If we try to add new value to the set and the set is full, we will throw
            // an exception
            throw std::range_error("The set is full!");
        }
        int j = 0; // j variable for double hashing if collision happens
        int key = abs(commonHash(item)); // Evaluation hashcode (abs because in c++ reminder could be zero)
        int hash1 = key % capacity; // Evaluating first hash function
        int hash2 = primeNumber2 - (key % primeNumber2); // Evaluation second hash function
        int index = (hash1 + j * hash2) % capacity; // Double hashing. In the beginning j = 0
        while (hashTable[index] != cusZer || hashTable[index] == defunct) { // If it will be the case, when such
            // index is not zero => we should increase
            // our variable j and find another cell
            j++; // Increasing j, when collision happened
            index = (hash1 + j * hash2) % capacity; // Trying to apply double hashing with increased j again
        }
        hashTable[index] = item; // If everything is ok we insert value into the hashTable
        sizeOf++; // Increase size after adding
    }

    /**
     * Remove an item from the set
     * Time Complexity - Θ(1)
     * @param item
     */
    void remove(T item) {
        int j = 0; // j variable if collision happens
        int key = abs(commonHash(item)); // Evaluation hashcode (abs because in c++ reminder could be zero)
        int hash1 = key % capacity; // Evaluating first hash function
        int hash2 = primeNumber2 - (key % primeNumber2); // Evaluation second hash function
        int index = (hash1 + j * hash2) % capacity;  // Double hashing. In the beginning j = 0
        while (hashTable[index] != cusZer && j < sizeOf) { // We will search and el
            // until j will equal to the capacity of the set
            // (therefore it will go to the second, lap => here is no such element)
            if (hashTable[index] == item) { // If we found an element, we should remove it by replacing there defunct
                sizeOf--;
                hashTable[index] = defunct; // Insertion defunct object
                return; // Finish function after removing an element
            }
            j++; // Increase
            index = (hash1 + j * hash2) % capacity; // Evaluate new index with changing j
        }
        throw std::range_error("No such element in the set!"); // If there is no such element, throw an exception
    }

    /**
     * Checking, if the set contains such element
     * Time Complexity - O(n)
     * @param item
     * @return
     */
    bool contains(T item) override {
        int j = 0; // j variable if collision happens
        int key = abs(commonHash(item)); // Evaluation hashcode (abs because in c++ reminder could be zero)
        int hash1 = key % capacity; // Evaluating first hash function
        int hash2 = primeNumber2 - (key % primeNumber2); // Evaluation second hash function
        int index = (hash1 + j * hash2) % capacity; // The same idea for removing as in adding (look up)
        while (hashTable[index] != cusZer && j < sizeOf) { // We will search and el
            // until j will equal to the capacity of the set
            // (therefore it will go to the second, lap => here is no such element)
            if (hashTable[index] == item) { // If we found an element, return true
                return true; // Finish run of function
            }
            j++; // If such index was not successful, we should increase our j
            index = (hash1 + j * hash2) % capacity; // Find new index with increased j
        }
        return false; // If j == capacity or hashTable, or we found default zero el, therefore here is no such el.
    }


    /**
     * Returning the size of the set
     * O(1)
     * @return
     */
    int size() override {
        return sizeOf;
    }

    /**
     * Check if the set is empty
     * O(1)
     * @return
     */
    bool isEmpty() override {
        return sizeOf == 0;
    }

    /**
     * Returning all existing elements in the
     * O(n)
     */
    void printAll() {
        for (int i = 0; i < capacity; i++) {
            if (hashTable[i] != defunct && hashTable[i] != cusZer) {
                std::cout << hashTable[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
#endif //HOME_ASSINMENT_DOUBLEHASHSET_H
