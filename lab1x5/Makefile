MOD = vector main

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

FLDR = lab1x5


OPTFLAG = -O3 

CFLAG = -c -DDBOOL -Wall
LFLAG =

all:
	make lab1x5

lab1x5 : $(OBJ) Makefile
	g++ $(OBJ) -o lab1x5

vector.o : vector.cpp vector.h Makefile
	g++ $(CFLAG) $(OPTFLAG) vector.cpp

main.o : main.cpp main.h Makefile
	g++ $(CFLAG) main.cpp

clean:
	rm -f *.o lab1x5 val_*.dat

test_weight:
	./lab1x5
	diff val_builtin.dat val_math.dat
	diff val_builtin.dat val_lookup8.dat
	diff val_builtin.dat val_lookup16.dat
	diff val_builtin.dat val_sparse.dat
	diff val_builtin.dat val_dense.dat
	
	
	
	
	

run:
	./lab1x5
