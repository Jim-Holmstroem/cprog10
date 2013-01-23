#include <stdexcept>
#include <fstream>
#include <sstream>
#include "Matrix.h"

bool equal(Matrix a, Matrix b ){
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

void print_assert(const char * msg,bool value){
    std::cout << msg << "=" << ((value)?"TRUE":"FALSE") << std::endl;
}
void print_assert(bool value){
    std::cout << ((value)?"TRUE":"FALSE") << std::endl;
}
int main()
{

    Matrix a( 2, 2 );
    Matrix b( 2, 2 );

    init_matrix(a, "[ 1 2 ; 3 4 ]");
    init_matrix(b, "[ 5 6 ; 7 8 ]");
    Matrix c = a*b;


    print_assert( 
            c[0][0] == 19 &
            c[0][1] == 22 &
            c[1][0] == 43 &
            c[1][1] == 50
    );

    print_assert( 
            a[0][0] == 1 &
            a[0][1] == 2 &
            a[1][0] == 3 &
            a[1][1] == 4
    );

    print_assert( 
            b[0][0] == 5 &
            b[0][1] == 6 &
            b[1][0] == 7 &
            b[1][1] == 8
    );

}
