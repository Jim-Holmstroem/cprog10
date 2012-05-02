#ifndef AREA_H
#define AREA_H
#include<vector>
#include<map>
#include "route.h"
#include "container.h"
#ifndef DEBUG
#include "logger.h"
#endif

namespace hax{
#ifndef DEBUG
    extern Logger log;
#endif

    typedef std::map<std::string, Route*> MapRoute;

    class Character; //forward declaration
//    class Object;

    class Area{
      public:
        Area();
        Area(std::string);
        Area(const Area&);
        virtual ~Area();

//        Area& operator=(const Area&);

        std::string getName() const;
        std::vector<Character*> chars() const; //TODO remove? currently used by level.cpp

        Area& neighbor(const Route&) const;
        std::string directions() const;
        std::string description() const;

        void addRoute(Route*);
        virtual void enter(Character*); //TODO return type? should Area be pure virtual base class?
        virtual void leave(Character* const); //TODO return type?
        bool pick_up(Object* const);
        bool drop(Object* const);
        virtual bool buy(Object* const);
        virtual Object* sell(const int, std::string);
        virtual bool rest(Character*) = 0;
        virtual Character* spawn() = 0;

        Character* getChar(std::string);
        std::vector<Character*>::iterator findChar(Character*);
        bool hasChar(Character* const) const;
        Object* getObject(std::string);
        std::vector<Object*>::iterator findObject(Object*);
        bool hasObject(Object* const) const;

//      protected: TODO
        MapRoute exits;

      protected:
        std::vector<Character*> vec_char;
//      std::vector<Character*> vec_creep; //for characters blocking a road, or other static enemies
        std::string name;
        std::string descr; //description

	//definition of Ground put in protected because class Shop needs it
        class Ground : public Container{ //like a big reservoir
          public:
            Ground();
	    Ground(std::string);
            int hold_weight() const;
            int hold_volume() const;
        };

      private:
        Ground* gnd;
    };
}
#endif
