#include "vector.h"

using namespace std;
typedef unsigned int uint;

Vector::Vector(): size(0), max_size(1){
#ifdef DEBUG
    cout<<"Vector()"<<endl;
#endif

    elems  = new uint[max_size];
    reset();
}

Vector::Vector(const size_t n): size(n), max_size(size){
#ifdef DEBUG
    cout<<"in Vector(uint n)"<<endl;
#endif

    elems = new uint[max_size];
    reset(); //resets to zero to be sure since uninitialized is undefined can be anything
}

Vector::Vector(const Vector& v){ //copy constructor
#ifdef DEBUG
    cout << "in Vector(const Vector& v):" << endl;
#endif

    elems = new uint[v.max_size];

    std::copy(v.elems,v.elems+v.size,elems);

    //       for(size_t i = 0; i!=v.max_size; ++i){
    //           elems[i] = v.elems[i];
    //           #ifdef DEBUG
    //           cout << "in Vector(const Vector& v):  i, elems[i]=" << i << "," << elems[i] << endl;
    //           #endif
    //       }

    this->size = v.size;
    this->max_size = v.max_size;

}

Vector::~Vector(){
#ifdef DEBUG
    cout << "~Vector" << endl;
#endif
    delete [] elems;
}

uint& Vector::operator[](const size_t i) {
    if(i < size){
#ifdef DEBUG
        cout << "in operator[]" << endl;
#endif
        return elems[i];
    }else{
        throw out_of_range("!");
    }
}
const uint& Vector::operator[](const size_t i) const {
    if(i < size){
#ifdef DEBUG
        cout << "in const operator[] const" << endl;
#endif
        return elems[i];
    }else{
        throw out_of_range("");
    }
}

Vector& Vector::operator=(const Vector& v){
    if (this != &v){ // protect against invalid self-assignment
#ifdef DEBUG
        cout << "operator=" << endl;
#endif

        uint* new_elems = new uint[v.max_size];

        std::copy(v.elems,v.elems+v.size,new_elems);

        //skapa en ny tom array med rätt storlek (tar kopiera size och max_size från v)
        //
        //    for(size_t i = 0; i!=v.size; ++i){
        //        new_elems[i] = v.elems[i];
        //    }

        delete [] elems;

        this->elems = new_elems;
        this->size = v.size;
        this->max_size = v.max_size;
    }
    return *this;
}


void Vector::reset(){ //resets the array by setting all elements to zero (null reference)
#ifdef DEBUG
    cout<<"in reset()"<<endl;
#endif
    for(size_t i = 0; i!=size; ++i){
        elems[i]=0;
    }
}

#ifdef DEBUG
void Vector::print(){
    cout << "#" << size << "/" << max_size << "[";
    for(size_t i = 0; i != size; ++i){
        cout << elems[i] << ((i!=(size-1))?",":"");
    }
    cout <<  "]" << endl;
}
#endif

/*    void Vector::push_back(const size_t& n){
      if(size >= max_size){
      change_size(2*max_size+1);
      }
      elems[size] = n;
      ++size;

      }


      void Vector::change_size(const size_t n){
      #ifdef DEBUG
      cout<<"change_size("<< n << ")"<<endl;
      #endif

      uint* tmp_elems = new uint[n];


      // copy old array to tmp-array
      size_t i = 0;
      for(; i!=this->size; ++i){
      tmp_elems[i] = this->elems[i];
      }
      //set the rest of the new array
      for(; i!=n; ++i){
      tmp_elems[i] = 0;
      }

      delete [] elems;
      this->elems = tmp_elems;
      //set new max_size
      this->max_size = n;

      }*/


