MOD = vector matrix maze

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

BACKUP = $(SRC) $(HDR)

FLDR = lab1x2

CFLAG = -c -DDMATRIX -Wall
LFLAG =


all:
	make lab1x2

lab1x% : $(OBJ) Makefile
	g++ $(OBJ) -o lab1x$*

vector.o : vector.cpp vector.h Makefile
	g++ $(CFLAG) vector.cpp

matrix.o : matrix.cpp matrix.h Makefile
	g++ $(CFLAG) matrix.cpp

maze.o : maze.cpp Makefile
	g++ $(CFLAG) maze.cpp

clean:
	rm -f *.o lab1x2

run:
	./lab1x2

#backup: $(BACKUP)
#	cp -R $(BACKUP) backup/backup_$$(date +20\%y\%m\%d_\%H\%M\%S)
