#ifndef LEVEL_H
#define LEVEL_H
#include<iostream>
#include<vector>
#include<map>
#include "operation.h"
#ifndef DEBUG
#include "logger.h"
#endif

namespace hax{
#ifndef DEBUG
    extern Logger log;
#endif

    class Area;
    class Character;
    class Container;
    class OperationVoid;

    class Level{
      public:
        Level();
        Level(int); //specify number of areas
//        Level(const Level&);
        ~Level();

        void add(Area*);
        void add(Character*);
	void parse(std::vector<std::string>);

      protected:
      private:
	void action();
	bool focus(std::string);
        void info();
	void help();
	void spawn();
	bool kill(std::string);
	void updatePlayers();

        std::vector<Area*> vec_area; //must be pointer since Area has pure virtual fcns
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
