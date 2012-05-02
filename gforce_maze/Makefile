MOD = vector matrix maze

SRC = $(MOD:=.cpp)
HDR = $(MOD:=.h)
OBJ = $(MOD:=.o)

BACKUP = $(SRC) $(HDR)

FLDR = g_maze

CFLAG = -c -Wall
LFLAG =


all: $(OBJ) Makefile
	g++ $(OBJ) -o g_maze

vector.o : vector.cpp vector.h Makefile
	g++ $(CFLAG) vector.cpp

matrix.o : matrix.cpp matrix.h Makefile
	g++ $(CFLAG) matrix.cpp

maze.o : maze.cpp Makefile
	g++ $(CFLAG) maze.cpp

clean:
	rm -f *.o g_maze

run:
	./g_maze

#backup: $(BACKUP)
#	cp -R $(BACKUP) backup/backup_$$(date +20\%y\%m\%d_\%H\%M\%S)
