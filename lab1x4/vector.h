#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstring>

template<typename T>
class Vector{

  public:

    Vector();
    Vector(const std::size_t);
    Vector(const std::size_t, const T&);

    Vector(const Vector&);

    T& operator[](const std::size_t);
    const T& operator[](const std::size_t) const;

    Vector<T>& operator=(const Vector<T>&);

    ~Vector();

    void reset();
    void reset(const T&);
    void print();
    void push_back(const T&);
    void insert(const std::size_t, const T&);
    void erase(const std::size_t);
    void clear();
    std::size_t size() const;
    void sort(bool);

    void change_size(const std::size_t);

  protected:

    T* elems;
    std::size_t cur_size; //total number of elements
    std::size_t max_size;

  private:

};

template<typename T>
std::ostream& operator<<( std::ostream&, const Vector<T>& ); //TODO: why can't this be friend under class definition (private?)

template<typename T>
Vector<T>::Vector(): cur_size(0), max_size(1){
#ifdef DEBUG
    std::cout<<"Vector()"<<std::endl;
#endif

    elems  = new T[max_size];
    reset();
}

template<typename T>
Vector<T>::Vector(const std::size_t n): cur_size(n), max_size(2*n+1){
#ifdef DEBUG
    std::cout<<"in Vector(std::size_t n)"<<std::endl;
#endif

    elems = new T[max_size];
    reset(); //resets to zero to be sure since uninitialized is undefined can be anything
}

template<typename T>
Vector<T>::Vector(const std::size_t n, const T& init_value):cur_size(n),max_size(2*n+1){
#ifdef DEBUG
    std::cout<<"in Vector(std::size_t n,T init_value)"<<std::endl;
#endif

    elems = new T[max_size];
    reset(init_value);

}

template<typename T>
Vector<T>::Vector(const Vector<T>& v){ //copy constructor
#ifdef DEBUG
    std::cout << "in Vector(const Vector& v):" << std::endl;
#endif

    elems = new T[v.max_size];

    std::copy(v.elems,v.elems+v.cur_size,elems);

    //       for(std::size_t i = 0; i!=v.max_size; ++i){
    //           elems[i] = v.elems[i];
    //           #ifdef DEBUG
    //           std::cout << "in Vector(const Vector& v):  i, elems[i]=" << i << "," << elems[i] << std::endl;
    //           #endif
    //       }

    this->cur_size = v.cur_size;
    this->max_size = v.max_size;

}

template<typename T>
Vector<T>::~Vector(){
#ifdef DEBUG
    std::cout << "~Vector" << std::endl;
#endif
    delete [] elems;
}

template<typename T>
T& Vector<T>::operator[](const std::size_t i) {
    if(i < cur_size){
#ifdef DEBUG
        std::cout << "in operator[]" << std::endl;
#endif
        return elems[i];
    }else{
        //std::string i_str(i);
        //std::string cur_str(cur_size);
        std::cerr << "operator[] says: " << i << " >= current_size:" << cur_size << std::endl;
        throw std::out_of_range("!");
    }
}

template<typename T>
const T& Vector<T>::operator[](const std::size_t i) const {
    if(i < cur_size){
#ifdef DEBUG
        std::cout << "in operator[]" << std::endl;
#endif
        return elems[i];
    }else{
        //std::string i_str(i);
        //std::string cur_str(cur_size);
        std::cerr << "const operator[] const says: " << i << " >= current_size:" << cur_size << std::endl;
        throw std::out_of_range("!");
    }
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v){
    if (this != &v){ // protect against invalid self-assignment
#ifdef DEBUG
        std::cout << "operator=" << std::endl;
#endif

        T* new_elems = new T[v.max_size];

        std::copy(v.elems,v.elems+v.cur_size,new_elems);

        //skapa en ny tom array med rätt storlek (tar kopiera cur_size och max_size från v)
        //
        //    for(std::size_t i = 0; i!=v.cur_size; ++i){
        //        new_elems[i] = v.elems[i];
        //    }

        delete [] elems;

        this->elems = new_elems;
        this->cur_size = v.cur_size;
        this->max_size = v.max_size;
    }
    return *this;
}

    template<typename T>
    void Vector<T>::reset(){ //resets the array by setting all elements to zero (null reference)
        //    #ifdef DEBUG
        //    std::cout<<"in reset()"<<std::endl;
        //    #endif
        //      for(std::size_t i = 0; i!=cur_size; ++i){
        //              elems[i]=0;
        //      }


        reset(T());

    }

template<typename T>
void Vector<T>::reset(const T& init_value){ //resets the array by setting all elements to zero (null reference)
#ifdef DEBUG
    std::cout<<"in reset(T init_elem)"<<std::endl;
#endif
    for(std::size_t i = 0; i!=cur_size; ++i){
        elems[i]=init_value;
    }
}


template<typename T>
void Vector<T>::print(){
    std::cout << "#" << cur_size << "/" << max_size << "[";
    for(std::size_t i = 0; i != cur_size; ++i){
        std::cout << elems[i] << ((i!=(cur_size-1))?',':'\000');
    }
    std::cout <<  "]" << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& t){
    if(cur_size >= max_size){
        change_size(2*max_size+1);
    }
    elems[cur_size] = t;
    ++cur_size;

}

template<typename T>
void Vector<T>::erase(const std::size_t pos){
#ifdef DEBUG
    std::cout << "in erase(std::size_t);pos="<< pos << std::endl;
#endif

    if(pos >= cur_size){
        //std::string i_str(pos);
        //std::string cur_str(cur_size);
        std::cerr << "erase() says: " << pos << " > current_size:" << cur_size << std::endl;
        throw std::out_of_range("!");
    }else/*i<cur_size*/{

        --cur_size;

        if(cur_size<=(max_size-1)/2){ //the new cur_size (cur_size+1)
            max_size = (max_size-1)/2+1;
        }
        T* new_elems = new T[max_size];

        std::size_t i=0;
        for(;i!=pos;++i){
            new_elems[i] = elems[i];
        }

        for(;i!=cur_size;++i){ //only goes up to the new cur_size so it doesnt copy any undefined(out of boundary) element
            new_elems[i] = elems[i+1]; //gauranteed to have new_elems[cur_size+1] since max_size is adjusted according to at least that value
        }

        delete [] elems;
        elems = new_elems;

#ifdef DEBUG
        std::cout << "after erase: ";
        print();
#endif
    }
}

template<typename T>
void Vector<T>::insert(const std::size_t pos, const T& t){

#ifdef DEBUG
    std::cout << "in insert(std::size_t,T);pos="<< pos << ",t=" << t << std::endl;
#endif

    if(pos > cur_size){
        //std::string i_str(pos);
        //std::string cur_str(cur_size);
        std::cerr << "insert() says: " << pos << " > current_size:" << cur_size << std::endl;
        throw std::out_of_range("!");
    }else if(pos==cur_size){ //om man försöker lägga in den till positionen "cur_size" så läggs det till ett nytt element, men om den är större så std::out_of_range
        push_back(t);

    }else/*i<cur_size*/{

        if(cur_size+1>=max_size){ //the new cur_size (cur_size+1)
            max_size = 2*max_size + 1;
        }

        T* new_elems = new T[max_size];

        std::size_t i=0;
        for(;i!=pos;++i){
            new_elems[i] = elems[i];
        }

        new_elems[pos] = t;

        for(;i!=cur_size;++i){
            new_elems[i+1] = elems[i]; //gauranteed to have new_elems[cur_size+1] since max_size is adjusted according to at least that value
        }

        ++cur_size;

        delete [] elems;
        elems = new_elems;

    }
#ifdef DEBUG
    std::cout << "after insert: ";
    print();
#endif
}

template<typename T>
void Vector<T>::clear(){
    delete [] elems;
    cur_size = 0;
    max_size = 1;

    elems = new T[max_size];
}

template<typename T>
std::size_t Vector<T>::size() const{
    return cur_size;
}

template<typename T>
void Vector<T>::sort(bool ascending = true){
    //using default comparator "<" as in lab assignment

    int i;
    int j;
    int flag = 1;    // set flag to 1 to start first pass
    T temp;             // holding variable

    for(i=1;(i<=cur_size)&&flag;i++){
        flag = 0;
        for(j=0;j<(cur_size-1);j++){
            // if descending(not ascending) and next element is larger then switch places, if ascending and next element is smaller then switch places
            if( !ascending && elems[j]<elems[j+1] || ascending && elems[j+1]<elems[j] ){
                temp = elems[j];             // swap elements
                elems[j] = elems[j+1];
                elems[j+1] = temp;
                flag = 1;               // indicates that a swap occurred.
            }
        }
    }
}

template<typename T>
void Vector<T>::change_size(const std::size_t n){
#ifdef DEBUG
    std::cout<<"change_size("<< n << ")"<<std::endl;
#endif

    T* tmp_elems = new T[n];


    // copy old array to tmp-array
    std::size_t i = 0;
    for(; i!=this->cur_size; ++i){
        tmp_elems[i] = this->elems[i];
    }
    //set the rest of the new array, not necessary
    //for(; i!=n; ++i){
    //    tmp_elems[i] = T();
    //}

    delete [] elems;
    this->elems = tmp_elems;
    //set new max_size
    this->max_size = n;

}

template<typename T>
std::ostream& operator<<( std::ostream& out, const Vector<T>& obj){
    for(std::size_t i = 0; i<obj.size(); i++){  //when friend declaration is possible use protected variable cur_size instead of size()
        out << obj[i];
        if(i!=obj.size()-1){
            out << " ";
        }
    }
    return out;
}

#endif
