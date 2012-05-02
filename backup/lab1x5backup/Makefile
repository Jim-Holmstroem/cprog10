MOD = vector main

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

FLDR = lab1x5

CFLAG = -c -DDBOOL -Wall
LFLAG =

all:
	make lab1x5

lab1x5 : $(OBJ) Makefile
	g++ $(OBJ) -o lab1x5

vector.o : vector.cpp vector.h Makefile
	g++ $(CFLAG) vector.cpp

main.o : main.cpp main.h Makefile
	g++ $(CFLAG) main.cpp

clean:
	rm -f *.o lab1x5

run:
	./lab1x5
