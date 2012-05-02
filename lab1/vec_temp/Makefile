all:
	g++ -DDEBUG vec_temp.cpp test_template_vec.cpp -o test
run:
	./test

no_debug:
	g++ vec_temp.cpp test_template_vec.cpp -o test
send:
	./submit.py cprog09lab15.cpp vec_temp.h
