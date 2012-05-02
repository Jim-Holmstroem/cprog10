/*
 * Driver for cprog06lab1a. Written 2006-08-27 by Gunnar Kreitz <gkreitz>
 *
 * If you need to modify this file to solve the assignment, you're most likely
 * solving it the wrong way.
 */

#include "vector.h"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <stdexcept>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::size_t;

namespace { // Anonymous namespace
	vector<Vector *> vectors;
	/* They're not required to keep track of sizes yet, so we do it for them.
	 */
	vector<size_t> vectors_s;

	/*
	 * There is no way in standard C++ to read a size_t. The way we solve it here is to
	 * read it as an unsigned long. This program will not be used with too large inputs.
	 * Another way would be to use size_t ret; scanf("%zu", &ret); which is legal in C99
	 * and thus most likely will be OK in C++0x. It's already supported by most compilers.
	 * If it was changed to using scanf instead, the sync_with_stdio(false)
	 * would need to be removed.
	 */
	size_t read_size_or_die() {
		unsigned long ret;
		cin >> ret;
		assert(cin);
		return static_cast<size_t>(ret);
	}

	size_t read_idx_or_die() {
		size_t ret = read_size_or_die();
		assert(ret < vectors.size() && vectors[ret]);
		return ret;
	}
}


int main(int argc, char **argv) {
	string command;
	string arg;

	std::ios::sync_with_stdio(false);

	while(cin >> command) {
		assert(vectors.size() == vectors_s.size());
		if(command == "new" ) {
			const size_t size = read_size_or_die();
			vectors.push_back(new Vector(size));
			vectors_s.push_back(size);
            cout << "size=" << vectors_s.size() << endl;
		} else if(command == "newcopy") {
			const size_t idx = read_idx_or_die();
			vectors.push_back(new Vector(* const_cast<const Vector*>(vectors[idx])));
			vectors_s.push_back(vectors_s[idx]);
            cout << idx << " copied, size=" << vectors_s.size() << endl;
		} else if(command == "delete") {
			const size_t idx = read_idx_or_die();
			delete vectors[idx];
			vectors[idx] = 0;
			vectors_s[idx] = 0;
            cout << idx << " deleted, size=" << vectors_s.size() << endl;            
		} else if(command == "copy") {
			const size_t from = read_idx_or_die();
			const size_t to = read_idx_or_die();
			*vectors[to] = *const_cast<const Vector*>(vectors[from]);
			vectors_s[to] = vectors_s[from];
            cout << from << " copied to" << to << endl;            
		} else if(command == "set") {
			const size_t idx = read_idx_or_die();
			const size_t idx2 = read_size_or_die();
			unsigned int value;
			cin >> value;
			try {
				(*vectors[idx])[idx2] = static_cast<const unsigned int>(value);
                cout << value << endl;
			} catch (std::out_of_range oor) {
				cout << "std::out_of_range" << endl;
			}
		} else if(command == "print") {
			const size_t idx = read_idx_or_die();
			for(size_t i = 0; i < vectors_s[idx]; ++i) {
				if(i)
					cout << " ";
				/*
				 * We read using both const and non-const operator[] to test both versions.
				 */
				if(i & 1)
					cout << (*vectors[idx])[i];
				else
					cout << (*const_cast<const Vector*>(vectors[idx]))[i];
			}
			cout << endl;
		} else if(command == "get") {
			const size_t idx = read_idx_or_die();
			const size_t idx2 = read_size_or_die();
			try {
				cout << (*const_cast<const Vector*>(vectors[idx]))[idx2] << endl;
			} catch (std::out_of_range oor) {
				cout << "std::out_of_range" << endl;
			}
		} else if(command == "inc") {
			const size_t idx = read_idx_or_die();
			const size_t idx2 = read_size_or_die();
			try {
				cout << (*vectors[idx])[idx2]++ << endl;
			} catch (std::out_of_range oor) {
				cout << "std::out_of_range" << endl;
			}
		} else {
			assert(!"Unknown command");
		}
	}

	return 0;
}
