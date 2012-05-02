#include "breakcontainer.h"

hax::BreakContainer::BreakContainer(){
}
hax::BreakContainer::~BreakContainer(){
}

int hax::BreakContainer::hold_weight() const{
    return maxWeight;
}
int hax::BreakContainer::hold_volume() const{
    return maxVolume;
}
bool hax::BreakContainer::add(Object* ob) const{
    if(Container::add(ob)){
	return true;
    }else{
	return false; //TODO fcn ptr breaks
    }
}
