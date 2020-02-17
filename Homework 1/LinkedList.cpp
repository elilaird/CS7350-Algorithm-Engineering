//
// Created by Eli Laird on 1/29/20.
//

#include "LinkedList.h"

LinkedList::LinkedList(){
    this->length = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

LinkedList::~LinkedList(){
    if(head == nullptr)
        return;
}

void LinkedList::add(unsigned long int data){
    Node* node = new Node();
    node->data = data;
    if(head == nullptr){
        this->head = node;
        this->tail = node;
        node->next = nullptr;
        this->length++;
    }
    else{
        this->tail->next = node;
        node->next = nullptr;
        this->tail = node;
        this->length++;
    }
}

void LinkedList::print(){
    Node* head = this->head;
    while(head){
        std::cout << head->data << std::endl;
        head = head->next;
    }
}

Node* LinkedList::operator[](unsigned long int i) {
    if(head == nullptr)
        return nullptr;
    Node* temp = head;
    int j = 0;
    while(temp){
        if(j == i)
            return temp;
        temp = temp->next;
        j++;
    }
    return temp;
}

bool LinkedList::isEmpty() {
    if(head == nullptr)
        return true;
    else
        return false;
}

