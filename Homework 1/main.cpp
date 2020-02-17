#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include "LinkedList.h"




long long problem1(unsigned long int n, std::default_random_engine generator){

    using namespace std::chrono;

    //initialize random number generator
    std::uniform_int_distribution<unsigned long int> dist(1,n);

    //int array for storage
    unsigned long int arr[n];

    //take the current time
    high_resolution_clock::time_point start = high_resolution_clock::now();

    for(unsigned long int i = 0; i < n; i++)
        arr[i] = dist(generator);

    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto total_time = duration_cast<nanoseconds>(end - start).count();
    std::cout << "n: " << n << " t: " << total_time << std::endl;

    return total_time;

}

long long problem2(unsigned long int n, std::default_random_engine generator){

    using namespace std::chrono;

    //initialize random number generator

    std::uniform_int_distribution<unsigned long int> dist(1,n);

    //int array for storage
    unsigned long int arr[n];

    //take the current time
    high_resolution_clock::time_point start = high_resolution_clock::now();

    int counter = 0; //used to track number of elements in arr
    for(unsigned long int i = 0; i < n; i++){
        int val = dist(generator);

        if(val > arr[counter - 1] || counter == 0){
            arr[counter] = val;
            counter++;
        }
        else{
            /* Adapted from https://www.geeksforgeeks.org/search-insert-and-delete-in-a-sorted-array/ */
            int i;
            for (i = counter - 1; (i >= 0 && arr[i] > val); i--)
                arr[i + 1] = arr[i];

            arr[i + 1] = val;
            counter++;
        }

    }

    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto total_time = duration_cast<nanoseconds>(end - start).count();

    std::cout << "n: " << n << " t: " << total_time << std::endl;

    return total_time;

}

long long problem3(unsigned long int n, std::default_random_engine generator){
    using namespace std::chrono;

    //initialize random number generator
    std::uniform_int_distribution<unsigned long int> dist(1,n);

    //int array for storage
    LinkedList* list = new LinkedList();

    //take the current time
    high_resolution_clock::time_point start = high_resolution_clock::now();

    for(unsigned long int i = 0; i < n; i++){
        list->add(dist(generator));
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();

    auto total_time = duration_cast<nanoseconds>(end - start).count();

    std::cout << "n: " << n << " t: " << total_time << std::endl;


    return total_time;
}

long long problem4(unsigned long int n, std::default_random_engine generator){
    using namespace std::chrono;

    //initialize random number generator

    std::uniform_int_distribution<unsigned long int> dist(1,n);

    //int array for storage
    LinkedList* list = new LinkedList();

    //take the current time
    high_resolution_clock::time_point start = high_resolution_clock::now();

    int counter = 0; //used to track number of elements in arr
    for(unsigned long int i = 0; i < n; i++){

        //if(i % 1000 == 0) std::cout << i <<std::endl;
        int val = dist(generator);


        if(list->isEmpty() || val > list->tail->getData()){
            list->add(val);
            counter++;
        }
        else{ /* Adapted from https://www.geeksforgeeks.org/given-a-linked-list-which-is-sorted-how-will-you-insert-in-sorted-way/ */
            Node* curr = list->head;
            while(curr->next != nullptr && curr->next->getData() < val)
                curr = curr->next;
            Node* valNode = new Node(val);
            valNode->next = curr->next;
            curr->next = valNode->next;
        }
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto total_time = duration_cast<nanoseconds>(end - start).count();
    std::cout << "n: " << n << " t: " << total_time << std::endl;

    return total_time;
}


int main() {

    int n = 6;
    unsigned long long int n_list[] = {10, 100, 1000, 100000, 500000, 1000000};
    long long times_1[6];
    long long times_2[6];
    long long times_3[6];
    long long times_4[6];

    std::random_device rd;
    std::default_random_engine generator(rd());

    //run experiments 1-4
    for(int i = 0; i < n; i++) {
        times_1[i] = problem1(n_list[i], generator);
        times_2[i] = problem2(n_list[i], generator);
        times_3[i] = problem3(n_list[i], generator);
        times_4[i] = problem4(n_list[i], generator);
    }

    std::ofstream fout("problem1_output.csv");
    std::ofstream fout2("problem2_output.csv");
    std::ofstream fout3("problem3_output.csv");
    std::ofstream fout4("problem4_output.csv");


    fout << "n,t\n";
    fout2 << "n,t\n";
    fout3 << "n,t\n";
    fout4 << "n,t\n";
    for(int i = 0; i < n; i++){
        fout << n_list[i] << "," << times_1[i] << "\n";
        fout2 << n_list[i] << "," << times_2[i] << "\n";
        fout3 << n_list[i] << "," << times_3[i] << "\n";
        fout4 << n_list[i] << "," << times_4[i] << "\n";
    }

    fout.close();
    fout2.close();
    fout3.close();
    fout4.close();
    return 0;
}