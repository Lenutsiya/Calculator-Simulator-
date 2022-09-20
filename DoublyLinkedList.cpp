//Name: DoublyLinkedList.cpp;
//Author: Elena Ochkina;
//Date: 11/19/2021;
//Description: Methods implementation for DoublyLinkedList Class.

#include "Node.h"
#include "DoublyLinkedList.h"
#include <ostream>
#include "NoSuchElementException.h"

using namespace std;

template <class T>
DoublyLinkedList<T>::DoublyLinkedList():first(nullptr), last(nullptr), length(0){}

template <class T>
DoublyLinkedList<T>:: ~DoublyLinkedList() {
    
    clear();
}

template <class T>
DoublyLinkedList<T>:: DoublyLinkedList(const DoublyLinkedList<T> &other) {
    
    this->first = nullptr;
        this ->last = nullptr;
        this->length = 0;

        Node<T> *originalPtr = other.first;//a pointer to a node in the copied list. This pointer is used for iteration;

        if (originalPtr == nullptr) {
            first = nullptr;
            last = nullptr;
        }
        else {
            while (originalPtr != nullptr) {
                insertLast(originalPtr->getItem());
                originalPtr = originalPtr->getNext();
            }
        }
}
    
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>:: operator=(const DoublyLinkedList<T> &other) {
    
    if (this != &other) {
        this ->clear(); //delete the current object
        this->first = nullptr;
        this ->last = nullptr;
        this->length = 0;

        Node<T> *originalPtr = other.first;//a pointer to a node in the copied list. This pointer is used for iteration;

        if (originalPtr == nullptr) {
            first = nullptr;
            last = nullptr;
        }
        else {
            while (originalPtr != nullptr) {
                insertLast(originalPtr->getItem());
                originalPtr = originalPtr->getNext();
            }
        }
    }
    return *this;

} 

template <class T>
void DoublyLinkedList<T>:: init() {
    this->first = nullptr;
    this->last = nullptr;
    this->length = 0;
} 
template <class T>
bool DoublyLinkedList<T>:: isEmpty() {
    return this->first==nullptr;
}

template <class T>
int DoublyLinkedList<T>::getLength(){
    return this->length;
} 

template <class T>
void DoublyLinkedList<T>::insertFirst(const T& data) {
    Node <T>* tempPtr = new Node<T>(data, nullptr, nullptr);
    
    if (this->first == nullptr) {
        this->first = tempPtr;
        this->last = tempPtr;
    }
    else {
        tempPtr->setNext(this->first);
        this->first->setPrev(tempPtr);
        this->first = tempPtr;        
    }
    this->length++;
}



template <class T>
void DoublyLinkedList<T>:: insertLast(const T& data) {
    Node <T>* tempPtr = new Node<T>(data, nullptr, nullptr);
    if (this->first == nullptr) {
        this->first = tempPtr;
        this->last = tempPtr;
        
    }
    else {
        this->last->setNext(tempPtr);
        tempPtr->setPrev(this->last);
        this->last = tempPtr ;
    }  
    this->length++;
}

template <class T>
void DoublyLinkedList<T>::deleteFirst(){
    Node<T> *nodeToDelete = this->first;
    this->first = this->first->getNext();
    delete nodeToDelete;
    nodeToDelete=nullptr;
    this->length--;
     
}

template <class T>
void DoublyLinkedList<T>::deleteLast(){
    Node<T> *nodeToDelete = this->last;
    this->last = this->last->getPrev();
    this->last->setNext(nullptr);
    delete nodeToDelete;
    nodeToDelete=nullptr;
    this->length--;
     
}

template <class T>
void DoublyLinkedList<T>:: clear() {
    while (this->first != nullptr) {
        deleteFirst();
    }
}

template <class T>    
void  DoublyLinkedList<T>:: setIteratorFirst() {
    this->iterator = this->first;
}

template <class T>    
void  DoublyLinkedList<T>:: setIteratorLast() {
    this->iterator = this->last;
}

template <class T>    
bool  DoublyLinkedList<T>:: hasNext() {
    return this->iterator->getNext() != nullptr;
}

template <class T>    
bool  DoublyLinkedList<T>:: hasPrev() {
    return this->iterator->getPrev() != nullptr;
}

template <class T>    
void  DoublyLinkedList<T>:: next() {
    if (this->iterator == nullptr) {
        throw NoSuchElementException ("there is no data");
    }
    else {
        this->iterator = this->iterator->getNext();
    }
     
}
template <class T>    
void DoublyLinkedList<T>:: prev() {    
    if (this->iterator == nullptr) {
        throw NoSuchElementException ("there is no data");
    }
    else {
        this->iterator = this->iterator->getPrev();
    }
}

template <class T>    
bool  DoublyLinkedList<T>:: isIteratorNULL() {
   if (isEmpty()) {
       throw NoSuchElementException ("there is no data");//if the list is Empty() throw exception No element exception
   }
   return this->iterator == nullptr;
}

template <class T>    
T  DoublyLinkedList<T>:: getData() {
    if (isEmpty()) {
       throw NoSuchElementException ("there is no data");//if the list is Empty() throw exception No element exception
   }
    return this->iterator->getItem();
}



    








