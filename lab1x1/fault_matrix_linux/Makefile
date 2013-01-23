# Change these
cxxtestpath = ../cxxtest/
testcode    = matrix_test.h

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest_all:
	for p in 0 1 2 3 4 5 6 7 8 9; do make runtest0$$p;done

runtest0%: testcode.cpp
	g++ -I $(cxxtestpath) -o runtest0$* testcode.cpp Matrix0$*.o
#./runtest0$*

ref_output: ref_output_maker.cpp
	g++ ref_output_maker.cpp matrix.cpp -o ref_output

ref_output0%:
	./ref_output $* > ref_matrices_$*.dat

showoff0%: showoff_0%.cpp
	g++ -o showoff_0$* showoff_0$*.cpp Matrix0$*.o
	./showoff_0$*

generate_ref_output:
	for i in 0 1 2 3 4 5 6 7 8 9; do make ref_output$$i;done

clean:
	touch runtest0* ref_output testcode.cpp 
	rm runtest0* ref_output testcode.cpp  ref_matrices_*.dat
