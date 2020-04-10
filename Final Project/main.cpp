#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <random>

#include "vertex.h"
#include "LinkedList.h"
#include "custom_vec.h"



#define INF 0x3f3f3f3f

typedef std::pair<custom_vec<vertex*>, int> order;

//parses input file and constructs adjList and degreesList
void parseInput(std::ifstream& file, LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>*& degreeList);
order smallestLastOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList);
order welshPowellOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList);
order uniformRandomOrdering(LinkedList<vertex*>*& adjList);
order largestLastOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList);
order largestEccentricityOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList);
order distanceFromHighestDegreeVertexOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList);
int color_graph(custom_vec<vertex*>& ordering);

//utility functions
int min_index(custom_vec<LinkedList<vertex*>*>*& v){
    int min = INF;
    int index = 0;
    for(int i = 0; i < v->vsize(); i++) {
        if (v->at(i)->getLength() < min && v->at(i)->getLength() >= 1) {
            min = v->at(i)->getLength();
            index = i;
        }
    }
    return index;
}
int max_index(custom_vec<LinkedList<vertex*>*>*& v){
    int max = 0;
    int index = 0;
    for(int i = 0; i < v->vsize(); i++) {
        if (v->at(i)->getLength() > max && v->at(i)->getLength() >= 1) {
            max = v->at(i)->getLength();
            index = i;
        }
    }
    return index;
}
int calc_average_degree(custom_vec<vertex*>& colored_vertices){
    int total = 0;
    for(int i = 0; i < colored_vertices.vsize(); i++)
        total += colored_vertices.at(i)->origDegree;

    return total / colored_vertices.vsize();
}
int max_del_degree(custom_vec<vertex*>& colored_vertices){
    int max = 0;
    for(int i = 0; i < colored_vertices.vsize(); i++){
        if(colored_vertices.at(i)->currDegree > max)
            max = colored_vertices.at(i)->currDegree;
    }

    return max;
}
bool is_connected(vertex*& v, int key){
    v->P.currentToHead();
    for(auto iter = v->P.currentNode(); iter != nullptr; iter = iter->getNext()){
        if(iter->getData()->id == key)
            return true;
    }

    return false;
}
void print_results(custom_vec<vertex*> ordering, int num_colors){

    for(int i = 0; i < ordering.vsize(); i++){
        std::cout << "\nVertex "            << ordering.at(i)->id << ":"
                  << "\n\t color: "         << ordering.at(i)->colorVal
                  << "\n\t orig degree: "   << ordering.at(i)->origDegree
                  << "\n\t deg delete: "    << ordering.at(i)->currDegree
                  << endl;
    }

    std::cout << "\n Total colors used: "       << num_colors
              << "\n Average Original Degree: " << calc_average_degree(ordering)
              << "\n Max Deleted Degree: "      << max_del_degree(ordering)
              << std::endl;
}
void shuffle(custom_vec<vertex*>& v){
    //initialize random device
    std::random_device rd;
    std::default_random_engine g(rd());

    std::uniform_int_distribution<int> dist(0, v.vsize() -1);
    for(int i = 0; i < 100; i++){

        v.swap(0, dist(g));
    }
}


int main(int argc, char** argv) {

    //read in input file
    ifstream file;
    file.open(argv[1], std::ifstream::in);

    //adjacency list
    LinkedList<vertex*>* adjList;

    //list of degrees
    custom_vec<LinkedList<vertex*>*>* degreeList;

    parseInput(file, adjList, degreeList);

    //order result = welshPowellOrdering(adjList, degreeList);
    //order result = smallestLastOrdering(adjList, degreeList);
    //order result = uniformRandomOrdering(adjList);
    order result = largestLastOrdering(adjList, degreeList);

    print_results(result.first, result.second);


    return 0;
}


void parseInput(std::ifstream& file, LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>*& degreeList){

    string line;
    custom_vec<int> input;

    //open file
    if( file.is_open()){
        while(file >> line){

            //add values to input custom_vec
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
        adjList->insertAtTail(new vertex(i, 0, -1, 0));

    //add edges to vertices
    for(int i = 1; i <= numVertices; i++){
        //if last vertex loop until end of input custom_vec
        if (i == numVertices){
            for(int j = input[i]; j < input.vsize(); j++){
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

    //initialize degrees custom_vec
    degreeList = new custom_vec<LinkedList<vertex*>*>();
    for(int i = 0; i <= numVertices; i++)
        degreeList->push_back(new LinkedList<vertex*>);



    while(adjList->currentNode() != nullptr){

        //insert vertex into corresponding degree index
        int degree = adjList->currentNode()->getData()->currDegree;
        adjList->currentNode()->getData()->origDegree = degree;
        degreeList->at(degree)->insertAtTail(adjList->currentNode()->getData());

        adjList->nextCurrent();
    }



}

int color_graph(custom_vec<vertex*>& ordering){

    //initialize color set
    custom_vec<int> color_set;
    color_set.push_back(1);

    //color first vertex
    ordering.at(ordering.vsize() - 1)->colorVal = 1;

    for(int i = ordering.vsize()-2; i >= 0; i--){

        bool colored = false;

        //try each color in color set
        for(int k = 1; k <= color_set.vsize(); k++){
            bool isNeighboringColor = false;

            //check if color is neighboring color
            while(ordering.at(i)->P.currentNode() != nullptr){
                vertex* neighbor = ordering.at(i)->P.currentNode()->getData();

                if(neighbor->colorVal != -1 && neighbor->colorVal == k){
                    isNeighboringColor = true;
                    ordering.at(i)->P.nextCurrent();
                    break;
                }
                ordering.at(i)->P.nextCurrent();
            }

            //reset iter
            ordering.at(i)->P.currentToHead();

            //if not a neighboring color, color this vertex with k
            if(!isNeighboringColor){
                ordering.at(i)->colorVal = k;
                colored = true;
                break;
            }
        }

        //if all of the colors are colors of neighbors then add new color
        if(!colored){
            color_set.push_back(color_set.vsize() + 1);
            ordering.at(i)->colorVal = color_set.at(color_set.vsize() - 1);
        }


    }

    return color_set.vsize();

}


//~~~~~~~~~~ ORDERING ALGORITHMS ~~~~~~~~~~//
custom_vec<vertex*> smallestLastOrderingUtil(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList){

    custom_vec<vertex*> ordering;
    int deletedCount = 0;

    //iterate until all vertices are deleted off degreeList
    while(deletedCount < adjList->getLength()){

        //loop through degreeList and find smallest populated degree list
        int min = min_index(degreeList);
        vertex* V = degreeList->at(min)->getHead()->getData();

        //set smallest vertex V to deleted
        V->deleted = -1;

        //delete vertex from degreeList
        degreeList->at(min)->remove(degreeList->at(min)->getHead()->getData());
        deletedCount++;

        //add vertex to ordering list
        ordering.push_back(V);

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


            V->P.nextCurrent();

        }

        //reset iter
        V->P.currentToHead();


    }

    //reverse ordering
    custom_vec<vertex*> rev_ordering;
    for(int i = ordering.vsize() - 1; i > -1; i--)
        rev_ordering.push_back(ordering.at(i));

    return rev_ordering;
}

order smallestLastOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList){

    //call smallestLastOrdering
    custom_vec<vertex*> ordering = smallestLastOrderingUtil(adjList, degreeList);

    int num_colors = color_graph(ordering);

    return std::make_pair(ordering, num_colors);
}

order welshPowellOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList){

    //initialize color
    int color = 1, colored = 0;

    //order of coloring
    custom_vec<vertex*> color_order;

    //add vertices to list in descending order
    custom_vec<vertex*> vertices;
    for(int i = degreeList->vsize() - 1; i > -1; i--){

        //check if any vertices with degree i
        if(degreeList->at(i)->getHead() == nullptr)
            continue;

        //add all vertices of degree i to vertices list
        while(degreeList->at(i)->currentNode() != nullptr){
            vertices.push_back(degreeList->at(i)->currentNode()->getData());
            degreeList->at(i)->nextCurrent();
        }
    }


    //color vertices
    for(int i = 0; i < vertices.vsize() && colored < vertices.vsize(); i++) {

        //color uncolored vertex
        if (vertices.at(i)->colorVal == -1) {
            vertices.at(i)->colorVal = color;
            color_order.push_back(vertices.at(i));
            colored++;
        }

        //color all vertices not connected to vertex i
        for(int k = i + 1; k < vertices.vsize(); k++){
            bool connected = is_connected(vertices.at(k), vertices.at(i)->id);

            if(!connected && vertices.at(k)->colorVal == -1){
                vertices.at(k)->colorVal = color;
                color_order.push_back(vertices.at(k));
                colored++;
            }
        }

        //change color
        color++;

    }


    return std::make_pair(color_order, color-1);

}

order uniformRandomOrdering(LinkedList<vertex*>*& adjList) {



    //store vertices in vector for shuffling
    custom_vec<vertex *> vertices;
    for (auto iter = adjList->getHead(); iter != nullptr; iter = iter->getNext()){
        vertices.push_back(iter->getData());
    }

    //randomly shuffle vertices
    shuffle(vertices);

    int num_colors = color_graph(vertices);

    return std::make_pair(vertices, num_colors);

}

custom_vec<vertex*> largestLastOrderingUtil(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList){
    custom_vec<vertex*> ordering;
    int deletedCount = 0;

    //iterate until all vertices are deleted off degreeList
    while(deletedCount < adjList->getLength()){

        //loop through degreeList and find smallest populated degree list
        int max = max_index(degreeList);
        vertex* V = degreeList->at(max)->getHead()->getData();

        //set smallest vertex V to deleted
        V->deleted = -1;

        //delete vertex from degreeList
        degreeList->at(max)->remove(degreeList->at(max)->getHead()->getData());
        deletedCount++;

        //add vertex to ordering list
        ordering.push_back(V);

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


            V->P.nextCurrent();

        }

        //reset iter
        V->P.currentToHead();


    }

//    //reverse ordering
//    custom_vec<vertex*> rev_ordering;
//    for(int i = ordering.vsize() - 1; i > -1; i--)
//        rev_ordering.push_back(ordering.at(i));

    return ordering;
}

order largestLastOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList){
    //call largestLastOrdering
    custom_vec<vertex*> ordering = largestLastOrderingUtil(adjList, degreeList);

    int num_colors = color_graph(ordering);

    return std::make_pair(ordering, num_colors);
}

order largestEccentricityOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList){



}

order distanceFromHighestDegreeVertexOrdering(LinkedList<vertex*>*& adjList, custom_vec<LinkedList<vertex*>*>* degreeList){

}










