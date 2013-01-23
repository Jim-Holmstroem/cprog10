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
    Matrix c( 2, 2 );
    Matrix abc( 2, 2 );
    Matrix abcp( 2, 2 );
	
	init_matrix(a,"[ 1 2 ; 3 4 ]");
	init_matrix(b,"[ 5 6 ; 7 8 ]");
	init_matrix(c,"[ 9 10 ; 11 12 ]");
	
	init_matrix(abc,"[ 413 454 ; 937 1030 ]");
	init_matrix(abcp,"[ 12 18 ; 21 24 ]");
	

    print_assert( "chain multiply",
		equal(a*b*c,abc)
	);

    print_assert( "chain addition",
		equal(a+b+c,abcp)
	);
	Matrix faultyu = a+b+c;
	std::cout << abcp << std::endl;

}
