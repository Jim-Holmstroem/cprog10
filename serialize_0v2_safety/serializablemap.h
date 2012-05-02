#ifndef SERIALIZABLEMAP_H
#define SERIALIZABLEMAP_H

#include<iostream>
#include<vector>
#include<exception>

template< typename Key,typename T,typename Compare = less<Key>,typename Allocator alloc=std::allocator< std::pair<const Key,T> > > class SerializableMap: public ISerializable
{
  protected:
    std::map<Key,T,Compare,Allocator> map;

    //NOTE shouldn't inherit from STL-containers since they aren't made for it and you can end up with hardtofind errors and memory-leaks.
    //REF http://www.cplusplus.com/reference/stl/map/

  public:
    typedef typename std::map<Key,T,Compare,Allocator>::key_type key_type;
    typedef typename std::map<Key,T,Compare,Allocator>::mapped_type mapped_type;
    typedef typename std::map<Key,T,Compare,Allocator>::value_type value_type;
    
    typedef typename std::map<Key,T,Compare,Allocator>::key_compare key_compare;
    typedef typename std::map<Key,T,Compare,Allocator>::value_compare value_compare;
    
    typedef typename std::map<Key,T,Compare,Allocator>::allocator_type allocator_type;
    
    typedef typename std::map<Key,T,Compare,Allocator>::size_type size_type;
    typedef typename std::map<Key,T,Compare,Allocator>::difference_type difference_type;

    typedef typename std::map<Key,T,Compare,Allocator>::reference reference;
    typedef typename std::map<Key,T,Compare,Allocator>::const_reference const_reference;

    typedef typename std::map<Key,T,Compare,Allocator>::pointer pointer;
    typedef typename std::map<Key,T,Compare,Allocator>::const_pointer const_pointer;
    
    typedef typename std::map<Key,T,Compare,Allocator>::iterator iterator;
    typedef typename std::map<Key,T,Compare,Allocator>::const_iterator const_iterator;
    typedef typename std::map<Key,T,Compare,Allocator>::reverse_iterator reverse_iterator;
    typedef typename std::map<Key,T,Compare,Allocator>::const_reverse_iterator;

    explicit SerializableMap(const Compare& comp = Compare(),const Allocator& alloc = Allocator()):map(comp,alloc){};
    template <class InputIterator> SerializableMap(InputIterator first,InputIterator last,const Compare& comp = Compare(),const Allocator& alloc = Allocator()):map(first,last,comp,alloc){};
    SerializableMap(const SerializableMap& x){
        this->map = x.map;
    };
    SerializableMap& operator=(const SerializableMap& x)
    {
        this->map = x.map;
        return *this;
    };
    ~SerializableMap(){};

    /* Iterators */

          iterator begin()        {return map.begin();};
    const_iterator begin() const{return map.begin();};
          iterator end()      {return map.end();};
    const_iterator end() const{return map.end();};
          reverse_iterator rbegin()      {return map.rbegin();};
    const_reverse_iterator rbegin() const{return map.rbegin();};
          reverse_iterator rend()      {return map.rend();};
    const_reverse_iterator rend() const{return map.rend();};
   
    /* Capacity */
    size_type size() const{return map.size();}; 
    size_type max_size() const{return map.max_size();};
    bool empty() const{return map.empty();};

    /* Element Access */
          reference operator[](const key_type& x)      {return map[x];};
    //const_reference operator[](key_type& x) const{return map[x];}; //TODO verify that there is no const version of operator[]

    /* Modifiers */
    pair<iterator,bool> insert(const value_type& x){return insert(x);};
    iterator insert(iterator pos,const value_type& x){return map.insert(pos,x);};
    template <class InputIterator> void insert(InputIterator first,InputIterator last){map.insert(first,last);};
    iterator erase(iterator pos){return map.erase(pos);};
    size_type erase( const key_type& x){return map.erase(x);};
    iterator erase(iterator first,iterator last){return map.erase(first,last);};
    void swap(SerializableVector& vec){
        throw std::exception("not implemented yet");
    };
    void clear(){map.clear();};

    /* Observers */

    key_compare key_comp() const{return map.key_comp();};
    value_compare value_comp() const{return map.value_comp();};

    /* Operations */

          iterator find(const key_type& x)      {return map.find(x);};
    const_iterator find(const key_type& x) const{return map.find(x);};
    size_type count(const key_type& x) const{return map.count(x);};
          iterator lower_bound(const key_type& x)      {return map.lower_bound(x);};
    const_iterator lower_bound(const key_type& x) const{return map.lower_bound(x);};
          iterator upper_bound(const key_type& x)      {return map.upper_bound(x);};
    const_iterator upper_bound(const key_type& x) const{return map.upper_bound(x);};
    pair<      iterator,      iterator> equal_range(const key_type& x)      {return map.equal_range(x);};
    pair<const_iterator,const_iterator> equal_range(const key_type& x) const{return map.equal_range(x);};

    /* Allocator */
    allocator_type get_allocator() const{return map.get_allocator();};

  protected:
    inline virtual void ToString(std::ostream& out) const
    {
        throw std::exception("not implemented yet");   
    };
    inline virtual void FromString(std::istream& in)
    {
        throw std::exception("not implemented yet");    
    };
};

#endif
