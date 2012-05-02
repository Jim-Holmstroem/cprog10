#ifndef INDOOR_H
#define INDOOR_H
#include "area.h"

namespace hax{

    class Ground;

    class Indoor : public Area{
      public:
        Indoor();
        Indoor(std::string);
        Indoor(const Indoor&);
        ~Indoor();

//        Indoor& operator=(const Indoor&);
        void enter(Character*);
        void leave(Character*);
        virtual bool rest(Character*);
	virtual Character* spawn();

      protected:
      private:
    };

    class Castle : public Indoor{
      public:
        Castle();
        Castle(std::string);
    };

    class School : public Indoor{
      public:
        School();
        School(std::string);
    };
    class Shop : public Indoor{
      public:
	Shop(std::string);
	virtual bool buy(Object*); // buy/sell operates like pick_up/drop
	virtual Object* sell(const int, std::string);

      private:
	Ground* goods; //items for sale
    };
}
#endif
