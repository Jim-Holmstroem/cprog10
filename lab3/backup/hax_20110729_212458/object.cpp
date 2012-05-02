#include "object.h"

hax::Object::Object(){
}
/*hax::Object::Object(const Object& ob){
  weight = ob.weight;
  volume = ob.volume;
  price = ob.price;
  name = ob.name;
  descr = ob.descr;
  }*/
hax::Object::~Object(){
    std::cout << "~Object: " << description() << " deleted" << std::endl;
}

int hax::Object::getWeight() const{
    return weight;
}
int hax::Object::getVolume() const{
    return volume;
}
int hax::Object::getPrice() const{
    return price;
}
std::string hax::Object::getName() const{
    return name;
}
std::string hax::Object::description() const{
    if(descr != ""){
        return (descr +" "+ name);
    }else{
        return name;
    }
}

hax::Key::Key(){
    name = "key";
    descr = "orange";
}

hax::Coin::Coin(){
    name = "coin";
    weight = 0;
    volume = 1;
//om skapa en Coin så slumpa en derived Coin
//this = new derivedCoin; ????
//eller bara sätt descr och price samtidigt
}
hax::Coin::Coin(const Coin& copy){
    price = copy.price;
    descr = copy.descr;
}
hax::NdCoin::NdCoin(){
    price = 1000; //value of coin
    descr = "neodymium";
}
hax::CsCoin::CsCoin(){
    price = 500;
    descr = "cesium";
}
hax::PtCoin::PtCoin(){
    price = 100;
    descr = "platinum";
}
hax::AuCoin::AuCoin(){
//    weight = 3;
    price = 50;
    descr = "gold";
}
hax::AgCoin::AgCoin(){
//    weight = 2;
    price = 20;
    descr = "silver";
}
hax::CuCoin::CuCoin(){
//    weight = 1;
    price = 10;
    descr = "copper";
}
hax::FeCoin::FeCoin(){
    price = 5;
    descr = "iron";
}
hax::NiCoin::NiCoin(){
    price = 1;
    descr = "nickel";
}
