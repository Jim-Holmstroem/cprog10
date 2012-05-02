#include "outdoor.h"
#include "human.h"

hax::Outdoor::Outdoor(){
}
hax::Outdoor::Outdoor(std::string name) : Area(name){
}
hax::Outdoor::Outdoor(const Outdoor& ou) : Area(ou){
}
hax::Outdoor::~Outdoor(){
}
void hax::Outdoor::enter(Character* ch){
    Area::enter(ch);
}
void hax::Outdoor::leave(Character* ch){
    Area::leave(ch);
}
bool hax::Outdoor::rest(Character* ch){
    int maxHp = ch->getmaxHp();
    int heal = maxHp/4;
    ch->curHp += heal;
    std::cout << ch->getName() << " healed " << heal << " HP" << std::endl;
    if(ch->curHp > maxHp){
        ch->curHp = maxHp;
    }
    return true;
}


hax::Forest::Forest(std::string name) : Outdoor(name){
    descr = "You are surrounded by trees.";
}
bool hax::Forest::rest(Character* ch){
    Outdoor::rest(ch);
/*    if(vec_char.size() > 1){ //other Chars here beside yourself
      vec_char[0]->fight(ch); //TODO slumpa chans och index
      }
*/
    Character* robber = new Barbarian("Robber"); //TODO slumpa chans att bli anfallen
    enter(robber);
    robber->fight(ch);
    return true;
}
hax::Character* hax::Forest::spawn(){
//list of random names
    Character* creep = new Barbarian("spawnedBarb");
    enter(creep);
    return(creep);
}
