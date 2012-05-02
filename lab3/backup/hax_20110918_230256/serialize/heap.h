#ifndef HEAP_H
#define HEAP_H

#include<iostream>
#include<string>
#include<vector>

#include<string>
#include"iserializable.h"
#include"serializablemap.h"

class Description : ISerializable
{
  protected:
    std::string UID;
    std::string type;

    inline virtual void ToString(std::ostream& out)
    {
        out << UID << ' ' << type << ' ';
    };
    inline virtual void FromString(std::istream& in)
    {
        in >> UID >> type; 
    };

  public:
    inline std::string GetUID() const
    {
        return UID;    
    };
    inline std::string GetType() const
    {
        return type;    
    };

};

class Heap : public SerializableMap<Description,ISerializable*> 
{





    
};

#endif
