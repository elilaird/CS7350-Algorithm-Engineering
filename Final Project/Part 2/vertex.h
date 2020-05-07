//
// Created by Eli Laird on 4/5/20.
//

#ifndef FINAL_PROJECT_VERTEX_H
#define FINAL_PROJECT_VERTEX_H

#include "LinkedList.h"

class vertex {

public:
    int id;
    int currDegree;
    int origDegree;
    int colorVal;
    int deleted;
    int orderColored;

    //edge list
    LinkedList<vertex*> P;

    //list of vertices of same current degree
    LinkedList<vertex*>* sameDegree;

    //pointer for order deleted list
    LinkedList<vertex*>* orderDeleted;



    vertex();
    vertex(const vertex&);
    vertex(int, int, int, int);
    ~vertex();
    vertex& operator=(const vertex&);
    bool operator==(const vertex);

    void addEdge(LinkedList<vertex*>& adjList, int v);
    void setColor(int c, int order); //Added to keep track of coloring order



};


#endif //FINAL_PROJECT_VERTEX_H
