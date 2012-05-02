#ifndef BREAKCONTAINER_H
#define BREAKCONTAINER_H

namespace hax{
    class BreakContainer : public Container{
      public:
        BreakContainer();
        ~BreakContainer();
        virtual int hold_weight() const = 0;
        virtual int hold_volume() const = 0;
      private:
	int maxWeight;
	int maxVolume;
    };

    class Wallet : public BreakContainer, public Object { //supposed to contain in-game currency
      public:
        Wallet(){
            name = "wallet";

            const char* attr[] = { //attributes
                "shiny",
                "Hello Kitty",
                "old"
            };
            descr = "old";
//    descr = attr[random int]; TODO

        }
    };



}
