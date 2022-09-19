//Name: Node.h;
//Author: Elena Ochkina;
//Date: 11/19/2021;
//Description: This Node class provides implementation of a single node for a double linked list;

#ifndef NODE_H
#define NODE_H

template <class T>
class Node{
    private:
        T data;
        Node<T> *next;
        Node<T> *prev;//pointer to the previous node;
    public:
        Node();
        Node(const T&, Node<T>*, Node<T>*);
        void setItem(const T&);
        T getItem()const;
        void setNext(Node<T>*);
        void setPrev(Node<T>*);//method to set the previous node;
        Node<T>* getNext() const;
        Node<T>* getPrev() const;//method to get the previous node;
        
};
template <class T>
Node<T>::Node():next(nullptr){}

template <class T>
Node<T>::Node(const T& _data, Node<T>* _next, Node<T>* _prev):data(_data),next(_next),prev(_prev){}

template <class T>
void Node<T>::setItem(const T& _data){
    data = _data;
}

template <class T>
void Node<T>::setNext(Node<T>* _next){
    next = _next;
}

template <class T>
void Node<T>::setPrev(Node<T>* _prev){
    prev = _prev;
}

template <class T>
T Node<T>::getItem()const{
    return data;
}

template <class T>
Node<T>* Node<T>::getNext() const{
    return next;
}

template <class T>
Node<T>* Node<T>::getPrev() const{
    return prev;
}


#endif
