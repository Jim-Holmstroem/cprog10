#ifndef CONTAINER_H
#define CONTAINER_H
#include<vector>
#include "object.h"

namespace hax{
    template<typename T>
      class Container : public Object{
      public:
//	typedef std::vector<T*>::iterator;

        Container();
//        Container(const Container&);
        ~Container(); //virtual by default since ~Object() is virtual

        T* operator[](size_t i);

        virtual int hold_weight() const = 0;
        virtual int hold_volume() const = 0;
        bool add(T*); //TODO hur används dessa 2 fkner via Character?
        bool remove(T*);
        size_t size() const;
        typename std::vector<T*>::iterator findObject(T*);
        typename std::vector<T*>::iterator findObject(std::string);
        bool hasObject(T*);
        T* pop();
        bool empty() const;


      protected:
        std::vector<T*> vec_obj;
      private:

    };

    class Wallet : public Container<Coin>{ //supposed to contain in-game currency
      public:
        Wallet();
        Wallet* operator+=(const int);
        Wallet* operator-=(const int);
        int hold_weight() const;
        int hold_volume() const;
    };

//OBS! Both Pocket and Ground are private in character.h resp area.h so they cannot be added to another container from outside
    class Pocket : public Container<Object>{
      public:
        Pocket();
        Pocket(std::string, unsigned int);
        int hold_weight() const;
        int hold_volume() const;
      private:
        unsigned int maxSize;
    };
    class Ground : public Container<Object>{ //like a big reservoir
      public:
        Ground(std::string);
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

template<typename T>
hax::Container<T>::Container(){
}
/*hax::Container::Container(const Container& co) : Object(co){
  vec_obj = co.vec_obj;
  }*/
template<typename T>
hax::Container<T>::~Container(){
    std::cout << "~Container: emptying " << description() << "..." << std::endl;
    for(size_t i=0; i<vec_obj.size(); i++){
        delete vec_obj[i];
    }
    vec_obj.clear();
}
template<typename T>
T* hax::Container<T>::operator[](size_t i){ //TODO const version?
    return vec_obj[i];
}
template<typename T>
bool hax::Container<T>::add(T* ob){
    if(weight+ob->getWeight() > hold_weight() || volume+ob->getVolume() > hold_volume()){
        return false;
    }else{
        vec_obj.push_back(ob);
        weight += ob->getWeight();
        volume += ob->getVolume();
        price += ob->getPrice();
        return true;
    }
}
template<typename T>
bool hax::Container<T>::remove(T* ob){
    if( findObject(ob) != vec_obj.end() ){
        vec_obj.erase(findObject(ob));
        weight -= ob->getWeight();
        volume -= ob->getVolume();
        price -= ob->getPrice();
        return true;
    }else{
        return false;
    }
}
template<typename T>
size_t hax::Container<T>::size() const{
    return vec_obj.size();
}
template<typename T>
T* hax::Container<T>::pop(){ //TODO not used
    T* lastObj = vec_obj.back();
    vec_obj.pop_back();
    return lastObj;
}
template<typename T>
bool hax::Container<T>::empty() const{
    return vec_obj.empty();
}
template<typename T>
typename std::vector<hax::Object*>::iterator hax::Container<T>::findObject(T* ob){
    std::vector<Object*>::iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if(*it == ob){
            return it;
        }
    }
    return it; //not found, return vec_obj.end()
}
template<typename T>
typename std::vector<hax::Object*>::iterator hax::Container<T>::findObject(std::string objName){
    std::vector<Object*>::iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if((*it)->description() == objName){
            return it;
        }
    }
    return it; //not found, return vec_obj.end()
}
template<typename T>
bool hax::Container<T>::hasObject(T* ob){
    std::vector<Object*>::iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if(*it == ob){
            return true;
        }
    }
    return false;
}



hax::Wallet::Wallet(){
    name = "wallet";
    weight = 1;
    volume = 1;
    price = 0;
/*
  const char* attr[] = { //attributes
  "shiny",
  "Hello Kitty",
  "old"
  };
*/
    descr = "old";
//    descr = attr[random int]; TODO

}
hax::Wallet* hax::Wallet::operator+=(const int profit){ //add Coins equal to int value
    *this -= (-profit);
    return this;
}
hax::Wallet* hax::Wallet::operator-=(const int cost){ //TODO return NULL first if cost > this->getPrice() ???
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
    return this;
}
int hax::Wallet::hold_weight() const{
    return 1;
}
int hax::Wallet::hold_volume() const{
    return 1000;
}

hax::Pocket::Pocket(){
    name = "pocket";
    descr = "nobody's";
}
hax::Pocket::Pocket(std::string owner, unsigned int maxSize){
    name = "pocket";
    descr = owner +"'s";
    weight = 1;
    volume = 1;
    this->maxSize = maxSize;
}
int hax::Pocket::hold_weight() const{ //TODO hold_size() instead
    return 100;
}
int hax::Pocket::hold_volume() const{
    return 100;
}

hax::Ground::Ground(std::string areaName){
    name = "ground";
//          weight = -1;
//          volume = -1;
    descr = areaName;
}
int hax::Ground::hold_weight() const{
    return 10000;
}
int hax::Ground::hold_volume() const{
    return 10000;
}



#endif
