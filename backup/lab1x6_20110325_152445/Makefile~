MOD = vector main

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

FLDR = lab1x6

OPTFLAG = -O3

CFLAG = -c -DDBOOL -Wall #-Wextra
LFLAG =

all:
	make lab1x6

lab1x6 : $(OBJ) Makefile
	g++ $(OBJ) -o lab1x6

vector.o : vector.cpp vector.h Makefile
	g++ $(CFLAG) vector.cpp

main.o : main.cpp main.h Makefile
	g++ $(CFLAG) main.cpp

clean:
	rm -f *.o lab1x6

run:
	./lab1x6
