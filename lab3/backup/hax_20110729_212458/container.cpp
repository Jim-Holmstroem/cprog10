#include "container.h"

hax::Container::Container(){
}
/*hax::Container::Container(const Container& co) : Object(co){
  vec_obj = co.vec_obj;
  }*/
hax::Container::~Container(){
    std::cout << "~Container: emptying " << description() << "..." << std::endl;
    for(size_t i=0; i<vec_obj.size(); i++){
        delete vec_obj[i];
    }
    vec_obj.clear();
}

hax::Object* hax::Container::operator[](size_t i){ //TODO const version?
    return vec_obj[i];
}

bool hax::Container::add(Object* ob){
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
bool hax::Container::remove(Object* ob){
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
size_t hax::Container::size() const{
    return vec_obj.size();
}
hax::Object* hax::Container::pop(){ //TODO not used
    Object* lastObj = vec_obj.back();
    vec_obj.pop_back();
    return lastObj;
}
bool hax::Container::empty() const{
    return vec_obj.empty();
}
std::vector<hax::Object*>::iterator hax::Container::findObject(Object* ob){
    std::vector<Object*>::iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if(*it == ob){
            return it;
        }
    }
    return it; //not found, return vec_obj.end()
}
hax::Object* hax::Container::getObject(std::string objName){
    std::vector<Object*>::iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if((*it)->description() == objName){
            return *it;
        }
    }
    return NULL; //not found, return NULL
}
bool hax::Container::hasObject(Object* ob) const{
    std::vector<Object*>::const_iterator it;
    for(it = vec_obj.begin(); it != vec_obj.end(); it++){
        if(*it == ob){
            return true;
        }
    }
    return false;
}

hax::Backpack::Backpack(){
    name = "backpack";
    weight = 1;
    volume = 2;
    price = 50;
    const char* attr[] = { //attributes
        "gangsta",
        "Hello Kitty",
        "old"
    };
    descr = attr[rand() % len(attr)];
}
int hax::Backpack::hold_weight() const{
    return 30;
}
int hax::Backpack::hold_volume() const{
    return 10;
}
