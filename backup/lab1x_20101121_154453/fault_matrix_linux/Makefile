cxxtestpath = /info/cprog09/cxxtest/

runnerstud.cpp: matrix_student_test.h
	python $(cxxtestpath)cxxtestgen.py --error-printer -o runnerstud.cpp matrix_student_test.h 

runnnerstud: runnerstud.cpp
	g++ -I $(cxxtestpath) -o runnerstud runnerstud.cpp Matrix01.o

# Usage: make rstud03
rstud0%: runnerstud.cpp
	g++ -I $(cxxtestpath) -o runnerstud0$* runnerstud.cpp Matrix0$*.o

clean:
	touch runnerstud runnerstud.cpp
	rm runnerstud runnerstud.cpp

