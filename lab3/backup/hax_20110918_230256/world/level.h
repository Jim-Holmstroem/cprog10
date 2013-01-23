#ifndef LEVEL_H
#define LEVEL_H
#include<iostream>
#include<vector>
#include<map>
#include "operation.h"
#ifndef DEBUG
#include "../ncurses/logger.h"
#endif

#include "../serialize/serializablevector.h"

namespace hax{
#ifndef DEBUG
    extern Logger log;
#endif

    class Area;
    class Character;
    class Container;
    class OperationVoid;

    class Level : public ISerializable{
      public:
        Level();
        Level(int); //specify number of areas
//        Level(const Level&);
        ~Level();

        void add(Area*);
        void add(Character*);
	void parse(std::vector<std::string>);

	//serialization
	virtual void ToString(std::ostream&) const;
	virtual void FromString(std::istream&);

      protected:
      private:
	void updatePlayers();
	void action();
	bool focus(std::string);
        void info();
	void help();
	void spawn();
	bool kill(std::string);

        SerializableVector<Area*> vec_area; //must be pointer since Area has pure virtual functions
	std::map<std::string, Operation*> opmap;
	std::vector<bool(Character::*)(void)> randomActions;
	std::map<std::string, std::string> levelHelp;
	std::map<std::string, std::string> charHelp;
        std::map<std::string, Character*> players; //global map with all characters, iterate over this and use action(), string is Character name
	Character* curChar;
	std::string curCharName;
    };

}
#endif