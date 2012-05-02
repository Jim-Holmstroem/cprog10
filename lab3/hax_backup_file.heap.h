#ifndef HEAP_H
#define HEAP_H

#include<iostream>
#include<string>
#include<vector>

#include<string>
#include<sstream>

#include"iserializable.h"
#include"serializablemap.h"

namespace hax
{
    class Description : ISerializable
    {
      protected:
        std::string UID;
        std::string type;

        virtual void ToString(std::ostream& out) const
        {
            out << UID << ' ' << type << ' ';
        };
        virtual void FromString(std::istream& in)
        {
            in >> UID >> type;
        };

      Description(std::string id,std::string tp)
          :UID(id)
            ,type(tp)
        {};

      public:

        inline std::string GetUID() const
        {
            return UID;
        };
        inline std::string GetType() const
        {
            return type;
        };
        static Description GetDescription(const ISerializable& obj)
        {
            return Description(obj.GetUID(),obj.GetType());
        };

        bool operator<(const Description& d) const
        {
            return this->UID.compare(d.UID)<0;
        };

    };

    class Heap : public SerializableMap<Description,ISerializable*>
    {
      public:

        virtual void ElementToString(std::ostream& out, const value_type& elem) const
        {
            out << elem.first << ' ' << *elem.second << ' ';
        };
        virtual void ElementFromString(std::istream& in)
        {
            key_type keyData;
            in >> keyData;
            value_type elem(keyData, mapped_type());
            in >> elem.second;

            /*TODO ADD CODE HERE TO HANDLE HEAP-MAPPING*/

            content.insert(elem);
        };
        virtual std::string GetType()
        {
            return "Heap"; //NOTE, will never be used
        };
      private:
        std::map<size_t,ISerializable*> convert;

    };

}

#endif
