#include "obstacle.h"

hax::Obstacle::Obstacle(){
    weight = -1; //TODO
}
hax::Obstacle::Obstacle(void* vo){
//    criteria = vo;
}
hax::Obstacle::~Obstacle(){
    std::cout << "~Obstacle()" << std::endl;
}
int hax::Obstacle::getPrice() const{
    return 0;
}
