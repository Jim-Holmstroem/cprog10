MOD = test iserializable iserializablecontainer serializablemap serializablevector parsehelper

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

EXE = test_serialize

CXX = g++

CFLAG = -c -Wall -Wextra #-ftabstop=4 
LFLAG =

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LFLAG) $(OBJ) -o $(EXE)

$(OBJ) : $(SRC) $(HDR)
	$(CXX) $< $(CFLAG) -o $@

clean:
	rm -f $(OBJ) $(EXE)

run:
	./$(EXE)

