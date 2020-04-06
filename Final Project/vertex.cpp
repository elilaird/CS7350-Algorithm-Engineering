//
// Created by Eli Laird on 4/5/20.
//

#include "vertex.h"

vertex::vertex(){

}

vertex::vertex(int id, int currDegree, int colorVal, int deleted)
    : id(id), currDegree(currDegree), colorVal(colorVal), deleted(deleted) {}

vertex::vertex(const vertex& v){

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

    return *this;
}

void vertex::addEdge(LinkedList<vertex*>& adjList, int v) {

    //get ptr to vertex node on adjacency list
    vertex* edgePtr = adjList[v-1]->getData();

    //add edge to edge list P
    P.insertAtTail(edgePtr);

    //increment current degree
    currDegree++;

}