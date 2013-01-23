MOD = matrix vector main helper

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

BACKUP = $(SRC) $(HDR)

FLDR = lab1x

CFLAG = -c -Wall #-DDMATRIX
LFLAG =

CTEST = -DCAL # recompiles main.cpp if Makefile is updated

all:
	make lab1x1

lab1x% : $(OBJ) Makefile
	g++ $(OBJ) -o lab1x$*

helper.o : helper.cpp helper.h Makefile
	g++ $(CFLAG) $(CTEST) helper.cpp

vector.o : vector.cpp vector.h Makefile
	g++ $(CFLAG) $(CTEST) vector.cpp

matrix.o : matrix.cpp matrix.h Makefile
	g++ $(CFLAG) $(CTEST) matrix.cpp

main.o : main.cpp main.h Makefile
	g++ $(CFLAG) $(CTEST) main.cpp


clean:
	rm -f *.o lab1x1

run:
	./lab1x1 < indata

#backup: $(BACKUP)
#	cp -R $(BACKUP) backup/backup_$$(date +20\%y\%m\%d_\%H\%M\%S)
