#
#	Makefile for lab2
#

MOD = date gregorian julian calendar kattistime datetest

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

CFLAG = -c -DDEBUG -Wall
LFLAG =

CTEST = -DCAL # recompiles main.cpp if Makefile is updated

lab2 : $(OBJ) 
	g++ $(OBJ) -o lab2
#rm -f calendar.o #TODO, fixa fulhaxet, den länker ngt fel, den uppdateras inte även fast calendar uppdateras

test1: $(OBJ) cprog09lab22a.o
	g++ $(OBJ) cprog09lab22a.o -o test1

cprog09lab22a.o : cprog09lab22a.cpp
	g++ $(CFLAG) cprog09lab22a.cpp	

datetest.o : datetest.cpp Makefile
	g++ $(CFLAG) datetest.cpp

#main.o : main.cpp main.h Makefile
#	g++ $(CFLAG) $(CTEST) main.cpp

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
	rm -f *.o lab2

run:
	./lab2
	rm -f *.o lab2 #fucked up but gotta do it man

send1:
	./submit.py -f -p oldkattis:cprog09lab22a cprog09lab22a.cpp date.cpp date.h julian.cpp julian.h kattistime.cpp kattistime.h

send2:
	./submit.py -f -p oldkattis:cprog09lab22b cprog09lab22b.cpp date.cpp date.h gregorian.cpp gregorian.h kattistime.cpp kattistime.h

send3:
	./submit.py -f -p oldkattis:cprog09lab22c cprog09lab22c.cpp date.cpp date.h julian.cpp julian.h gregorian.cpp gregorian.h kattistime.cpp kattistime.h

send4:
	./submit.py -f -p oldkattis:cprog09lab23 cprog09lab23.cpp date.cpp date.h julian.cpp julian.h gregorian.cpp gregorian.h calendar.h kattistime.cpp kattistime.h
