#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix.h"
#include "../cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>

class MatrixTestSuite : public CxxTest::TestSuite
{
    /*
    Matrix a_matrix_2by2() {    // [ 3 5 ]
        Matrix m;               // [ 2 0 ]
        stringstream s("3 5; 2 0 ");
        s >> m;
        return m;
    }
    */
public:
    void testIndexOperator ( )
    {
        Matrix m( 2, 2 );
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );
    }
};

#endif // MATRIX_TEST_H_INCLUDED

