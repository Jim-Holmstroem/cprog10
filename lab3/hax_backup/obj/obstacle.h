#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "object.h"

namespace hax{
    class Obstacle : public Object{
      public:
        Obstacle();
        Obstacle(void*); //TODO remove?
        ~Obstacle();
        int getPrice() const;
    };

    class Tree : public Obstacle{
      public:
        Tree(){
	    descr = "";
            name = "tree";
        }
    };

}
#endif
