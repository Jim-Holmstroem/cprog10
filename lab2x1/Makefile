#
#	Makefile for lab2
#

MOD = date gregorian julian calendar kattistime main

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

CFLAG = -c -DDEBUG -Wall
LFLAG =

CTEST = -DCAL # recompiles main.cpp if Makefile is updated

lab2 : $(OBJ)
	g++ $(OBJ) -o lab2x1
	#rm -f calendar.o #TODO, fixa fulhaxet, den länker ngt fel, den uppdateras inte även fast calendar uppdateras

main.o : main.cpp main.h Makefile
	g++ $(CFLAG) $(CTEST) main.cpp

kattistime.o : kattistime.cpp kattistime.h
	g++ $(CFLAG) $(CTEST) kattistime.cpp

gregorian.o : gregorian.cpp gregorian.h date.h
	g++ $(CFLAG) $(CTEST) gregorian.cpp

julian.o : julian.cpp julian.h date.h
	g++ $(CFLAG) $(CTEST) julian.cpp

#fuck funkar inte heller :(
calendar.o : $(SRC) $(HDR)
	g++ $(CFLAG) $(CTEST) calendar.cpp

date.o : date.cpp date.h
	g++ $(CFLAG) $(CTEST) date.cpp

clean:
	rm -f *.o lab2x1

run:
	./lab2x1
	rm -f *.o lab2x1 #fucked up but gotta do it man
