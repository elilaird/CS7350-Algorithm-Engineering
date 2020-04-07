#include <iostream>
#include "vertex.h"
#include "LinkedList.h"
#include <fstream>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f

//parses input file and constructs adjList and degreesList
void parseInput(std::ifstream& file, LinkedList<vertex*>*& adjList, vector<LinkedList<vertex*>*>*& degreeList);
vector<int> smallestLastOrdering(LinkedList<vertex*>*& adjList, vector<LinkedList<vertex*>*>*& degreeList);

//utility functions
int min_index(vector<int> v){
    int min = INF;
    int index = 0;
    for(int i = 0; i < v.size(); i++) {
        if (v[i] < min && v[i] >= 1) {
            min = v[i];
            index = i;
        }
    }
    return index;
}


using namespace std;

int main(int argc, char** argv) {

    //read in input file
    ifstream file;
    file.open(argv[1], std::ifstream::in);

    //adjacency list
    LinkedList<vertex*>* adjList;

    //list of degrees
    vector<LinkedList<vertex*>*>* degreeList;

    parseInput(file, adjList, degreeList);

    vector<int> ordering = smallestLastOrdering(adjList, degreeList);

    return 0;
}


void parseInput(std::ifstream& file, LinkedList<vertex*>*& adjList, vector<LinkedList<vertex*>*>*& degreeList){

    string line;
    vector<int> input;

    //open file
    if( file.is_open()){
        while(file >> line){

            //add values to input vector
            input.push_back(stoi(line));

            //handle comments and move to next line
            getline(file, line);
        }
    }
    else{
        cout << "Failed to open file" << endl;
    }

    /*~~~~~~~~~~~ BUILD ADJACENCY LIST ~~~~~~~~~~~*/

    int numVertices = input[0];

    adjList = new LinkedList<vertex*>();

    //create vertices
    for(int i = 1; i <= numVertices; i++)
        adjList->insertAtTail(new vertex(i, 0, 0, 0));

    //add edges to vertices
    for(int i = 1; i <= numVertices; i++){
        //if last vertex loop until end of input vector
        if (i == numVertices){
            for(int j = input[i]; j < input.size(); j++){
                //add edge input[j] to vertex i
                adjList->operator[](i-1)->getData()->addEdge(*(adjList) , input[j]);
            }
        }
        else{
            for(int j = input[i]; j < input[i+1]; j++){
                //add edge input[j] to vertex i
                adjList->operator[](i-1)->getData()->addEdge(*(adjList) , input[j]);
            }
        }
    }

    /*~~~~~~~~~~~ BUILD DEGREES LIST ~~~~~~~~~~~*/

    //initialize degrees vector
    degreeList = new vector<LinkedList<vertex*>*>();
    for(int i = 0; i <=numVertices; i++)
        degreeList->push_back(new LinkedList<vertex*>);



    while(adjList->currentNode() != nullptr){

        //insert vertex into corresponding degree index
        int degree = adjList->currentNode()->getData()->currDegree;
        degreeList->at(degree)->insertAtTail(adjList->currentNode()->getData());

        adjList->nextCurrent();
    }



}

vector<int> smallestLastOrdering(LinkedList<vertex*>*& adjList, vector<LinkedList<vertex*>*>*& degreeList){

    vector<int> lengths;
    for(int i = 0; i < degreeList->size();i++)
        lengths.push_back(degreeList->at(i)->getLength());

    //iterate until all vertices are deleted off degreeList
    while(degreeList->size() > 0){

        //loop through degreeList and find smallest populated degree list
        vertex* V = degreeList->at(min_index(lengths))->getHead()->getData();

        //set smallest vertex V to deleted
        V->deleted = -1;

        //for every neighbor U of V -> insert U into degree i-1 list
        V->P.currentToHead();
        while(V->P.currentNode() != nullptr){

            //check if U has been deleted
            if(V->P.currentNode()->getData()->deleted == -1){
                V->P.nextCurrent();
                continue;
            }
            //remove U from degree i list
            vertex* U = degreeList->at(V->P.currentNode()->getData()->currDegree)->remove(V->P.currentNode()->getData())->getData();

            //insert U into degree i-1 list
            degreeList->at(--U->currDegree)->insertAtTail(U);


            V->P.currentNode()->getNext();

        }


    }
}










