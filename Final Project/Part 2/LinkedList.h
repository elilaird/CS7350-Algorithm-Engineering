//
// Created by Eli Laird on 1/29/20.
//

#include <cstdlib>
#include <iostream>

#ifndef HOMEWORK_1_LINKEDLIST_H
#define HOMEWORK_1_LINKEDLIST_H


#include "node.h"
#include <iostream>

using namespace std;
template<typename T>

class LinkedList
{
public:
    LinkedList();
    LinkedList( LinkedList & ll);
    ~LinkedList();
    void insertAtHead(T x);
    void insertAtTail(T x);
    void insertBefore(T x ,Node<T>*);
    void clear();
    bool isEmpty();
    Node<T>* remove(Node<T>* x);
    void printList();

    Node<T>* currentNode();
    void currentToHead();
    void nextCurrent();
    int getLength();
    Node<T>* getTail();
    Node<T>* getHead();
    LinkedList<T>& operator=( const LinkedList<T> &);
    Node<T>* operator[](int);
    int contains(T x);

private:
    Node<T>* head; //represents the first node in the list
    Node<T>* tail; // represents the last node
    Node<T>* current; // iterator used to represent the current node
    int index;
    int length;



};

//default constructor
template<typename T>
LinkedList<T> :: LinkedList(){
    head = nullptr;
    tail = nullptr;
    current = head;
    index = 0;
    length = 0;

}

//copy constructor
template<typename T>
LinkedList<T> :: LinkedList( LinkedList & ll){
    length = ll.length;
    Node<T>* temp = ll.head;
    while(temp != nullptr){
        insertAtTail(temp()->getData());
        temp = temp->next;

    }

}

//destructor
template<typename T>
LinkedList<T> :: ~LinkedList(){
    this->clear();

}

//inserts a node at the head of the linkedlist
template<typename T>
void LinkedList<T> :: insertAtHead(T x){
    Node<T>* nde = new Node<T>(x);
    if(isEmpty()){
        head = nde;
        tail =nde;
        nde->next = nullptr;
        nde->prev = nullptr;
    }
    else{
        Node<T>* temp = new Node<T>();
        temp = head;
        head->prev = nde;
        nde->prev = nullptr;
        head = nde;
        nde->next = temp;
        delete temp;
    }
    length++;

}

//inserts a node at the tail of the linkedlist
template<typename T>
void LinkedList<T> :: insertAtTail(T x){
    Node<T>* nde = new Node<T>(x);
    if(isEmpty()){
        head = nde;
        tail = nde;
        nde->next = nullptr;
        nde->prev = nullptr;
    }
    else{
        tail->next = nde;
        nde->next = nullptr;
        nde->prev = tail;
        tail = nde;
    }
    length++;
    currentToHead();
}


template<typename T>
void LinkedList<T> :: insertBefore(T x,Node<T>* nde){
    Node<T>* before = new Node<T>(x);
    Node<T>* temp = before->prev;
    Node<T>* it = head;
    while(it != nullptr){
        if(it== before)
            break;

        it = it->next;
    }
    nde->next = before;
    nde->prev = temp;
    temp->next = nde;
    before->prev = nde;
    delete temp;
    length++;
}

template<typename T>
void LinkedList<T> :: clear(){
    if(head != nullptr){
        while(tail != nullptr){
            Node<T>* temp = tail->prev;
            delete tail;
            tail = temp;
        }
    }
}

template<typename T>
Node<T>* LinkedList<T> :: remove(Node<T>* x ){
    if(this->length == 1){
        this->head = nullptr;
        this->tail = nullptr;
    }
    if(x->prev != nullptr )
        x->prev->next = x->next;
    if(x->next != nullptr)
        x->next->prev = x->prev;

    this->length--;
    this->currentToHead();
    return x;
}

template<typename T>
bool LinkedList<T> :: isEmpty(){
    if(head == nullptr)
        return true;
    else
        return false;
}

template<typename T>
void LinkedList<T> :: printList(){
    Node<T>* temp = head;
    while(temp != nullptr){
        cout << "Data: " << current->getData() << endl;
        temp = temp->next;
    }
}

template<typename T>
int LinkedList<T> :: contains(T x){
    Node<T>* temp = head;
    index = 0;
    while(temp != nullptr){
        if(temp->getData() == x)
            return index;
        temp = temp->next;
        index++;
    }
    return -1;
}

template<typename T>
Node<T>* LinkedList<T> :: operator [](int x){
    Node<T>* temp = head;
    index = 0;
    while(temp != nullptr){
        if(index == x)
            return temp;
        temp = temp->next;
        index++;
    }
    return temp;
}





template<typename T>
LinkedList<T>& LinkedList<T> :: operator=(  const LinkedList<T> &list){
    if(this->length > 0){
        this->clear();
    }

    Node<T>* temp = list.head;
    while(temp != nullptr){
        insertAtTail(temp->getData());
        temp = temp->next;
    }


    return *this;
}





//iterators
template<typename T>
Node<T>*LinkedList<T>::currentNode(){ return current; }


template<typename T>
void LinkedList<T> :: currentToHead(){ current = head; index = 0;}


template<typename T>
void LinkedList<T> :: nextCurrent(){ current = current->next; index++; }


template<typename T>
int LinkedList<T> :: getLength() { return length;}

template<typename T>
Node<T>* LinkedList<T> :: getTail(){ return tail;}

template<typename T>
Node<T>* LinkedList<T> :: getHead(){ return head;}

#endif //HOMEWORK_1_LINKEDLIST_H
