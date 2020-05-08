//
// Created by Eli Laird on 4/5/20.
//

#include "vertex.h"

vertex::vertex(){

}

vertex::vertex(int id, int currDegree, int colorVal, int deleted)
    : id(id), currDegree(currDegree), colorVal(colorVal), deleted(deleted), origDegree(currDegree) {
    orderColored = 0;

}

vertex::vertex(const vertex& v){
    this->id = v.id;
    this->currDegree = v.id;
    this->P = v.P;
    this->deleted = v.deleted;
    this->colorVal = v.colorVal;
    this->sameDegree = v.sameDegree;
    this->orderDeleted = v.orderDeleted;
    this->orderColored = v.orderColored;
    this->origDegree = v.origDegree;
}

vertex::~vertex() {}

vertex& vertex::operator=(const vertex& v) {
    this->id = v.id;
    this->currDegree = v.id;
    this->P = v.P;
    this->deleted = v.deleted;
    this->colorVal = v.colorVal;
    this->sameDegree = v.sameDegree;
    this->orderDeleted = v.orderDeleted;
    this->orderColored = v.orderColored;
    this->origDegree = v.origDegree;
    return *this;
}

bool vertex::operator==(const vertex v) {
    return (this->id == v.id);
}

void vertex::addEdge(LinkedList<vertex*>& adjList, int v) {

    //get ptr to vertex node on adjacency list
    vertex* edgePtr = adjList[v-1]->getData();

    //add edge to edge list P
    P.insertAtTail(edgePtr);

    //increment current degree
    currDegree++;

}

void vertex::setColor(int c, int order) {
    this->colorVal = c;
    this->orderColored = order;
}