//
// Created by alber on 2/10/2022.
//

#ifndef HOME_ASSINMENT_ISET_H
#define HOME_ASSINMENT_ISET_H

/**
* Interface of set with double hashing
* @tparam T
*/
template<class T>
class ISet {
    virtual void add(T item) = 0; // add item in the set
    virtual void remove(T item) = 0; // remove an item from the set
    virtual bool contains(T item) = 0; // check if the item belongs to the set
    virtual int size() = 0; // number of elements in the set
    virtual bool isEmpty() = 0; // check if the set is empty
};

#endif //HOME_ASSINMENT_ISET_H
