#include <iostream>
#include "vertex.h"
#include "LinkedList.h"
#include <fstream>
#include <string>
#include <vector>

void parseInput(std::ifstream& file, LinkedList<vertex*>*& adjList, vector<LinkedList<vertex*>*>*& degrees);

using namespace std;

int main(int argc, char** argv) {

    //read in input file
    ifstream file;
    file.open(argv[1], std::ifstream::in);

    //adjacency list
    LinkedList<vertex*>* adjList;

    //list of degrees
    vector<LinkedList<vertex*>*>* degrees;

    parseInput(file, adjList, degrees);



    return 0;
}


void parseInput(std::ifstream& file, LinkedList<vertex*>*& adjList, vector<LinkedList<vertex*>*>*& degrees){

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
    degrees = new vector<LinkedList<vertex*>*>();
    for(int i = 0; i <=numVertices; i++)
        degrees->push_back(new LinkedList<vertex*>);



    while(adjList->currentNode() != nullptr){

        //insert vertex into corresponding degree index
        int degree = adjList->currentNode()->getData()->currDegree;
        degrees->at(degree)->insertAtTail(adjList->currentNode()->getData());

        adjList->nextCurrent();
    }



}












