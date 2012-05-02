MOD = game logger level area indoor outdoor route road character hero human undead object container obstacle sprite multisprite

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

FLDR = hax

PRGM = hax

CFLAG = -c -Wall -g
LFLAG = -lncurses -lmenu


all:
	make $(PRGM)

hax: $(OBJ) Makefile
	g++ $(OBJ) $(LFLAG) -o $(PRGM)

game.o: game.cpp game.h Makefile
	g++ $(CFLAG) game.cpp -o game.o

logger.o: logger.cpp logger.h Makefile
	g++ $(CFLAG) logger.cpp -o logger.o 

sprite.o: sprite.cpp sprite.h Makefile
	g++ $(CFLAG) sprite.cpp -o sprite.o

multisprite.o: multisprite.cpp multisprite.h Makefile
	g++ $(CFLAG) multisprite.cpp -o multisprite.o

obstacle.o: obstacle.cpp obstacle.h Makefile
	g++ $(CFLAG) obstacle.cpp -o obstacle.o

container.o: container.cpp container.h Makefile
	g++ $(CFLAG) container.cpp -o container.o

object.o: object.cpp object.h Makefile
	g++ $(CFLAG) object.cpp -o object.o

road.o: road.cpp road.h Makefile
	g++ $(CFLAG) road.cpp -o road.o

route.o: route.cpp route.h Makefile
	g++ $(CFLAG) route.cpp -o route.o

outdoor.o: outdoor.cpp outdoor.h Makefile
	g++ $(CFLAG) outdoor.cpp -o outdoor.o

indoor.o: indoor.cpp indoor.h Makefile
	g++ $(CFLAG) indoor.cpp -o indoor.o

area.o: area.cpp area.h Makefile
	g++ $(CFLAG) area.cpp -o area.o

level.o: level.cpp level.h Makefile
	g++ $(CFLAG) level.cpp -o level.o

undead.o: undead.cpp undead.h Makefile
	g++ $(CFLAG) undead.cpp -o undead.o

human.o: human.cpp human.h Makefile
	g++ $(CFLAG) human.cpp -o human.o

hero.o: hero.cpp hero.h Makefile
	g++ $(CFLAG) hero.cpp -o hero.o

character.o: character.cpp character.h Makefile
	g++ $(CFLAG) character.cpp -o character.o

clean:
	rm -f $(OBJ) hax

run:
	./hax
