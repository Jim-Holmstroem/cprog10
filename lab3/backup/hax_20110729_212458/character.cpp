#include "character.h"
#include "area.h" //included here since there are only Area pointers
#include "object.h" //same reason as above
#include "route.h"

hax::Character::Character(){
    name = "defaultName";
    curArea = NULL;
    inventory = new Pocket();
}
hax::Character::Character(std::string n){
    name = n;
    curArea = NULL;
    inventory = new Pocket(name, 5); //TODO different chars can have different sized pockets
}
hax::Character::Character(const Character& ch){
    std::cout <<"Character::copy constructor"<< std::endl;
    curArea = ch.curArea;
    align = ch.align;
    //race = ch.getType();
    name = ch.name;
    curHp = ch.curHp;
    maxHp = ch.maxHp;
    strength = ch.strength;
//    inventory = new Pocket(ch.inventory); //TODO ok?
}
hax::Character::~Character(){
    std::ostringstream oss;
    oss <<"~Character: "<< name <<" died"<< std::endl;
#ifdef DEBUG
    std::cout << oss.str();
#else
    hax::log.write(oss.str()); //TODO if ncurses unloads before last characters is cleaned then segfault
#endif

    if(curArea != NULL){ //if just create this Object without using enter() then curArea will be NULL, so delete causes seg fault

        //try to drop the carried objects, i.e. loot from dead character
        for(size_t i=0; i < inventory->size(); ){
            if(!drop( (*inventory)[i]->description() )){
                i++;
            }
        }
        delete inventory; //the objects not dropped will be deleted in ~Container()
        curArea->leave(this); //remove the pointer to this from Area::vector<Character*>
    }
}

/*hax::Character& hax::Character::operator=(const Character& ch){
  return *this;
  };*/

bool hax::Character::alignment() const{
    return align;
}
std::string hax::Character::getName() const{
    return name;
}
int hax::Character::getcurHp() const{
    return curHp;
}
int hax::Character::getmaxHp() const{
    return maxHp;
}
int hax::Character::getStr() const{
    return strength;
}
int hax::Character::totWeight() const{
    return(this->weight + inventory->getWeight());
}
bool hax::Character::hasObject(Object* const ob) const{
    return inventory->hasObject(ob);
}
void hax::Character::view_stats(){
#ifdef DEBUG
    std::cout << name <<" the "<< getType() << std::endl;
    std::cout <<"HP: "<< curHp <<"/"<< maxHp << std::endl;
    std::cout <<"Strength: "<< strength << std::endl;
    std::cout <<"Weight: "<< totWeight() << std::endl;
#else
    hax::log.write(name +" the "+ getType());
    std::ostringstream oss;
    oss <<"HP: "<< curHp <<"/"<< maxHp;
    hax::log.write(oss.str());
    oss.str(""); //clear stream
    oss <<"Strength: "<< strength;
    hax::log.write(oss.str());
    oss.str("");
    oss <<"Weight: "<< totWeight();
    hax::log.write(oss.str());
#endif
}
void hax::Character::view_area(){
#ifdef DEBUG
    std::cout << curArea->description() << std::endl;
#else
    hax::log.write(curArea->description());
#endif
}
/*void hax::Character::look(std::string routeName){ //TODO
  std::cout << curArea->maptoRoute[routeName]->view() << std::endl;
  }*/
void hax::Character::view_inventory(){
    std::cout << name <<"'s inventory: "<< *inventory << std::endl;
    std::cout <<"Total money: "<< myWallet.getPrice() <<" h@x"<< std::endl;
}
bool hax::Character::go(std::string routeName){
    if(curArea != NULL){
        if( curArea->exits.find(routeName) != curArea->exits.end() ){
            return go( *(curArea->exits[routeName]) );
        }else{
            std::cout <<"Route does not exist!"<< std::endl;
            return false;
        }
    }else{
        std::cout <<"curArea is not set!"<< std::endl;
        return false;
    }
}
bool hax::Character::go(const Route& ro){ //TODO Route is passed by reference, what is the difference with pass by pointer? will virtual calls work?
    if(ro.isBlocked(this)){
        std::cout << this->name <<" is blocked when trying to go to "<< ro.nextArea->getName() <<" through a "<< ro.getType() <<". "<< ro.blockMessage() << std::endl;
        return false;
    }else{
        curArea->leave(this);
        curArea->neighbor(ro).enter(this);
        std::cout << name <<" enters "<< curArea->getName() <<" through a "<< ro.getType() <<". "<< ro.passMessage() << std::endl;
        return true;
    }
}
bool hax::Character::go_random(){
    unsigned int routeNr = rand() % curArea->exits.size();
    MapRoute::const_iterator it = curArea->exits.begin();
    for(unsigned int i=0; i<routeNr; i++){
        it++;
    }
    return(this->go( *(it->second) ));
}
bool hax::Character::fight(std::string name){
    Character* enemy = curArea->getChar(name); //is NULL if not found
    if(enemy == NULL){
        std::cout <<"No character called "<< name <<" in this area."<< std::endl;
        return false;
    }else if(this == enemy){ //protection against fighting myself
        std::cout <<"You cannot fight yourself!"<< std::endl;
        return false;
    }else{
        fight(enemy);
        return true;
    }
}
void hax::Character::fight(Character* ch){
    attack(ch);
//TODO
/*        char msg[512];
          sprintf(msg,"%s has %iHP left",ch->name.c_str(),ch->curHp);
          hax::log.write(msg);
*/
    std::cout<< ch->name <<" has " << ch->curHp <<" HP left."<< std::endl << std::endl;
    if(ch->curHp <= 0){
        return;
//        delete ch; //character is killed
//        ch = NULL;
    }else{
        ch->fight(this); //continue if other character is not killed
    }
}
bool hax::Character::fight_random(){
    const std::vector<Character*> charsInArea = curArea->chars();
    unsigned int totChars = charsInArea.size();
    if(totChars == 1){ //no one to fight
        return false;
    }
    Character* enemy = charsInArea[rand() % totChars];
    while(this == enemy){ //protection against fighting myself
        enemy = charsInArea[rand() % totChars];
    }
    fight(enemy);
    return true;
}
bool hax::Character::pick_up(std::string objName){
    Object* ob = curArea->getObject(objName);
    if(ob != NULL){
        if(ob->getWeight() < 0){ //Obstacle should not be picked up and has weight = -1
            std::cout <<"Only Chuck Norris can pick up Obstacles!"<< std::endl;
            return false;
        }else if(curArea->drop(ob)){ //picked up, add to correct container (no need to consider this in drop since no need to drop money)
            if(ob->getName() == "coin"){
                myWallet.add(ob);
            }else{
                inventory->add(ob);
            }
            std::cout << this->name <<" picked up "<< ob->description() <<"."<< std::endl;
            return true;
        }else{
            std::cout << objName <<" cannot be picked up for some reason."<< std::endl;
            return false;
        }
    }else{ //curArea does not have this object
        std::cout << objName <<" not found in this area."<< std::endl;
        return false;
    }
}
bool hax::Character::drop(std::string objName){
    Object* ob = inventory->getObject(objName);
    if(ob != NULL){
        if( curArea->pick_up(ob) ){
            inventory->remove(ob); //remove from vector<Object*>, i.e. this Character no longer knows about ob
            std::cout << name <<" dropped "<< ob->description() <<"."<< std::endl;
            return true;
        }else{
            std::cout <<"Cannot drop "<< objName <<" here."<< std::endl;
            return false; //cannot drop object in this Area
        }
    }else{ //this character does not have this object
        std::cout << name <<" does not have "<< objName <<"."<< std::endl;
        return false;
    }
}
bool hax::Character::buy(std::string objName){
    Object* purchase = curArea->sell(myWallet.getPrice(), objName);
    if(purchase != NULL){
        inventory->add(purchase);
        myWallet -= purchase->getPrice();
        std::cout <<"You bought "<< objName <<" for "<< purchase->getPrice() <<" h@x."<< std::endl;
        return true;
    }else{
        return false;
    }
}
bool hax::Character::sell(std::string objName){
    Object* sale = inventory->getObject(objName);
    if(sale == NULL){
        std::cout <<"You do not have this item."<< std::endl;
        return false;
    }else if(!curArea->buy(sale)){
        std::cout <<"You cannot sell anything here."<< std::endl;
        return false;
    }else{ //Shop bought your item since buy was called
        inventory->remove(sale);
        myWallet += sale->getPrice();
        std::cout <<"You sold "<< objName <<"."<< std::endl;
        return true;
    }
}
bool hax::Character::rest(){
    return(curArea->rest(this));
}
/*
  void hax::Character::check(Object* ob){ //TODO
  if( curArea->hasObject(ob) ){
  Object* interact = *(curArea->findObject(ob));
  interact->check(*(this->inventory));
  }
  }
*/

hax::Character::Wallet::Wallet(){
    name = "wallet";
    descr = "";
    weight = 1;
    volume = 1;
    price = 0;
}
hax::Character::Wallet& hax::Character::Wallet::operator+=(const int profit){ //add Coins equal to int value
    *this -= (-profit);
    return *this;
}
hax::Character::Wallet& hax::Character::Wallet::operator-=(const int cost){ //TODO return NULL first if cost > this->getPrice() ???
//pop coins until have enough then create new Coins for växel
    int payment = 0;
    while(payment < cost){
        Object* mynt = vec_obj.front(); //TODO change to Coin* when implement template
        this->remove(mynt);
        payment += mynt->getPrice();
        delete mynt; //give to shopkeeper, gone forever
    }
    int change = payment - cost;
/*            for(int i=0; i<change; i++){
              this->add(new CuCoin());
              }
*/
//          Coin moneyValue[] = {CuCoin(), FeCoin(), NiCoin()}; //TODO get sizeof and use in while loop
    std::vector<Coin> moneyValue;
    moneyValue.push_back(CuCoin());
    moneyValue.push_back(FeCoin());
    moneyValue.push_back(NiCoin());
//          int i=0;
//          while(moneyValue[i] != NULL){ //TODO safe to do this?
    for(size_t i=0; i<moneyValue.size(); i++){
        int numCoin = change / moneyValue[i].getPrice(); //truncated division
        change -= numCoin * moneyValue[i].getPrice();
        for(int j=0; j<numCoin; j++){
            this->add(new Coin(moneyValue[i]));
        }
//              i++;
    }
/*          int numAuCoin = change/10;
            int leftover = change - numAuCoin*10;
            int numAgCoin = change/5;
            leftover = change - numAgCoin*5;
            int numCuCoin = leftover;
*/
    return *this;
}
int hax::Character::Wallet::hold_weight() const{
    return 1;
}
int hax::Character::Wallet::hold_volume() const{
    return 1000;
}

hax::Character::Pocket::Pocket(){
    name = "pocket";
    descr = "nobody's";
}
hax::Character::Pocket::Pocket(std::string owner, unsigned int maxSize){
    name = "pocket";
    descr = owner +"'s";
    weight = 1;
    volume = 1;
    this->maxSize = maxSize;
}
int hax::Character::Pocket::hold_weight() const{ //TODO hold_size() instead
    return 100;
}
int hax::Character::Pocket::hold_volume() const{
    return 100;
}
