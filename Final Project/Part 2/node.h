//
// Created by Eli Laird on 4/5/20.
//

#ifndef FINAL_PROJECT_NODE_H
#define FINAL_PROJECT_NODE_H

template<typename T>

class Node
{
public:
    Node(T);
    Node(const Node<T>& );
    ~Node();
    T& getData(); //returns the data
    void setData(T x  ); //sets the data
    Node<T>* getNext();
    Node<T>* operator=(Node<T>*);


private:

    T data;
    Node<T> * next;
    Node<T> * prev;
    template<typename U>
    friend class LinkedList;


};


template<typename T>
Node<T>* Node<T> :: operator =(Node<T>* n){
    data = n->data;
    next = n->next;
    prev = n->prev;
}


template<typename T>
Node<T> :: Node(T x){
    data = x;
    next = nullptr;
    prev = nullptr;

}

template<typename T>
Node<T> :: Node(const Node<T> & n){
    data = n.data;
    next = n.next;
    prev = n.prev;

}

template<typename T>
Node<T> :: ~Node(){}

template<typename T>
void Node<T> :: setData(T x) {data = x;}

template<typename T>
T& Node<T> :: getData(){return data;}

template<typename T>
Node<T>* Node<T>:: getNext() {return next; }

#endif //FINAL_PROJECT_NODE_H
