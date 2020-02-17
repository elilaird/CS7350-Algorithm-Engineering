//
// Created by Eli Laird on 1/29/20.
//

#include <cstdlib>
#include <iostream>

#ifndef HOMEWORK_1_LINKEDLIST_H
#define HOMEWORK_1_LINKEDLIST_H


class Node
{
public:
    Node* next;
    Node(){next = nullptr;}
    Node(unsigned long int n){data = n;}
    unsigned long int data;
    friend class LinkedList;

    unsigned long int getData(){
        return data;
    }

    void setData(unsigned long int n){ data = n;}
};

using namespace std;

class LinkedList
{
public:
    unsigned long int length;
    Node* head;
    Node* tail;

    LinkedList();
    ~LinkedList();
    void add(unsigned long int data);
    void print();
    Node* operator[](unsigned long int);
    bool isEmpty();
};


#endif //HOMEWORK_1_LINKEDLIST_H
