#include <stdexcept>
#include <fstream>
#include <sstream>
#include "Matrix.h"

bool checkEqualMatrix(Matrix a, Matrix b ){
    // Compare matrices without using matrix 
    // implementation (except for rows/cols and [])

    if(a.rows() != b.rows() ) 
        throw std::out_of_range("Dimension missmatch on rows");
    if(a.cols() != b.cols() )
        throw std::out_of_range("Dimension missmatch on cols");	

    for(int i = 0 ; i<a.rows() ; i++) 
    {
        for(int j = 0 ; j<a.cols() ; j++) 
        {
            std::cout << "A";
            if(a[i][j] != b[i][j])
            {
                return false;
            }
	}
    }
    return true;
}

Matrix constant_matrix() {
    Matrix m;
    std::stringstream ss("[ 1 3 5 ; 0 2 0]");
    ss >> m;
    return m;
}

void init_matrix( Matrix& m, const char * input )
{
    std::stringstream ss( input );
    ss >> m;
}


int main()
{
    std::cout << checkEqualMatrix(constant_matrix(),constant_matrix()) << std::endl;
}
