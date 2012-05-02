/**
   TODO: Interger conversion
*/

#ifndef VECTOR_H
#define VECTOR_H
#include <cstring>
#include <stdexcept>
#include <exception>
#include <iostream>
#include <cmath>

template <class T>
class Vector
{
  public:
    //constructors
    Vector();
    explicit Vector(size_t);
    Vector(size_t, T);
    Vector(const Vector &);
    virtual ~Vector();

    //member functions
    void push_back(T); //add an element to the end of array
    void insert(int, T); //insert an element before the position declared in the first argument
    void erase(int); //erase the element at the position in the argument
    void clear(); //remove all the elements
    void sort(bool ascending = true);
    size_t size() const;

    //operators
    Vector & operator= (const Vector &);
    T & operator[] (int);
    const T & operator[] (int) const;
  private:
    size_t numEls;
    size_t maxEls;
    T * elems;
    void checkOutOfRange(int) const;
};

/******************************
          Constructors and destructors
******************************/

//Default constructor
template <class T>
Vector<T>::Vector():
numEls(0), maxEls(1), elems(new T[maxEls])
{
}

//Constructor with a set size
template <class T>
Vector<T>::Vector(size_t s):
numEls(s), maxEls(2*s+1), elems(new T[maxEls])
{
    for(int i=0; i<numEls; i++)
    {
        elems[i] = T(); //initialize to default value
    }
}

//Constructor with set size and a default value
template <class T>
Vector<T>::Vector(size_t s, T t):
numEls(s), maxEls(2*s+1), elems(new T[maxEls])
{
    for(int i=0; i<numEls; i++)
    {
        elems[i] = t;
    }
}

//Copy constructor
template <class T>
Vector<T>::Vector(const Vector &orig):
numEls(orig.numEls), elems(new T[orig.maxEls]), maxEls(orig.maxEls)
{
    for(int i=0; i < numEls; i++)
    {
        elems[i] = orig.elems[i];
    }
}

//Destructor
template <class T>
Vector<T>::~Vector()
{
    delete [] elems;
}

/******************************
          Operators
******************************/

//assignment operator
template <class T>
Vector<T> & Vector<T>::operator=(const Vector &rhs)
{
    if(&rhs != this)
    {
        T * elemsTemp = new T[rhs.maxEls];

        for(int i = 0; i < rhs.numEls; i++)
        {
            elemsTemp[i] = rhs.elems[i];
        }

        delete [] elems;
        elems = elemsTemp;
        numEls = rhs.numEls;
        maxEls = rhs.maxEls;
    }

    return *this;
}

//bracket operator
    template <class T>
    T & Vector<T>::operator[] (int index)
    {
        checkOutOfRange(index);
        return elems[index];
    }

template <class T>
const T & Vector<T>::operator[] (int index) const
{
    checkOutOfRange(index);
    return elems[index];
}

/******************************
          Methods
******************************/

//get the size of the vector
template <class T>
size_t Vector<T>::size() const
{
    return numEls;
}

//add an element to the end of array
template <class T>
void Vector<T>::push_back(T value)
{
    insert(numEls, value);
}

//insert an element at pos
template <class T>
void Vector<T>::insert(int pos, T value)
{
    if(pos > numEls || pos < 0)
        throw std::out_of_range("Index was out of range");

    if(numEls >= maxEls)
    {
        maxEls = maxEls == 0 ? 1 : 2*maxEls+1;
        T * tmp = new T[maxEls];

        for(int i=0; i<numEls; i++)
        {
            tmp[i] = elems[i];
        }

        delete [] elems;
        elems = tmp;
    }

    for(int i= numEls; i > pos; i--)
    {
        elems[i] = elems[i-1];
    }
    elems[pos] = value;
    numEls++;
}

//erase the element at the position in the argument
template <class T>
void Vector<T>::erase(int pos)
{
    checkOutOfRange(pos);

    //check if the allocated memory is way to large
    if(maxEls > 4*numEls) {
        T * tmp = new T[numEls*2+1];

        for(int i=0; i<numEls; i++)
        {
            tmp[i] = elems[i];
        }

        delete [] elems;
        maxEls = numEls*2+1;
        elems = tmp;
    }

    for(int i=pos; i<(numEls-1); i++)
    {
        elems[i] = elems[i+1];
    }

    numEls--;
}

//remove all the elements in the vector
template <class T>
void Vector<T>::clear()
{
    delete [] elems;
    elems = new T[1];
    numEls = 0;
    maxEls = 1;
}

//Sorting - uses shell sort
template <class T>
void Vector<T>::sort(bool ascending)
{
    int inc = (int)(size()/2);
    T temp;
    bool flag = true;

    while(inc > 1 || flag)
    {
        inc = (int)((inc+1)/2);
        flag = false;

        for(int i=inc; i<size(); i++)
        {
            temp = (*this)[i];

            if(ascending)
            {
                if((*this)[i] < (*this)[i-inc]) {
                    //swap positions
                    (*this)[i] = (*this)[i-inc];
                    (*this)[i-inc] = (*this);
                    flag = true;
                }

            }
            else
            {
                if((*this)[i-inc] < (*this)[i]) {
                    //swap positions
                    (*this)[i] = (*this)[i-inc];
                    (*this)[i-inc] = temp;
                    flag = true;
                }
            }
        }
    }
}

/******************************
          Help methods
******************************/

template <class T>
void Vector<T>::checkOutOfRange(int index) const
{
    if((index+1) > numEls || index < 0)
    {
        throw std::out_of_range("Index was out of range!");
    }
}

/******************************
          Boolean Specialization
          Stores booleans as bits (0/1) in unsigned ints. An unsigned int holds
          32 bits, the first bit corresponding to 2^0, second to 2^1, third to 2^2 etc.
******************************/

int bits_per_uint = sizeof(unsigned int)*8; //number of bits stored in each unsigned int

template <>
class Vector<bool>
{
  public:
    class Reference;
    //constructors
  Vector() : _size(0), _uint_size(1), elements(new unsigned int[1]) { }
    explicit Vector(size_t);
    Vector(size_t, bool);
    Vector(const Vector<bool> &);
    ~Vector();

    //member functions
    void push_back(const bool &); //add an element to the end of array
    void clear(); //remove all the elements
    void insert(size_t, bool);
    //void erase(size_t); <- not mandatory, current version is not working anyway
    void sort(bool ascending = true);
    size_t size() const;
    size_t weight() const;
    size_t weight2() const;
    size_t weight3() const;

    //operators
    Vector & operator= (const Vector<bool> &);
    Reference operator[] (size_t);
    const bool operator[] (size_t) const;
    operator unsigned int () const;
    Vector<bool> operator & (Vector<bool> &) const;
    Vector<bool> operator | (Vector<bool> &) const;
    Vector<bool> operator ^ (Vector<bool> &) const;
    Vector<bool> operator ~() const;

    //Reference class, used to point to bits
    typedef const bool & const_reference;
    class Reference
    {
      public:
        Reference(size_t, Vector<bool> *);
        Reference & operator=(const Reference &);
        Reference & operator=(const bool &);
        operator bool() const;
      private:
        size_t index;
        Vector<bool> * parent;
    };

    //const_iterator and iterator
    class const_iterator
    {
      protected:
        size_t index;
        const Vector<bool> * parent;
        void is_valid() const;
      public:
        typedef ptrdiff_t difference_type;
        typedef const bool value_type;
        typedef const bool * pointer;
        typedef const bool reference;
        typedef std::random_access_iterator_tag iterator_category;

        const_iterator();
        const_iterator(size_t, const Vector<bool> *);
        const_iterator(const const_iterator &);

        //operators
        const_iterator & operator=(const const_iterator &);

        //dereference
        reference operator*() const;
        reference operator[](int) const;

        //arithmetics
        const_iterator    operator+(int) const;
        const_iterator    operator-(int) const;
        difference_type   operator-(const const_iterator &) const;
        const_iterator  & operator++();
        const_iterator  & operator--();
        const_iterator    operator++(int);
        const_iterator    operator--(int);
        const_iterator  & operator+=(int);
        const_iterator  & operator-=(int);

        bool operator==(const const_iterator &) const;
        bool operator!=(const const_iterator &) const;
        bool operator<(const const_iterator &) const;
        bool operator>(const const_iterator &) const;
        bool operator<=(const const_iterator &) const;
        bool operator>=(const const_iterator &) const;
    };

    class iterator : public const_iterator
    {
      public:
        typedef bool value_type;
        typedef bool * pointer;
        typedef Reference reference;

      iterator() : const_iterator() { };
      iterator(size_t s, const Vector<bool> * p) : const_iterator(s, p) { }
      iterator(const iterator & i) : const_iterator(i) { }
        iterator & operator=(const iterator &);

        //dereference
        reference operator*() const;
        reference operator[](int) const;

        //arithmetics
        using const_iterator::operator-;
        iterator    operator+(int) const;
        iterator    operator-(int) const;
        iterator  & operator++();
        iterator  & operator--();
        iterator    operator++(int);
        iterator    operator--(int);
        iterator  & operator+=(int);
        iterator  & operator-=(int);
    };

    const_iterator begin() const { return const_iterator(0, this); }
    iterator begin() { return iterator(0, this); }
    const_iterator end() const { return const_iterator(size(), this); }
    iterator end() { return iterator(size(), this); }


    static Vector<bool> construct_from_int(unsigned int k)
    {
        Vector<bool> tmp(bits_per_uint);
        tmp.elements[0] = k;
        return tmp;
    }
  private:
    size_t _size; //current size
    size_t _uint_size; //how many unsigned ints that have been allocated
    unsigned int * elements;
    void check_out_of_range(const size_t &) const;
    size_t get_outer_index(const size_t &) const;
    size_t get_inner_index(const size_t &) const;
    bool get_bool_value(const size_t &) const;
    void assign_value(const size_t &, const bool &);
    void swap_bit(const size_t &);
    void grow_if_needed();
    void shrink_if_needed();
    size_t get_max(size_t, size_t) const;
    unsigned int bit_window(int start=0, int end=bits_per_uint-1) const;
    size_t get_largest_uint_index() const;
};

/******Reference class*******/
//constructor
Vector<bool>::Reference::Reference(size_t ind, Vector<bool> * p)
: index(ind), parent(p)
{ }

//assignment operator that takes another Reference object
Vector<bool>::Reference & Vector<bool>::Reference::operator=(const Vector<bool>::Reference & r)
{
    if(this != &r)
    {
        //check if the bits that the two Reference:s refer to are different
        if(!(bool(*this) == bool(r)))
        {
            //in that case swap the bit
            parent->elements[parent->get_outer_index(index)] ^= (1 << parent->get_inner_index(index));
        }
    }
    return *this;
}

//assignment operator for a bool object
    Vector<bool>::Reference & Vector<bool>::Reference::operator=(const bool & b)
    {
        if(b)
        {
            parent->elements[parent->get_outer_index(index)] |= (1 << parent->get_inner_index(index));
        }
        else
        {
            parent->elements[parent->get_outer_index(index)] &= ~(1 << parent->get_inner_index(index));
        }
        return *this;
    }

    //bool parsing
        Vector<bool>::Reference::operator bool() const
        {
            return parent->get_bool_value(index);
        }

/******** Vector<bool> ********/
/******************************
          Constructors and destructors
******************************/

//Constructor with set size
Vector<bool>::Vector(size_t s)
: _size(s), _uint_size(s / bits_per_uint + 1), elements(new unsigned int[_uint_size])
{
    //fill with false's, i.e. zero bits
    for(int i=0; i < _uint_size; i++)
    {
        elements[i] = 0;
    }
}

Vector<bool>::Vector(size_t s, bool val)
: _size(s), _uint_size(s / bits_per_uint + 1), elements(new unsigned int[_uint_size])
{
    if(val)
    {
        //fill with 1s
        for(int i=0; i < _uint_size; i++)
        {
            elements[i] = ~0; //fill with 1:s
        }
    }
    else
    {
        //fill with 0s
        for(int i=0; i < _uint_size; i++)
        {
            elements[i] = 0; //fill with 0:s
        }
    }
}

//Copy constructor
Vector<bool>::Vector(const Vector<bool> & v)
: _size(v.size()), _uint_size(v._uint_size), elements(new unsigned int[_uint_size])
{
    for(int i=0; i < _uint_size; i++)
    {
        elements[i] = v.elements[i];
    }
}

//destructor
Vector<bool>::~Vector()
{
    delete [] elements;
}

/******************************
          Operators
******************************/

Vector<bool> & Vector<bool>::operator= (const Vector<bool> & v)
{
    if(this != &v)
    {
        unsigned int * tmp = new unsigned int[v._uint_size];

        //copy
        for(int i=0; i < v._uint_size; i++)
        {
            tmp[i] = v.elements[i];
        }

        delete [] elements;
        elements = tmp;
        _size = v.size();
        _uint_size = v._uint_size;
    }
    return *this;
}

    Vector<bool>::Reference Vector<bool>::operator[] (size_t ind)
    {
        check_out_of_range(ind);
        return Vector<bool>::Reference(ind,this);
    }

const bool Vector<bool>::operator[] (size_t ind) const
{
    check_out_of_range(ind);
    return get_bool_value(ind);
}

// Type conversion
Vector<bool>::operator unsigned int () const
{
    if(size() > bits_per_uint)
        throw std::out_of_range("Int overflow");

    return elements[0];
}

// Bitwise operators
Vector<bool> Vector<bool>::operator ~() const
{
    Vector<bool> tmp(this->size());
    for(int i=0; i <= tmp.get_largest_uint_index(); i++)
    {
        tmp.elements[i] = ~(this->elements[i]);
    }
    return tmp;
}

Vector<bool> Vector<bool>::operator & (Vector<bool> & rhs) const
{
    Vector<bool> tmp(get_max(this->size(), rhs.size())); //tmp is filled with 0:s
    for(int i=0; i <= tmp.get_largest_uint_index(); i++)
    {
        //check if there's anything to copy from the first vector
        if(this->size() > bits_per_uint*i)
        {
            tmp.elements[i] = this->elements[i];
        }

        //do the same check for the other vector
        if(rhs.size() > bits_per_uint*i)
        {
            //if an element is 0, &= will yield 0, which is expected
            tmp.elements[i] &= rhs.elements[i];
        }
        else
        {
            tmp.elements[i] = 0;
        }
    }
    return tmp;
}

Vector<bool> Vector<bool>::operator | (Vector<bool> & rhs) const
{
    Vector<bool> tmp(get_max(this->size(), rhs.size())); //tmp is filled with 0:s

    for(int i=0; i <= tmp.get_largest_uint_index(); i++)
    {
        //check if there's anything to copy from the first vector
        if(this->size() > bits_per_uint*i)
        {
            tmp.elements[i] = this->elements[i];
        }

        //do the same check for the other vector
        if(rhs.size() > bits_per_uint*i)
        {
            //if an element is 0, |= will have the same effect as =
            tmp.elements[i] |= rhs.elements[i];
        }
    }
    return tmp;
}

Vector<bool> Vector<bool>::operator ^ (Vector<bool> & rhs) const
{
    Vector<bool> tmp(get_max(this->size(), rhs.size())); //tmp is filled with 0:s
    for(int i=0; i <= tmp.get_largest_uint_index(); i++)
    {
        //check if there's anything to copy from the first vector
        if(this->size() > bits_per_uint*i)
        {
            tmp.elements[i] = this->elements[i];
        }

        //do the same check for the other vector
        if(rhs.size() > bits_per_uint*i)
        {
            tmp.elements[i] ^= rhs.elements[i];
        }
    }
    return tmp;
}


/******************************
          Methods
******************************/

void Vector<bool>::push_back(const bool & v)
{
    grow_if_needed();
    assign_value(_size, v); //assign v to the last element
    _size++;
}

void Vector<bool>::insert(size_t ind, bool val)
{
    if(ind > _size || ind < 0)
    {
        throw std::out_of_range("Index out of range!");
    }
    else if(ind == _size)
    {
        push_back(val); //this saves some operations
    }
    else
    {
        grow_if_needed();

        //pick out the bits before 'ind'
        unsigned int pick_out_bits = bit_window(0,get_inner_index(ind)-1);
        size_t outer_index = get_outer_index(ind);

        unsigned int tmp = elements[outer_index] & pick_out_bits;

        //store the last bit as: x??????? -> 0000000x
        unsigned int next_first_bit = (elements[outer_index] & (1 << (bits_per_uint-1))) >> (bits_per_uint-1); //last bit in the current
        unsigned int next_first_bit_temp;

        //shift all 1 step
        elements[outer_index] <<= 1;

        //use xxxx0000 | 0000yyyy -> xxxxyyyy
        elements[outer_index] = (elements[outer_index] & ~pick_out_bits) | tmp;

        for(int i=(outer_index+1); i<=get_outer_index(_size+1); i++)
        {
            next_first_bit_temp = (elements[i] & (1 << (bits_per_uint-1))) >> (bits_per_uint-1);
            elements[i] <<= 1;
            elements[i] |= next_first_bit;
            next_first_bit = next_first_bit_temp;
        }

        assign_value(ind, val); //assign v at ind
        _size++;
    }
}

/*void Vector<bool>::erase(size_t ind)
  {
  check_out_of_range(ind);
  shrink_if_needed();

  //pick out the bits before 'ind'
  unsigned int pick_out_bits = 0;
  size_t ind_before = 0;
  if(ind != 0)
  {
  if(ind % bits_per_uint == 0) //first element in an array
  ind_before = ind;
  else
  ind_before = ind - 1;
  }
  size_t outer_index = get_outer_index(ind_before);
  for(int i=0; i < get_inner_index(ind_before); i++)
  {
  pick_out_bits += (1 << i);
  }

  unsigned int tmp = elements[outer_index] & pick_out_bits;
  unsigned int next_last_bit = 0;
  unsigned int next_last_bit_temp = 0;

  for(size_t i=get_outer_index(_size); i > outer_index; i--)
  {
  //store the first bit as: ???????x -> x0000000
  next_last_bit_temp = (elements[outer_index] & 1) << (bits_per_uint-1);
  elements[i] >>= 1;
  elements[i] |= next_last_bit;
  next_last_bit = next_last_bit_temp;
  }

  elements[outer_index] >>= 1;
  if(ind % bits_per_uint != 0 && ind != 0)
  elements[outer_index] |= next_last_bit;

  //Reinsert the elements that was before "ind"
  elements[outer_index] = (elements[outer_index] & ~pick_out_bits) | tmp;

  _size--;
  }*/

void Vector<bool>::sort(bool ascending)
{
    size_t num_ones = weight3();
    if(ascending)
    {
        size_t num_zeroes = size() - num_ones;
        size_t num_zero_parts = num_zeroes/bits_per_uint; //number of uints fully filled with 0s
        for(size_t i=0; i <= get_largest_uint_index(); i++)
        {
            if(num_zero_parts > i)
            {
                elements[i] = 0;
            }
            else if(num_zero_parts == i)
            {
                elements[i] = bit_window(num_zeroes-i*bits_per_uint);
            }
            else
            {
                elements[i] = ~0;
            }
        }
    }
    else
    {
        size_t num_ones_parts = num_ones/bits_per_uint;
        for(size_t i=0; i <= get_largest_uint_index(); i++)
        {
            if(num_ones_parts > i)
            {
                elements[i] = ~0;
            }
            else if(num_ones_parts == i)
            {
                elements[i] = bit_window(0,num_ones-i*bits_per_uint-1);
            }
            else
            {
                elements[i] = 0;
            }
        }
    }
}

size_t Vector<bool>::size() const
{
    return _size;
}

void Vector<bool>::clear()
{
    delete [] elements;
    elements = new unsigned int[1];
    _uint_size = 1;
    _size = 0;
}

size_t Vector<bool>::weight() const
{
    short bit_map[256] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

    size_t count = 0;
    unsigned int byte_map = 255; // 00000000000000000000000011111111
    for(size_t i=0; i <= get_largest_uint_index() ; i++)
    {
        for(unsigned int val= elements[i]; val != 0; val >>= 8)
        {
            count += bit_map[val & byte_map];
        }
    }
    return count;
}

size_t Vector<bool>::weight2() const
{
    size_t count = 0;
    for(size_t i=0; i <= get_largest_uint_index() ; i++)
    {
        for(unsigned int map=1; map != 0; map <<= 1)
        {
            if((elements[i] & map) != 0)
            {
                count++;
            }
        }
    }
    return count;
}

size_t Vector<bool>::weight3() const
{
    size_t count = 0;
    for(size_t i=0; i <= get_largest_uint_index() ; i++)
    {
        unsigned int x = elements[i];
        size_t xCount = x - ((x >> 1) & 033333333333) - ((x >> 2) & 011111111111);
        count += ((xCount + (xCount >> 3)) & 030707070707) % 63;

    }
    return count;
}

/******************************
          Help methods
******************************/

void Vector<bool>::check_out_of_range(const size_t & index) const
{
    if(index >= size() || index < 0)
    {
        std::cout << index << std::endl;
        throw std::out_of_range("Index out of range!");
    }
}

size_t Vector<bool>::get_outer_index(const size_t & ind) const
{
    return ind/bits_per_uint;
}

size_t Vector<bool>::get_inner_index(const size_t & ind) const
{
    return ind%bits_per_uint;
}

bool Vector<bool>::get_bool_value(const size_t & ind) const
{
    return (elements[get_outer_index(ind)] & (1 << get_inner_index(ind))) != 0;
}

void Vector<bool>::assign_value(const size_t & ind, const bool & val)
{
    if(val)
    {
        elements[get_outer_index(ind)] |= (1 << get_inner_index(ind));
    }
    else
    {
        elements[get_outer_index(ind)] &= ~(1 << get_inner_index(ind));
    }
}

void Vector<bool>::grow_if_needed()
{
    //check if size is to small
    if((_size+1) >= _uint_size * bits_per_uint)
    {
        //allocate memory
        size_t _uint_size_old = _uint_size;
        _uint_size = 2*_uint_size + 1;
        unsigned int * temp = new unsigned int[_uint_size];

        for(int i = 0; i < _uint_size_old; i++)
        {
            temp[i] = elements[i];
        }
        delete [] elements;
        elements = temp;
    }
}

void Vector<bool>::shrink_if_needed()
{
    //check if _uint_size is to big
    if(_size < 4*_uint_size * bits_per_uint)
    {
        //allocate memory
        _uint_size = 2*_size/bits_per_uint + 1;
        unsigned int * temp = new unsigned int[_uint_size];

        for(int i = 0; i < _uint_size; i++)
        {
            temp[i] = elements[i];
        }
        delete [] elements;
        elements = temp;
    }
}

void Vector<bool>::swap_bit(const size_t & ind)
{
    elements[get_outer_index(ind)] ^= (1 << get_inner_index(ind));
}

size_t Vector<bool>::get_max(size_t n1, size_t n2) const
{
    if(n1 > n2)
    {
        return n1;
    }
    return n2;
}

unsigned int Vector<bool>::bit_window(int start, int end) const
{
    unsigned int bit_win = 0;
    for(int i=start; i <= end; i++)
    {
        bit_win += (1 << i);
    }
    return bit_win;
}

size_t Vector<bool>::get_largest_uint_index() const
{
    return get_outer_index(size()-1);
}

/*****************
   const_iterator
*****************/

Vector<bool>::const_iterator::const_iterator()
: index(0), parent(0)
{}

Vector<bool>::const_iterator::const_iterator(size_t s, const Vector<bool> * p)
: index(s), parent(p)
{ }

Vector<bool>::const_iterator::const_iterator(const Vector<bool>::const_iterator & c)
: index(c.index), parent(c.parent)
{ }

//operators
Vector<bool>::const_iterator & Vector<bool>::const_iterator::operator=(const Vector<bool>::const_iterator & c)
{
    if(this != &c)
    {
        index = c.index;
        parent = c.parent;
    }
    return *this;
}

//dereference
    Vector<bool>::const_iterator::reference Vector<bool>::const_iterator::operator*() const
    {
        is_valid();
        return (*parent)[index];
    }

Vector<bool>::const_iterator::reference Vector<bool>::const_iterator::operator[](int s) const
{
    return *((*this)+s);
}

//arithmetics
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator+(int s) const
{
    is_valid();
    const_iterator tmp(*this);
    tmp.index += s;
    return tmp;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator-(int s) const
{
    return (*this) + (-s);
}

Vector<bool>::const_iterator::difference_type Vector<bool>::const_iterator::operator-(const Vector<bool>::const_iterator & rhs) const
{
    is_valid();
    return index - rhs.index;
}
Vector<bool>::const_iterator & Vector<bool>::const_iterator::operator++()
{
    return (*this) += 1;
}

Vector<bool>::const_iterator & Vector<bool>::const_iterator::operator--()
{
    return (*this) -= 1;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator++(int)
{
    is_valid();
    const_iterator tmp(*this);
    index++;
    return tmp;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator--(int)
{
    is_valid();
    const_iterator tmp(*this);
    --index;
    return tmp;
}

Vector<bool>::const_iterator & Vector<bool>::const_iterator::operator+=(int s)
{
    is_valid();
    index += s;
    return *this;
}

Vector<bool>::const_iterator & Vector<bool>::const_iterator::operator-=(int s)
{
    return (*this) += (-s);
}

bool Vector<bool>::const_iterator::operator<(const Vector<bool>::const_iterator & rhs) const
{
    is_valid();
    if(parent != rhs.parent)
    {
        throw std::runtime_error("The iterators are not pointing to the same Vector.");
    }
    return (index < rhs.index);
}

bool Vector<bool>::const_iterator::operator>(const Vector<bool>::const_iterator & rhs) const
{
    return rhs < (*this);
}

bool Vector<bool>::const_iterator::operator==(const Vector<bool>::const_iterator & rhs) const
{
    return !(((*this) < rhs) || ((*this) > rhs));
}

bool Vector<bool>::const_iterator::operator!=(const Vector<bool>::const_iterator & rhs) const
{
    return !((*this) == rhs);
}
bool Vector<bool>::const_iterator::operator<=(const Vector<bool>::const_iterator & rhs) const
{
    return !((*this) > rhs);
}

bool Vector<bool>::const_iterator::operator>=(const Vector<bool>::const_iterator & rhs) const
{
    return !((*this) < rhs);
}

void Vector<bool>::const_iterator::is_valid() const
{
    if(parent == 0)
        throw std::runtime_error("Iterator is invalid");
}

/*****************
          iterator
*****************/

//dereference
Vector<bool>::iterator::reference Vector<bool>::iterator::operator*() const
{
    is_valid();
    return (*const_cast<Vector<bool>*>(parent))[index];
}

Vector<bool>::iterator::reference Vector<bool>::iterator::operator[](int s) const
{
    return *((*this) + s);
}

Vector<bool>::iterator & Vector<bool>::iterator::operator=(const Vector<bool>::iterator & i)
{
    if(this != &i)
    {
        index = i.index;
        parent = i.parent;
    }
    return *this;
}

//arithmetics
    Vector<bool>::iterator Vector<bool>::iterator::operator+(int s) const
    {
        is_valid();
        iterator tmp(*this);
        tmp.index += s;
        return tmp;
    }

Vector<bool>::iterator Vector<bool>::iterator::operator-(int s) const
{
    return (*this) + (-s);
}

Vector<bool>::iterator & Vector<bool>::iterator::operator++()
{
    return (*this) += 1;
}

Vector<bool>::iterator & Vector<bool>::iterator::operator--()
{
    return (*this) -= 1;
}

Vector<bool>::iterator Vector<bool>::iterator::operator++(int)
{
    is_valid();
    iterator tmp(*this);
    ++index;
    return tmp;
}

Vector<bool>::iterator Vector<bool>::iterator::operator--(int)
{
    is_valid();
    iterator tmp(*this);
    --index;
    return tmp;
}

Vector<bool>::iterator & Vector<bool>::iterator::operator+=(int s)
{
    is_valid();
    index += s;
    return *this;
}

Vector<bool>::iterator & Vector<bool>::iterator::operator-=(int s)
{
    return (*this) += (-s);
}
#endif
