#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <limits>
#include <stdio.h>
#include <iterator>

namespace constant{
    const unsigned int  BYTE_SIZE = 8;
    const unsigned int BOOL_PER_INT = BYTE_SIZE*sizeof(unsigned int);
}

//l�nknings fel ngnstans
namespace helper { //TODO should be moved to helper.cpp and helper.cpp should be copied into this folder

    /*
     * inline itoa2(char[],const &int)
     *
     * converts an integer to its binary form in a string(char *) used for ordinary integers
     *
     * @param buff is a char array of size const::BOOL_PER_INT+1
     * @param value is the value that should be printed to buff
     */
    void inline itoa2(char * buff,const unsigned int value){
        for(std::size_t j = 0;j!=constant::BOOL_PER_INT; j++){
            buff[j] = ( (value&(1<<(constant::BOOL_PER_INT-j-1))) !=0 )? '1':'0';
        }
        buff[constant::BOOL_PER_INT] = '\000';
    };

    /*
     * inline itoa2rev(char[],const &int)
     *
     * converts an integer to its binary form in a string(char *) used for Vector<bool>.print() in revers order
     *
     * @param buff is a char array of size const::BOOL_PER_INT+1
     * @param value is the value that should be printed to buff
     */
    void inline itoa2rev(char * buff,const unsigned int value){
        for(std::size_t j = 0;j!=constant::BOOL_PER_INT; j++){
            buff[j] = ( (value&(1<<j)) !=0 )? '1':'0';
        }
        buff[constant::BOOL_PER_INT] = '\000';
    };

    /*
     * reverseBits - reverse the bits of x
     *   Example: reverseBits(0x01020304) = 0x20a04080
     *   Legal ops: ! ~ & ^ | + << >>
     *   Max ops: 90
     *   Best ops: 34
     *   Rating: 4
     */
    unsigned int inline reverseBits(unsigned int x){
        //funktionen fungerar enligt f�ljande princip, d�
        //den byter plats p� mindre och mindre stycken bitar
        //1234 5678
        //5678 1234
        //7856 3412
        //8765 4321

        //skapa masker
        int m16= 0xff<< 8|0xff;                  //0x0000ffff
        int m8 = 0xff<<16|0xff;                  //0x00ff00ff
        int m4 = 0x0f<<24|0x0f<<16|0x0f<<8|0x0f; //0x0f0f0f0f
        int m2 = 0x33<<24|0x33<<16|0x33<<8|0x33; //001100110...
        int m1 = 0x55<<24|0x55<<16|0x55<<8|0x55; //010101010...

        /* smartare masker, f�r utr�knade, man har inte begr�nsingen //TODO use these, uses only 30operations
           int m16 = 0x0000ffff
           int m8  = 0x00ff00ff
           int m4  = 0x0f0f0f0f
           int m2  = 0x33333333
           int m1  = 0x55555555
        */

        //byt stegvis plats p� samlingar av bitar
        x = ((x>>16)&m16)|((x&m16)<<16);
        x = ((x>>8 )&m8 )|((x&m8 )<<8 );
        x = ((x>>4 )&m4 )|((x&m4 )<<4 );
        x = ((x>>2 )&m2 )|((x&m2 )<<2 );
        x = ((x>>1 )&m1 )|((x&m1 )<<1 );

        return x;
    };

};

template<typename T>
class Vector{
  public:
    Vector();
    Vector(const std::size_t);
    Vector(const std::size_t, const T&);
    Vector(const Vector&);
    ~Vector();
    T& operator[](const std::size_t);
    const T& operator[](const std::size_t) const;
    Vector<T>& operator=(const Vector<T>&);

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
    reset(init_value); //resets to zero to be sure since uninitialized is undefined can be anything
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

        //skapa en ny tom array med r�tt storlek (tar kopiera cur_size och max_size fr�n v)
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
    }else if(pos == cur_size){ //om man f�rs�ker l�gga in den till positionen "cur_size" s� l�ggs det till ett nytt element, men om den �r st�rre s� std::out_of_range
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







//---------- template specialization for Vector<bool> ----------


template<>
class Vector<bool>{
  private:
  protected:
    std::size_t inline numElems() const{ //numElems() fast since constant::BOOL_PER_INT is a 2^n it will use shift
        return cur_size/constant::BOOL_PER_INT+1;
    };
    std::size_t inline maxNumElems() const{
        return max_size/constant::BOOL_PER_INT+1;
    };
    void check_OOR(int absIndex) const{ //TODO use this in iterator
        if(absIndex >= size() || absIndex < 0){
            throw std::out_of_range("Index out of range!");
        }
    };

    std::size_t cur_size; //total number of elements
    std::size_t max_size;
    unsigned int* elems; //instead of bool* elems


  public:
    typedef const bool const_reference;

    class bool_proxy{
      public:
        //TODO should there be a const version to handle the "const operator[]() const" ?
        bool_proxy(){};
        bool_proxy(unsigned int* dat,unsigned int internal_pos){
            data = dat;
            mask = make_mask(internal_pos);
        };
        bool_proxy(const Vector<bool>* boolvec, int absIndex){
            data = &(boolvec->elems[absIndex / constant::BOOL_PER_INT]);
            mask = make_mask(absIndex % constant::BOOL_PER_INT);
        };
        ~bool_proxy(){};

        bool_proxy& operator=(const bool value){ //assign value to the bit that this proxy represent
            write_bit(value);
            return *this;
        };
        bool operator<(const bool_proxy& rhs){ //TODO is this needed for std::sort?
            return (int(bool(*this)) > int(bool(rhs)));
        }

        operator bool() const{
            return read_bit();
        };

      private:
        unsigned int* data; // a pointer to where the data for this boolean is located
        unsigned int mask; //pos within this (one) int [0,32]

        /*
         *  make_mask creates a one at pos and rest zeros ex: pos=4 produces 0x1000
         *  can also be used to calculate 2^pos
         */
        unsigned int inline make_mask(unsigned int pos) const{
            return 1<<(constant::BOOL_PER_INT-pos-1); //note that the order is reversed
        };

        /*
         * bool_proxy::write_bit(const bool value):
         *
         * Writes the value to the bit (specified by mask) that this proxy represents
         */
        void inline write_bit(const bool value){
            if(value){
                *data |= mask;
            }else{
                *data &= ~mask;
            }
        };
        bool inline read_bit() const{
            return ((*data&mask)!=0);
        };
    };//end of class bool_proxy



    class const_iterator{
      protected:
        const Vector<bool>* iterObj;
        int absIndex;
      public:
        //iterator_traits; this 5 shall exist for it to be an valid iterator, and they are used by the algoritms to determine the charecteristics of the iterators passed to them
        typedef std::random_access_iterator_tag iterator_category; 
	//        typedef const bool value_type;
        typedef std::ptrdiff_t difference_type;
        typedef const bool* pointer;
        typedef const bool reference;

        const_iterator(){
            iterObj = NULL;
            absIndex = 0;
        };
        const_iterator(const Vector<bool>* iterObj, int absIndex){
            this->iterObj = iterObj;
            this->absIndex = absIndex;
        };
        const_iterator(const const_iterator& copy){
            iterObj = copy.iterObj;
            absIndex = copy.absIndex;
        };

        const_iterator& operator=(const const_iterator& iter){
            if(this != &iter){
                iterObj = iter.iterObj;
                absIndex = iter.absIndex;
            }
            return *this;
        };
        //in-/decrement operators
        const_iterator& operator++(){
            return (*this) += 1;
        };
        const_iterator operator++(int){
            return const_iterator(iterObj, absIndex++);
        };
        const_iterator& operator--(){
            return (*this) += -1;
        };
        const_iterator operator--(int){
            return const_iterator(iterObj, absIndex--);
        };
        //arithmetic operators
        const_iterator operator+(int pos) const{
            return const_iterator(iterObj, absIndex + pos);
        };
        const_iterator operator-(int pos) const{
            return (*this) + -pos;
        };
        const_iterator& operator+=(int pos){
            absIndex += pos;
            return *this;
        };
        const_iterator& operator-=(int pos){
            return (*this) += -pos;
        };
        //difference operator
        difference_type operator-(const const_iterator& iter) const{
            return this->absIndex - iter.absIndex;
        };
        //comparison operators
        bool operator==(const const_iterator& iter) const{
            if(this->iterObj == iter.iterObj && this->absIndex == iter.absIndex){
                return true;
            }else{
                return false;
            }
        };
        value_type operator!=(const const_iterator& iter) const{
            return !(*this == iter);
        };
        bool operator<(const const_iterator& iter) const{
            if(this->iterObj == iter.iterObj && this->absIndex < iter.absIndex){
                return true;
            }else{
                return false;
            }
        };
        bool operator>(const const_iterator& iter) const{
            if(this->iterObj == iter.iterObj && this->absIndex > iter.absIndex){
                return true;
            }else{
                return false;
            }
        };
        bool operator<=(const const_iterator& iter) const{
            if(*this < iter || *this == iter){
                return true;
            }else{
                return false;
            }
        };
        bool operator>=(const const_iterator& iter) const{
            if(*this > iter || *this == iter){
                return true;
            }else{
                return false;
            }
        };
        //reference operators
        reference operator*() const{
            return (*this)[absIndex];
        };
        reference operator[](int pos) const{
            return (*iterObj)[pos];
        };
    }; //end of class const_iterator

    class iterator : public const_iterator{
      public:
        //re-typedef those that differs from const_iterator
        typedef bool value_type;
        typedef bool* pointer;
        typedef bool_proxy reference;

        iterator() : const_iterator(){};
        iterator(const Vector<bool>* iterObj, int absIndex) : const_iterator(iterObj, absIndex){};
        iterator(const iterator& copy) : const_iterator(copy){};

        iterator& operator=(const iterator& iter){
            if(this != &iter){
                iterObj = iter.iterObj;
                absIndex = iter.absIndex;
            }
            return *this;
        };
        //increment operators
        iterator& operator++(){
            return (*this) += 1;
        };
        iterator operator++(int){
            return iterator(iterObj, absIndex++);
        };
        iterator& operator--(){
            return (*this) += -1;
        };
        iterator operator--(int){
            return iterator(iterObj, absIndex--);
        };
        //arithmetic operators
        iterator operator+(int pos) const{
            return iterator(iterObj, absIndex + pos);
        };
        iterator operator-(int pos) const{
            return (*this) + -pos;
        };
        iterator& operator+=(int pos){
            absIndex += pos;
            return *this;
        };
        iterator& operator-=(int pos){
            return (*this) += -pos;
        };
        //difference operator
        difference_type operator-(const iterator& iter) const{
            return this->absIndex - iter.absIndex;
        };
        //comparison operators will be inherited

        reference operator*() const{ //bool_proxy so value can be changed when dereferenced
            return (*this)[absIndex]; //using operator[] below
        };
        reference operator[](int pos) const{ //using Vector<bool>::operator[]
            return (*iterObj)[pos];
        };
//      reference operator->(){

// ostream& operator ostream(){ ???????????

    }; //end of class iterator




  Vector(): cur_size(0), max_size(constant::BOOL_PER_INT){
#ifdef DEBUG
        std::cout<<"Vector<bool>()"<<std::endl;
#endif
        elems  = new unsigned int[maxNumElems()];
        reset();
    };

    //TODO testa funktionaliteten
    //TODO kolla upp minneshanteringen f�r de h�r, ska man skapa en maxNumElems() eller ?
    explicit Vector(const std::size_t i): cur_size(i), max_size(2*i){
        elems  = new unsigned int[maxNumElems()];
        reset();
    };
    explicit Vector(const std::size_t i, const bool& value): cur_size(i), max_size(2*i){
        elems  = new unsigned int[maxNumElems()];
        reset(value);
    };

    Vector(const Vector& v){
#ifdef DEBUG
        std::cout << "in Vector<bool>(const Vector& v):" << std::endl;
#endif
        elems = new unsigned int[v.maxNumElems()];
        std::copy(v.elems,v.elems+ v.numElems(),elems); //only copy the elems that has a non-undefined value

        //       for(std::size_t i = 0; i!=v.max_size; ++i){
        //           elems[i] = v.elems[i];
        //           #ifdef DEBUG
        //           std::cout << "in Vector(const Vector& v):  i, elems[i]=" << i << "," << elems[i] << std::endl;
        //           #endif
        //       }

        this->cur_size = v.cur_size;
        this->max_size = v.max_size;
    };

    ~Vector(){
#ifdef DEBUG
        std::cout<<"in ~Vector<bool>()"<<std::endl;
#endif
        delete [] elems;
    };

    Vector<bool>& operator=(const Vector<bool>& v){
        if (this != &v){ // protect against invalid self-assignment
#ifdef DEBUG
            // std::cout << "<bool>operator=" << std::endl;
#endif
            unsigned int* new_elems = new unsigned int[v.numElems()];
            std::copy(v.elems,v.elems+v.numElems(),new_elems);

            //skapa en ny tom array med r�tt storlek (tar kopiera cur_size och max_size fr�n v)
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
    };

    Vector<bool>& operator=(const unsigned int i){
#ifdef DEBUG
        //           std::cout << "<bool>operator=(unsigned int)" << std::endl;
#endif
        delete[] elems; //delete old memory

        //set the new size/maxsize
        this->cur_size = constant::BOOL_PER_INT;
        this->max_size = 2*constant::BOOL_PER_INT; //sets the max size and current size to the max integer so that it has 32bits (as does i)

        unsigned int* new_elems = new unsigned int[maxNumElems()]; //allocate needed memory
        new_elems[0] = helper::reverseBits(i);
        this->elems = new_elems;
        return *this;
    };

    std::size_t size() const{
        return cur_size;
    };

    /*
     *  make_bool_proxy(const size_t i)
     *
     *  a factory for making bool_proxys
     */
    bool_proxy inline make_bool_proxy(const std::size_t i){
        return bool_proxy(
            &(this->elems[i/constant::BOOL_PER_INT]),
            i%constant::BOOL_PER_INT
            );
    };
    const bool_proxy inline make_bool_proxy(const std::size_t i) const{
        return bool_proxy(
            &(this->elems[i/constant::BOOL_PER_INT]),
            i%constant::BOOL_PER_INT
            );
    };
    bool_proxy operator[](const std::size_t i){ //overloading Vector<bool>::operator[], this is where objects of class bool_proxy are created
        if(i < cur_size){
#ifdef DEBUG
            std::cout << "in <bool>operator[]" << std::endl;
#endif
            return make_bool_proxy(i);
        }else{
            //std::string i_str(i);
            //std::string cur_str(cur_size);
            std::cerr << "<bool>operator[] says: " << i << " >= current_size:" << cur_size << std::endl;
            throw std::out_of_range("!");
        }
    };
    const bool_proxy operator[](const std::size_t i) const{
        if(i < cur_size){
#ifdef DEBUG
            std::cout << "in <bool>operator[]" << std::endl;
#endif
            return make_bool_proxy(i);
        }else{
            //std::string i_str(i);
            //std::string cur_str(cur_size);
            std::cerr << "<bool>operator[] says: " << i << " >= current_size:" << cur_size << std::endl;
            throw std::out_of_range("!");
        }
    };


    //-----------------[for lab1x6]-----------------------

    //Vector<bool>::

    const_iterator begin() const{
        return const_iterator(this, 0);
    };
    const_iterator end() const{
        return const_iterator(this, size()); //end() points to the position after last bit
    };
    iterator begin(){
        return iterator(this, 0);
    };
    iterator end(){
        return iterator(this, size());
//        return iterator(&elems[numElems()-1], cur_size - (numElems()-1)*constant::BOOL_PER_INT); //SIMON why do I need numElems()-1? end should be one past last element??
    };




    //-----------------[for lab1x7]-----------------------


    //friend Vector<bool> operator&(const Vector<bool>& v); //be friend with yourself
    Vector<bool> operator&(const Vector<bool>& v) const{
        if(v.size() != this->size()){ //use max(this->size,v.size()) instead??
            throw std::domain_error("vectors must have the same length to use bitwise operators");
        }

        Vector<bool> tmp(this->size());

        std::size_t uint_ops = this->numElems();
        for(std::size_t t=0;t<uint_ops;++t){
            tmp.elems[t] = this->elems[t] & v.elems[t];
        }

        return tmp;
    };

    //friend Vector<bool> operator^(const Vector<bool>& v); //be friend with yourself
    Vector<bool> operator^(const Vector<bool>& v) const{
        if(v.size() != this->size()){ //use max(this->size,v.size()) instead??
            throw std::domain_error("vectors must have the same length to use bitwise operators");
        }

        Vector<bool> tmp(this->size());

        std::size_t uint_ops = this->numElems();
        for(std::size_t t=0;t<uint_ops;++t){
            tmp.elems[t] = this->elems[t] ^ v.elems[t];
        }

        return tmp;
    };

    //friend Vector<bool> operator|(const Vector<bool>& v); //be friend with yourself
    Vector<bool> operator|(const Vector<bool>& v) const{
        if(v.size() != this->size()){ //use max(this->size,v.size()) instead??
            throw std::domain_error("vectors must have the same length to use bitwise operators");
        }

        Vector<bool> tmp(this->size());

        std::size_t uint_ops = this->numElems();
        for(std::size_t t=0;t<uint_ops;++t){
            tmp.elems[t] = this->elems[t] | v.elems[t];
        }

        return tmp;
    };

/*
  std::size_t weight_math() const{
  std::size_t sum = 0;
  for(std::size_t i = 0;i<this->numElems();++i){
  //sum for element-i
  std::size_t xCount = elems[i] - ((elems[i] >> 1) & 033333333333) - ((elems[i] >> 2) & 011111111111);
  std::size_t sum_i = ((xCount + (xCount >> 3)) & 030707070707) % 63;
  sum+=sum_i;//add to the total
  }
  return sum;
  };

  std::size_t weight_lookup16() const{
  std::size_t sum = 0;
  union{
  unsigned short int s[2];
  unsigned int i;
  } mix;

  for(std::size_t i=0;i<this->numElems();++i){
  mix.i = this->elems[i];
  unsigned int sum_i = constant::lookup16bit[mix.s[0]]+constant::lookup16bit[mix.s[1]];
  sum+=sum_i;
  }
  return sum;
  }

  std::size_t weight_lookup8() const{
  std::size_t sum = 0;
  union{
  unsigned char c[4];
  unsigned int i;
  } mix;

  for(std::size_t i = 0;i<this->numElems();++i){
  //sum for element-i
  mix.i = this->elems[i];
  // printf("0x%x :\n" ,this->elems[i]);
  //for(unsigned int t=0;t<4;++t){
  //  printf("0x%x -> 0x%x\n",mix.c[t],constant::lookup8bit[mix.c[t]]);
  //  }

  unsigned int sum_i = constant::lookup8bit[mix.c[0]]+constant::lookup8bit[mix.c[1]]+constant::lookup8bit[mix.c[2]]+constant::lookup8bit[mix.c[3]];
  sum+=sum_i;//add it to the total
  }
  return sum;
  };


  std::size_t weight_builtin() const{
  std::size_t sum = 0;
  for(std::size_t i = 0;i<this->numElems();++i){
  sum+= __builtin_popcount(this->elems[i]);
  }
  return sum;
  }

  std::size_t weight_sparse() const{
  std::size_t sum = 0;
  for(std::size_t i = 0;i<this->numElems();++i){
  //sum for element-i
  std::size_t sum_i = 0;

  unsigned int n = this->elems[i];
  while(n){
  sum_i++;
  n&= (n-1);
  }

  sum+=sum_i;//add it to the total
  }
  return sum;
  };

  std::size_t weight_dense() const{
  std::size_t sum = 0;
  for(std::size_t i = 0;i<this->numElems();++i){
  //sum for element-i
  std::size_t sum_i = constant::BOOL_PER_INT; //go backwards since it faster when dense

  unsigned int n = (this->elems[i]^(static_cast<unsigned int>(-1)));
  while(n){
  sum_i--;
  n&= (n-1);
  }

  sum+=sum_i;//add it to the total
  }
  return sum;
  };
*/


    //-------------------------------------------------


    //TODO vet inte om den funkar riktigt som den ska
    operator unsigned int() const{
        //a mask to take away the bad data bits
        if(cur_size<constant::BOOL_PER_INT){
            unsigned int mask = -1; //biggest number
            mask <<= cur_size;
            mask = ~mask;

            //char buff[33];
            //helper::itoa2rev(buff,mask); //TODO SLIMJIM MAYBE WRONG WITH <<=

            // std::cout << "mask: " << buff << std::endl;

            return helper::reverseBits(elems[0]) & mask;
        }else{
            return helper::reverseBits(elems[0]); //take the first elems and convert that
        }
    };

    void reset(){
#ifdef DEBUG
        std::cout<<"in <bool>reset()"<<std::endl;
#endif
        reset(false);//reset(bool())
    };
    void reset(const bool& init_value){ //resets the array by setting all elements to zero (null reference)
#ifdef DEBUG
        std::cout<<"in <bool>reset(T init_elem)"<<std::endl;
#endif
        if(init_value){
            std::size_t numelems = numElems();
            for(std::size_t i = 0; i!=numelems; ++i){
                elems[i]=-1; //hax to set 0x1111111111111111
            }
        }else{
            std::size_t numelems = numElems();
            for(std::size_t i = 0; i!=numelems; ++i){
                elems[i]=0; //     to set 0x0000000000000000
            }
        }
    };

    void print() const{ //TODO check for this in Vector<T> also
#ifdef DEBUG
        std::cout<<"in <bool>print()" <<std::endl;
#endif
        char buff [constant::BOOL_PER_INT]; //numberof bits + '\000' TODO, is this correct ??
        std::size_t numelems =numElems();
        std::cout << '#' << cur_size << '/' << max_size << '[';
        for(std::size_t i = 0; i!=numelems ; i++){

            helper::itoa2(buff,elems[i]); //fill the buffer with the bit-values in char form
            std::size_t displaying_bits = (i+1)*constant::BOOL_PER_INT;

            if(displaying_bits > cur_size){ //if there is undefined elements in the integer display them as #
                for(std::size_t j = cur_size%constant::BOOL_PER_INT;j!=constant::BOOL_PER_INT;++j){
                    buff[j] = '#';
                }
            }
            std::cout << buff;
        }

        std::cout<< ']' << std::endl;
    };

    void push_back(const bool& t){
#ifdef DEBUG
        std::cout<<"in <bool>push_back(const bool& t)" <<std::endl;
#endif
        if(cur_size >= max_size){ //if it needs more memory
            change_size(2*max_size);
        }
        ++cur_size;
        (*this)[cur_size-1] = t; //TODO no need to use this when it uses proxys etc
    };


    void insert(const std::size_t, const bool&); //TODO
    void erase(const std::size_t);


    void clear(){
        delete [] elems;
        cur_size = 0;
        max_size = constant::BOOL_PER_INT;
        std::cout << "clear()" << std::endl;
        elems = new unsigned int[maxNumElems()];
    };

    void change_size(const std::size_t n){
#ifdef DEBUG
        std::cout<<"<bool>change_size("<< n << ")"<<std::endl;
#endif
        unsigned int* tmp_elems = new unsigned int[n/constant::BOOL_PER_INT]; //TODO make a factory for all this memory allocation calls

        // copy old array to tmp-array
        std::size_t i = 0;
        std::size_t numelems = numElems();
        for(; i!=numelems; ++i){ //copies one extra integer when divisible with BOOL_PER_INT since there is 2n+1 memory avaible and it works for n=1 as well, and the values that are overwriten are undefined so that isn't an issue
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
    };



};//end of template specialization for Vector<bool>
#endif
