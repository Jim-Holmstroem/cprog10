#include "route.h"
#include "character.h"
#include "area.h"
#include "container.h" //needed for inventory

hax::Route::Route(std::string n, Area* from, Area* to){
    name = n;
    thisArea = from;
    nextArea = to;
}
hax::Route::~Route(){
    std::cout << name << " route deleted" << std::endl;
}
std::string hax::Route::getName() const{
    return name;
}

hax::Door::Door(std::string name, Area* from, Area* to, Key* ke) : Route(name, from, to){
    match_key = ke;
}
std::string hax::Door::getType() const{
    return "door";
}
bool hax::Door::isBlocked(Character* const ch) const{
    if(ch->hasObject(match_key)){
        return false; //has key to unlock door so not blocked
    }else{
        return true;
    }
}
std::string hax::Door::blockMessage() const{
    return("The door requires a "+ match_key->description() +" to open!");
}
std::string hax::Door::passMessage() const{
    return("The door is opened with a "+ match_key->description() +".");
}

hax::Hatch::Hatch(std::string name, Area* from, Area* to) : Route(name, from, to){
    type = "hatch";
}
std::string hax::Hatch::getType() const{
    return "hatch";
}
bool hax::Hatch::isBlocked(Character* const ch) const{
    if(ch->totWeight() > 100){
        return false; //trapdoor opens if Character and the Objects he carry weighs enough
    }else{
        return true;
    }
}
std::string hax::Hatch::blockMessage() const{
    return("Get heavier!");
}
std::string hax::Hatch::passMessage() const{
    return("The hatch is released by your heavy weight.");
}
