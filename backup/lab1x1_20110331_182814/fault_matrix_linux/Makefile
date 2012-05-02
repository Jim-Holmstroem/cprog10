# Change these
cxxtestpath = /info/cprog09/cxxtest/
testcode    = matrix_test.h

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest_all:
	for p in 0 1 2 3 4 5 6 7 8 9; do make runtest0$$p;done

runtest0%: testcode.cpp
	g++ -I $(cxxtestpath) -o runtest0$* testcode.cpp Matrix0$*.o
	./runtest0$*
clean:
	touch runtest0* testcode.cpp
	rm runtest0* testcode.cpp
