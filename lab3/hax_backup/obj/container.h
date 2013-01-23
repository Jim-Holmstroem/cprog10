#ifndef CONTAINER_H
#define CONTAINER_H
#include<vector>
#include<map>
#include<queue>
#include "object.h"

#include "../serialize/serializablevector.h"

namespace hax{

    class Container : public Object{
      public:
        Container();
//        Container(const Container&);
        ~Container(); //virtual by default since ~Object() is virtual

        Object* operator[](size_t i);

        virtual int hold_weight() const = 0;
        virtual int hold_volume() const = 0;
        bool add(Object* const); //TODO hur anv�nds dessa 2 fkner via Character?
        bool remove(Object* const);
        size_t size() const;
        Object* pop();
        bool empty() const;
	std::string contents() const;
	std::map<std::string, Container*> get_subContainers();
        Object* getObject(std::string);
        SerializableVector<hax::Object*>::iterator findObject(Object* const);
        bool hasObject(Object* const) const;

/*
        friend std::ostream& operator<<(std::ostream& out, const Container& c){
            SerializableVector<Object*>::const_iterator it = c.vec_obj.begin();
            while(it != c.vec_obj.end()){
                out << (*it)->description() << ", ";
                it++;
            }
            return out;
        };
*/

      protected:
        SerializableVector<Object*> vec_obj;
      private:
    };

    class Backpack : public Container{
      public:
        Backpack();
        int hold_weight() const;
        int hold_volume() const;
    };

/*    class Pokeball : public Container{ //TODO for the lulz, i.e. not important
      public:
      Pokeball(){
      name = "pokeball";
      }
//      Pokemon poke; //derived from Character
};
*/
}

#endif