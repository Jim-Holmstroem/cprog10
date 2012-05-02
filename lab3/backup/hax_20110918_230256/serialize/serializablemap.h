#ifndef SERIALIZABLEMAP_H
#define SERIALIZABLEMAP_H

#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<exception>
#include"parsehelper.h"
#include"iserializablecontainer.h"

template < class Key,
           class T,
           class Compare = std::less<Key>,
           class Allocator = std::allocator<std::pair<const Key,T> >
         >
    class SerializableMap: public ISerializableContainer< std::pair<const Key,T> >
{
  protected:
    std::map<Key,T,Compare,Allocator> content;

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
    typedef typename std::map<Key,T,Compare,Allocator>::const_reverse_iterator const_reverse_iterator;

    explicit SerializableMap(const Compare& comp = Compare(),const Allocator& alloc = Allocator()):content(comp,alloc){};
    template <class InputIterator> SerializableMap(InputIterator first,InputIterator last,const Compare& comp = Compare(),const Allocator& alloc = Allocator()):content(first,last,comp,alloc){};
    SerializableMap(const SerializableMap& x)
    {
        this->content = x.content;
    };
    SerializableMap& operator=(const SerializableMap& x)
    {
        this->content = x.content;
        return *this;
    };
    ~SerializableMap(){};

    //TODO inline the hole shebang

    /* Iterators */

          iterator begin()      {return content.begin();};
    const_iterator begin() const{return content.begin();};
          iterator end()      {return content.end();};
    const_iterator end() const{return content.end();};
          reverse_iterator rbegin()      {return content.rbegin();};
    const_reverse_iterator rbegin() const{return content.rbegin();};
          reverse_iterator rend()      {return content.rend();};
    const_reverse_iterator rend() const{return content.rend();};

    /* Capacity */
    size_type size() const{return content.size();};
    size_type max_size() const{return content.max_size();};
    bool empty() const{return content.empty();};

    /* Element Access */
    mapped_type operator[](const key_type& x)      {return content[x];};
    //const mapped_type operator[](key_type& x) const{return content[x];}; //TODO verify that there is no const version of operator[]

    /* Modifiers */
    std::pair<iterator,bool> insert(const value_type& x){return content.insert(x);};
    iterator insert(iterator pos,const value_type& x){return content.insert(pos,x);};
    template <class InputIterator> void insert(InputIterator first,InputIterator last){content.insert(first,last);};
    iterator erase(iterator pos){return content.erase(pos);};
    size_type erase( const key_type& x){return content.erase(x);};
    iterator erase(iterator first,iterator last){return content.erase(first,last);};
    void swap(SerializableMap& map){
        content.swap(map.content());
    };
    void clear(){content.clear();};

    /* Observers */
    key_compare key_comp() const{return content.key_comp();};
    value_compare value_comp() const{return content.value_comp();};

    /* Operations */
          iterator find(const key_type& x)      {return content.find(x);};
    const_iterator find(const key_type& x) const{return content.find(x);};
    size_type count(const key_type& x) const{return content.count(x);};
          iterator lower_bound(const key_type& x)      {return content.lower_bound(x);};
    const_iterator lower_bound(const key_type& x) const{return content.lower_bound(x);};
          iterator upper_bound(const key_type& x)      {return content.upper_bound(x);};
    const_iterator upper_bound(const key_type& x) const{return content.upper_bound(x);};
    std::pair<      iterator,      iterator> equal_range(const key_type& x)      {return content.equal_range(x);};
    std::pair<const_iterator,const_iterator> equal_range(const key_type& x) const{return content.equal_range(x);};

    /* Allocator */
    allocator_type get_allocator() const{return content.get_allocator();};


    /* Pure virtual functions from ISerializableContainer */
    virtual void ElementToString(std::ostream& out, const value_type& elem) const
    {
        out << elem.first << ' ' << *(elem.second) << ' ';
    };
    virtual void ElementFromString(std::istream& in)
    {
	//TODO beware too specialized function
	std::string keyData; //have to store a temp string since std::pair has const Key
	std::getline(in, keyData, ' ');
        value_type elem(keyData, mapped_type());
        in >> *(elem.second);
        content.insert(elem);
    };
    virtual void ToString(std::ostream& out) const
    {
        for(const_iterator it = content.begin(); it!=content.end(); ++it)
        {
            ElementToString(out,*it);
            if(it!=(--content.end()))
            {
                out << ", ";
            }
        }
    };
    virtual void FromString(std::istream& in)
    {
        while(in.peek()==',')
        {
            ElementFromString(in);
        }
    };

};
#endif
