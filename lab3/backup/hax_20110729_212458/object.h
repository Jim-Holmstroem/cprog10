#ifndef OBJECT_H
#define OBJECT_H
#include<iostream>

namespace hax{
    class Object{
      public:
        Object();
//        Object(const Object&);
        virtual ~Object(); //is virtual because when adding a Container to a Container and deleting will give segfault

// EXAMPLE
//    Object* ob1 = new Wallet();
//    Container* con1 = new Pocket("con1", 5);
//    Container* con2 = new Pocket("con2", 5);
/*      con1->add(ob1); //OBS adding a Container to a Container, ~Object() must be virtual otherwise delete con will give segfault
        con1->remove(ob1);
        con2->add(ob1);
        delete con1;
        delete con2;
*/

        int getWeight() const;
        int getVolume() const;
        int getPrice() const;
        std::string getName() const;
        std::string description() const;

      protected:
        int weight; //unit is kg
        int volume; //unit is liter
        int price; //unit is kr
        std::string name;
        std::string descr; //TODO set random description when creating object
      private:

    };

    class Key : public Object{
      public:
        Key();
    };

    class Coin : public Object{
      public:
        Coin();
        Coin(const Coin&);
    };
    class NdCoin : public Coin{ //Nd = neodymium
      public:
	NdCoin();
    };
    class CsCoin : public Coin{ //Cs = cesium
      public:
	CsCoin();
    };
    class PtCoin : public Coin{ //Pt = platinum
      public:
	PtCoin();
    };
    class AuCoin : public Coin{ //Au = gold
      public:
        AuCoin();
    };
    class AgCoin : public Coin{ //Ag = silver
      public:
        AgCoin();
    };
    class CuCoin : public Coin{ //Cu = copper
      public:
        CuCoin();
    };
    class FeCoin : public Coin{ //Fe = iron
      public:
	FeCoin();
    };
    class NiCoin : public Coin{ //Ni = nickel
      public:
	NiCoin();
    };
}
#endif
