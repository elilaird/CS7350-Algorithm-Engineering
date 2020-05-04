

#ifndef FINAL_PROJECT_CUSTOM_VEC_H
#define FINAL_PROJECT_CUSTOM_VEC_H

#include <stdexcept>
#include <iostream>

using namespace std;

template<typename T>

class custom_vec
{
public:

    custom_vec(int = 10);
    custom_vec(const custom_vec<T>&);
    ~custom_vec();
    void push_back(T);
    void remove(); //remove last element of the vector
    custom_vec<T>& operator=(const custom_vec<T> &);
    T& operator[](const int);
    T& at(int);
    bool operator==(const custom_vec<T>&);
    int vsize() const;
    void setSize(int);
    //iterators
    void moveToStart();      // Reset position
    void moveToEnd();     // Set at end
    void prev();       // Back up
    void next(); // Next
    int currPos() const;   //return current position
    void moveToPos(int pos); // move current list position to pos
    int end();
    int begin();
    void clear();
    T& getValue() const; // get current element
    bool linearSearch(T);
    void swap(int, int);



private:
    T* data;
    int size; // amount of spaces used
    int capacity; //total number of spaces available
    void resize();
    int curr;
};

template<typename T> custom_vec<T> :: custom_vec(int x){
    size = 0;
    capacity = x;
    data = new T[x];
    curr = 0;
}

template<typename T> custom_vec<T> :: custom_vec(const custom_vec<T>& v){
    size = v.size;
    capacity = v.capacity;
    curr = 0;
    data = new T[v.vsize()];
    for(int i = 0; i < v.size;i++)
        data[i] = v.data[i];
}

template<typename T> custom_vec<T> ::  ~custom_vec(){
    if(data != nullptr)
        delete[] data;
}

template<typename T>
void custom_vec<T> :: push_back(T  p){
    if(size == capacity){
        capacity *= 2;
        this->resize();
    }
    data[size++] = p;

}

template<typename T>
void custom_vec<T> :: remove(){
//    T* temp = new T[capacity];
//    size = size - 1;
//    for(int i = 0; i < size;i++)
//            temp[i] = data[i];
//    delete[] data;
//    data = new T[capacity];
//    for(int j = 0;j < size;j++)
//        data[j] = temp[j];
//    delete[] temp;
    size--;

}

template<typename T>
void custom_vec<T> :: clear(){
    if(data != nullptr){
        delete[] data;
        size = 0;
        capacity = 10;
        data = new T[10];
    }
}




template<typename T>
void custom_vec<T> :: resize(){
    T* temp = new T[capacity * 2];
    for(int i = 0;i < size;i++){
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;

}

template<typename T>
T& custom_vec<T> :: operator[](const int x) {
    if(x > vsize())
        throw std::out_of_range("Index out of range");
    return data[x];
}

template<typename T>
T& custom_vec<T> :: at(int x){
    if(x > vsize())
        throw std::out_of_range("Index out of range");
    return data[x];
}


template<typename T>
custom_vec<T>& custom_vec<T>:: operator= (const custom_vec<T>& v){

    size = v.size;
    capacity = v.capacity;
    for(int i = 0; i < v.size;i++){
        data[i] = v.data[i];
    }


    return *this;

}

template<typename T>
bool custom_vec<T> :: operator==(const custom_vec<T>& v){
    if(this->size != v.size)
        return false;
    for(int i = 0;i < size;i++){
        if(this-> data[i] != v[i])
            return false;
    }
    return true;
}

template<typename T>
void custom_vec<T> :: swap(int i, int j){

    if(i >= this->size || i < 0 || j >= this->size || j <0)
        throw std::out_of_range("Indexes out of range");

    auto temp = data[i];
    data[i] = data[j];
    data[j] = temp;

}

template<typename T>
int custom_vec<T> :: vsize() const{
    return this->size;
}

template<typename T>
void custom_vec<T> :: setSize(int x) { size = x; }

template<typename T>
void custom_vec<T> :: moveToStart() { curr = 0; }        // Reset position

template<typename T>
void custom_vec<T> :: moveToEnd() { curr = size; }     // Set at end

template<typename T>
void custom_vec<T> :: prev() { if (curr != 0) curr--; }       // Back up

template<typename T>
void custom_vec<T> :: next() { if (curr < size) curr++; } // Next

template<typename T>
int custom_vec<T> :: currPos() const { return curr;}

template<typename T>
int custom_vec<T> :: end(){
    moveToEnd();
    return curr;
}

template<typename T>
int custom_vec<T> :: begin(){
    moveToStart();
    return curr;
}

template<typename T>
// Set current list position to "pos"
void custom_vec<T> :: moveToPos(int pos) {
    if((pos<0)&&(pos>size))
        throw std::out_of_range("pos out of range");
    curr = pos;
}

template<typename T>
T& custom_vec<T> :: getValue() const { // Return current element
    if((curr<=0)&&(curr>size))
        throw std::out_of_range("No current element");
    return data[curr];
}





template<typename T>
bool custom_vec<T> :: linearSearch(T key){
    for(int i = 0; i < this->vsize(); i++){
        if(key == (*this)[i])
            return true;
    }
    return false;
}

//template<typename T>
//int custom_vec<T> :: linearSearchPair(T key){
//PairEquals pe;
//    for(int i = 0; i < this->vsize(); i++){

//        if(pe(key,(*this)[i]))
//            return i;

//    }
//    return -1;
//}










#endif //FINAL_PROJECT_CUSTOM_VEC_H
