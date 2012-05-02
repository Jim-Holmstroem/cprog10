#ifndef CONTAINER_H
#define CONTAINER_H
#include<vector>
#include<cstdlib>
#include "object.h"

#define len(a) ( sizeof(a) / sizeof(a[0]) )

namespace hax{

    class Container : public Object{
      public:
        Container();
//        Container(const Container&);
        ~Container(); //virtual by default since ~Object() is virtual

        Object* operator[](size_t i);

        virtual int hold_weight() const = 0;
        virtual int hold_volume() const = 0;
        bool add(Object*); //TODO hur används dessa 2 fkner via Character?
        bool remove(Object*);
        size_t size() const;
        Object* pop();
        bool empty() const;
        Object* getObject(std::string);
        std::vector<hax::Object*>::iterator findObject(Object*);
        bool hasObject(Object*) const;

        friend std::ostream& operator<<(std::ostream& out, Container& c){
            std::vector<Object*>::iterator it = c.vec_obj.begin();
            while(it != c.vec_obj.end()){
                out << (*it)->description() << ", ";
                it++;
            }
            return out;
        };

      protected:
        std::vector<Object*> vec_obj;
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
