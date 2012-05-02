#ifndef SPELLCASTER_H
#define SPELLCASTER_H
#include "character.h"

namespace hax{
    class Spellcaster : public Character{
      public:
	void magic() = 0;

      protected:
	int curMp; //magic points
	int maxMp;
    };
}
#endif
