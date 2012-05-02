all:
	g++ -c must_follow_a.cpp
	cxxtest/cxxtestgen.py --error-printer -o 1.2b.cpp test_must_follow_a.cpp
	g++ -o test_1.2b -I cxxtest 1.2b.cpp must_follow_a.o
	./test_1.2b
