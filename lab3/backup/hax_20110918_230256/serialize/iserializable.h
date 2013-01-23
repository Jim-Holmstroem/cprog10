#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include<string>
#include<sstream>
#include<map>
#include"parsehelper.h"

class ISerializable
{
  protected: 
    virtual void ToString(std::ostream& out) const = 0;
    virtual void FromString(std::istream& in) = 0;
//    virtual void ReLink(std::map<std::size_t,std::size_t>& converter) = 0;

//    virtual TYPE GetType() = 0;
    virtual std::string GetUID()
    {
	    std::stringstream uid;
        uid << this;
        return uid.str();
    };

  public:

    friend std::ostream& operator<<(std::ostream& out,const ISerializable& s)
    {
        out << "{ ";
        s.ToString(out);
        out << "}";
        return out;
    };
    friend std::istream& operator>>(std::istream& in,ISerializable& s)
    {
        checkToken(in,"{");
        s.FromString(in);
        checkToken(in,"}");
        return in;
    };
};

#endif