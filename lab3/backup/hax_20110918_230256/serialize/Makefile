MOD = test iserializable iserializablecontainer serializablemap serializablevector parsehelper

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

EXE = test_serialize

CXX = g++

CFLAG = -c -Wall -Wextra #-ftabstop=4 
LFLAG =

$(EXE): $(OBJ)
	$(CXX) $^ -o $@ $(LFLAG)

$(OBJ) : $(SRC) $(HDR)
	$(CXX) $< $(CFLAG) -o $@

#test.o : test.cpp test.h Makefile
#	g++ $(CFLAG) test.cpp

#serializablemap.o : serializablemap.cpp serializablemap.h Makefile
#	g++ $(CFLAG) serializablemap.cpp

#serializablevector.o : serializablevector.cpp serializablevector.h Makefile
#	g++ $(CFLAG) serializablevector.cpp

#iserializable.o : iserializable.cpp iserializable.h Makefile
#	g++ $(CFLAG) iserializable.cpp

#parsehelper.o : parsehelper.cpp parsehelper.h Makefile
#	g++ $(CFLAG) parsehelper.cpp

#heap.o : heap.cpp heap.h Makefile
#	g++ $(CFLAG) heap.cpp

#loadfactory.o : loadfactory.cpp loadfactory.h Makefile
#	g++ $(CFLAG) loadfactory.cpp

clean:
	rm -f $(OBJ) $(EXE)

run:
	./$(EXE)

