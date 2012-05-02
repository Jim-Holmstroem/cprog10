#ifndef TEST_H
#define TEST_H

#include<string>
#include<vector>
#include<stdexcept>
#include<iterator>
/**/

struct ParseException : public std::runtime_error
{
    ParseException(const std::string& msg):std::runtime_error(msg){};
    ParseException(const std::string& token,const std::string& found)
        :std::runtime_error("missing '"+token+"',instead found: '"+found+"'"){};

};
/*
class Heap
{
  public:
    void load(stream){};
    void save(stream) const{};

    (void *) const operator[](const std::size_t UID) const
    {
               
    };
};

template<class T> class LoadFactory<T> 
{
  protected:
    Heap heap;
    void loadLevel(){
    
    };
    void loadTheHeap(){
    
    };
    void connectPointers(){
    
    };
  public:
    T* GetLevel(string filename)
    {
        
    };

};
*/

class ISerializable
{
   protected: 
    inline virtual void ToString(std::ostream& out) const{}; //TODO why can't these be pure virtual?
    inline virtual void FromString(std::istream& in){};

   public:
    friend std::ostream& operator<<(std::ostream& out,const ISerializable& s);
    friend std::istream& operator>>(std::istream& in,ISerializable& s);

};

//TODO where to put this?
inline void checkToken(std::istream& in,const std::string& check) throw()
{
    std::string token;
    in >> token;
    if(token.compare(check)!=0)
        throw ParseException(check,token);       
};

/*
inline bool peekToken(std::istream& in,const std::string& check)
{
    std::string token(in.peek());
    return token.compare(check)==0;
}
*/
std::ostream& operator<<(std::ostream& out,const ISerializable& s)
{
    out << "{ ";
    s.ToString(out);
    out << '}';
    return out;
};
std::istream& operator>>(std::istream& in,ISerializable& s)
{
    checkToken(in,"{");
    s.FromString(in);
    checkToken(in,"}");
    return in;
};

class MiniA : public ISerializable
{
    int mini1;
    int mini2;

  public:
    MiniA():mini1(13),mini2(37){};
    MiniA(int m1,int m2):mini1(m1),mini2(m2){};
  
  protected:
    inline virtual void ToString(std::ostream& out) const
    {
        out << mini1 << ' ' << mini2 << ' '; //TODO make a function to wich you only register wich ones that should be serialized 
    };
    inline virtual void FromString(std::istream& in)
    {
       in >> mini1 >> mini2; 
    };

};


class A : public ISerializable
{
    int var1;
    int var2;
    std::string var3;
    MiniA minia;
    MiniA minib;

  public:
    A():var1(1337),var2(1449),var3("bajs"),minia(12,34){};
    A(int v1,int v2,std::string v3):var1(v1),var2(v2),var3(v3),minia(12,34){};

  protected:
    inline virtual void ToString(std::ostream& out) const
    {
        out << var1 << ' ' << var2 << ' ' << var3 << ' ' << minia << ' ' << minib << ' ';
    };
    inline virtual void FromString(std::istream& in)
    {
        in >> var1 >> var2 >> var3 >> minia >> minib;
    };

};

/**/

class B : public A
{
    int varB1;
    std::string varB2;

  public:
    B():A(),varB1(9234),varB2("varB2"){};
    B(int v1,int v2,std::string v3,int vB1,std::string vB2):A(v1,v2,v3),varB1(vB1),varB2(vB2){};


  protected:
    inline virtual void ToString(std::ostream& out) const
    {
        A::ToString(out);
        out << "| "; 
        out << varB1 << ' ' << varB2 << ' ';
    };
    inline virtual void FromString(std::istream& in)
    {
        A::FromString(in);
        checkToken(in,"|"); 
        in >> varB1 >> varB2;
    };
};



//TODO the same thing for map
template< typename T,typename Allocator=std::allocator<T> > class SerializableVector: public ISerializable
{
  protected:
    std::vector<T,Allocator> content;

    //NOTE shouldn't inherit from STL-containers since they aren't made for it and you can end up with hardtofind errors and memory-leaks.
    //NOTE Can probably only use the standard allocator #STD_ALLOC_ONLY# since it haven't been considered in constructor and element access etc.
    //REF http://www.cplusplus.com/reference/stl/vector/

  public:

    typedef typename std::vector<T,Allocator>::iterator iterator;
    typedef typename std::vector<T,Allocator>::const_iterator const_iterator;
    typedef typename std::vector<T,Allocator>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T,Allocator>::const_reverse_iterator const_reverse_iterator;
    
    typedef typename std::vector<T,Allocator>::reference reference;
    typedef typename std::vector<T,Allocator>::const_reference const_reference;
    typedef typename std::vector<T,Allocator>::size_type size_type;
    typedef typename std::vector<T,Allocator>::difference_type difference_type;
    typedef typename std::vector<T,Allocator>::value_type value_type;
    typedef typename std::vector<T,Allocator>::allocator_type allocator_type;
    typedef typename std::vector<T,Allocator>::pointer pointer;
    typedef typename std::vector<T,Allocator>::const_pointer const_pointer;

    explicit SerializableVector(const allocator_type& alloc = allocator_type()):content(alloc){};
    explicit SerializableVector(size_type n,const_reference value = value_type(),const allocator_type& alloc = allocator_type()):content(n,value){};
    template<class InputIterator> SerializableVector(InputIterator first,InputIterator last):content(first,last){};
    SerializableVector(const SerializableVector& x)
    {
        this->content = x.content;            
    };
    SerializableVector& operator=(const SerializableVector& x)
    {
        this->content = x.content;
    };
    ~SerializableVector(){};

    //TODO make all these inline, since they are just all wrappers


    /* Iterators */

          iterator begin()        {return content.begin();};
    const_iterator begin() const{return content.begin();};//TODO verify that content in this situation is const
          iterator end()      {return content.end();};
    const_iterator end() const{return content.end();};
          reverse_iterator rbegin()      {return content.rbegin();};
    const_reverse_iterator rbegin() const{return content.rbegin();};
          reverse_iterator rend()      {return content.rend();};
    const_reverse_iterator rend() const{return content.rend();};
    
    /* Capacity */
    size_type size() const{return content.size();}; //TODO verify that it's ok to convert from size_type to size_t (also have this issue in several places trough-out)
    size_type max_size() const{return content.max_size();};
    void resize(size_type size,T c = T()){content.resize(size,c);};
    size_type capacity() const{return content.capacity();};
    bool empty() const{return content.empty();};
    void reserve(size_type n){content.reserve(n);};

    /* Element Access */
          reference operator[](size_type n)      {return content[n];};
    const_reference operator[](size_type n) const{return content[n];};
          reference at(size_type n)      {return content.at(n);};
    const_reference at(size_type n) const{return content.at(n);};
          reference front(size_type n)      {return content.front(n);};
    const_reference front(size_type n) const{return content.front(n);};
          reference back(size_type n)      {return content.back(n);};
    const_reference back(size_type n) const{return content.back(n);};

    /* Modifiers */
    template <class InputIterator> void assign(InputIterator first,InputIterator last){content.assign(first,last);};
    void assign(size_type n,const_reference u){content.assign(n,u);};
    void push_back(const_reference x){content.push_back(x);};
    void pop_back(){content.pop_back();};
    iterator insert(iterator pos,const_reference x){return content.insert(pos,x);};
        void insert(iterator pos,size_type n,const_reference x){content.insert(pos,n,x);};
    template <class InputIterator> void insert(iterator pos,InputIterator first,InputIterator last){content.insert(pos,first,last);};
    iterator erase(iterator pos){return content.erase(pos);};
    iterator erase(iterator first,iterator last){return content.erase(first,last);};
    void swap(SerializableVector& vec){
        throw std::exception("not implemented yet");
    };
    void clear(){content.clear();};

    /* Allocator */
    //allocator_type get_allocator() const; OMITTED

  protected:
    inline virtual void ToString(std::ostream& out) const
    {
        /*for(std::vector<T>::const_iterator it = content.begin();it!=content.end();)
        {
            out << *it;
            ++it;
            if(it!=content.end())
            {
                out << ", ";
            }
        }*/
    };
    inline virtual void FromString(std::istream& in)
    {
     
    };
    
};


/* TODO Stream-operators for the vector-types,instead use specialclass, and ToString/FromString as in the others */
/*template<typename T>
std::ostream& operator<<(std::ostream& out,std::vector<T> vec)
{
    return out;
};
*/

#endif
