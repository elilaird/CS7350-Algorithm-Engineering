#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>


bool isUnique(int j, int arr[], int start, int end){
    for(int i = start; i<=end; i++)
        if(arr[i] == j)
            return false;
    return true;
}

long long problem1(long n, long m, int p, std::default_random_engine generator, bool printDist = false){
    using namespace std::chrono;

    int arr[p * n];
    int iter = 0;
    std::uniform_int_distribution<long int> dist(1,m);

    //measure starting time
    high_resolution_clock::time_point start = high_resolution_clock::now();

    //loop p iterations
    for(int i = 0; i < p; i++){
        int uniqueNums = 0;
        int setIter = iter;

        //loop until n unique numbers are generated
        while(uniqueNums < n){
            int x = dist(generator);

            if(isUnique(x, arr, setIter, setIter+n-1)){
                arr[iter++] = x;
                uniqueNums++;
            }
        }
    }

    //measure total time
    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto total_time = duration_cast<nanoseconds>(end - start).count();
    std::cout << "p: " << p << " n: " << n << " m: " << m << " time: " << total_time << std::endl;

    if(printDist){
        //store distribution of numbers to file
        std::ofstream fout("problem1_dist.csv");
        for(int i = 0; i < n*p; i++)
            fout << arr[i] << ",\n";
        fout.close();
    }


    return total_time;

}

std::vector<int>* skewed_distribution(int m, std::default_random_engine generator){
    std::vector<int> *dist = new std::vector<int>();
    int val = 1;
    //create skewed distribution by adding numbers with skewed num of occurences
    for(int i = m; i > 0; i--){
        for(int j = 0; j < i; j++)
            dist->push_back(val);
        val++;
    }

    //shuffle distribution
    std::shuffle(dist->begin(),dist->end(), generator);
    return dist;
}

long long problem2(long n, long m, int p, std::default_random_engine generator, bool printDist = false){
    using namespace std::chrono;

    int arr[p * n];
    int iter = 0;
    std::vector<int>* dist_skewed = skewed_distribution(m, generator); //create skewed distribution
    std::uniform_int_distribution<long int> rand(0,dist_skewed->size()-1); //rand # generator for skewed dist selection

    //measure starting time
    high_resolution_clock::time_point start = high_resolution_clock::now();

    //loop p iterations
    for(int i = 0; i < p; i++){
        int uniqueNums = 0;
        int setIter = iter;

        //loop until n unique numbers are generated
        while(uniqueNums < n){
            int x = dist_skewed->at(rand(generator)); //select a random # from skewed distribution

            if(isUnique(x, arr, setIter, setIter+n-1)){
                arr[iter++] = x;
                uniqueNums++;
            }
        }
    }

    //measure total time
    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto total_time = duration_cast<nanoseconds>(end - start).count();
    std::cout << "p: " << p << " n: " << n << " m: " << m << " time: " << total_time << std::endl;

    if(printDist){
        //store distribution of numbers to file
        std::ofstream fout("problem2_dist.csv");
        for(int i = 0; i < n*p; i++)
            fout << arr[i] << ",\n";
        fout.close();
    }

    return total_time;
}

//Adapted from https://www.geeksforgeeks.org/bubble-sort/
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//Adapted from https://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

long long problem3(long n, std::default_random_engine generator, bool printDist = false){
    using namespace std::chrono;

    int arr[n];
    std::uniform_int_distribution<long int> dist(1,3);

    //measure starting time
    high_resolution_clock::time_point start = high_resolution_clock::now();

    //insert n random numbers between 1 & 3
    for(int i = 0; i < n; i ++)
        arr[i] = dist(generator);

    //sort array using bubble sort
    bubbleSort(arr, n);

    //measure total time
    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto total_time = duration_cast<nanoseconds>(end - start).count();
    std::cout << "n: " << n << " time: " << total_time << std::endl;

    if(printDist){
        //store distribution of numbers to file
        std::ofstream fout("problem3_dist.csv");
        for(int i = 0; i < n; i++)
            fout << arr[i] << ",\n";
        fout.close();
    }


    return total_time;

}

//Adapted from https://www.geeksforgeeks.org/merge-sort/
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

//Adapted from https://www.geeksforgeeks.org/merge-sort/
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

long long problem4(int n, std::default_random_engine generator, bool printDist){
    using namespace std::chrono;

    int arr[n];
    std::uniform_int_distribution<long int> dist(1,3);

    //measure starting time
    high_resolution_clock::time_point start = high_resolution_clock::now();

    //insert n random numbers between 1 & 3
    for(int i = 0; i < n; i ++)
        arr[i] = dist(generator);

    //sort array using bubble sort
    mergeSort(arr, 0, n-1);

    //measure total time
    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto total_time = duration_cast<nanoseconds>(end - start).count();
    std::cout << "n: " << n << " time: " << total_time << std::endl;

    if(printDist){
        //store distribution of numbers to file
        std::ofstream fout("problem3_dist.csv");
        for(int i = 0; i < n; i++)
            fout << arr[i] << ",\n";
        fout.close();
    }


    return total_time;
}

int main() {

    //For each value, total numbers generated is p x n

    int p[] = {100, 1000, 10000};
    int n[] = {5, 10, 15};
    int m[] = {20, 100, 500};

    std::random_device rd;
    std::default_random_engine generator(rd());

    long time_1;
    long time_2;
    long time_3;
    long time_4;

    std::ofstream fout("problem1_data.csv");
    std::ofstream fout2("problem2_data.csv");

    //Run values for problems 1-2
    fout << "p,n,m,t\n";
    fout2 << "p,n,m,t\n";
    bool printDist = false;
    int iter = 0;
    for(int p_i : p){
        for(int n_i : n){
            for(int m_i : m){
                if(m_i == 100 && n_i == 15 && p_i == 10000)
                    printDist = true;
                time_1 = problem1(n_i,m_i,p_i, generator, printDist);
                time_2 = problem2(n_i,m_i,p_i, generator, printDist);

                fout << p_i << "," << n_i << "," << m_i << "," << time_1 << "\n";
                fout2 << p_i << "," << n_i << "," << m_i << "," << time_2 << "\n";

                printDist = false;
            }
        }
    }

    fout.close();
    fout2.close();

    std::ofstream fout3("problem3_data.csv");
    std::ofstream fout4("problem4_data.csv");

    fout3 << "n,t\n";
    fout4 << "n,t\n";

    //run values for problems 3-4
    int n2[] = {10, 100, 1000, 10000, 100000};

    printDist = false;
    for(int i = 0; i < 5; i++){
        if(i == 4)
            printDist = true;

        time_3 = problem3(n2[i], generator, printDist);
        time_4 = problem4(n2[i], generator, printDist);

        fout3 << n2[i] <<  "," << time_3 << "\n";
        fout4 << n2[i] <<  "," << time_4 << "\n";
    }

    fout3.close();
    fout4.close();



    return 0;
}
