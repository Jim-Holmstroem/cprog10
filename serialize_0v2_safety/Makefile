MOD = test

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

CFLAG = -c -Wall #-DDMATRIX
LFLAG =

CTEST = -DCAL # recompiles main.cpp if Makefile is updated

all:
	make test

test: $(OBJ) Makefile
	g++ $(OBJ) -o test

#helper.o : helper.cpp helper.h Makefile
#	g++ $(CFLAG) $(CTEST) helper.cpp

test.o : test.cpp test.h Makefile
	g++ $(CFLAG) $(CTEST) test.cpp


clean:
	rm -f *.o test

run:
	./test

#backup: $(BACKUP)
#	cp -R $(BACKUP) backup/backup_$$(date +20\%y\%m\%d_\%H\%M\%S)
