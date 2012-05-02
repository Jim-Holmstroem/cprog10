#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix.h"
#include "/info/cprog09/cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>

class MatrixTestSuite : public CxxTest::TestSuite
{
    /*
    Matrix a_matrix_3by2() {    // [ 1 3 5 ]
        Matrix m;               // [ 0 2 0 ]
        m << "1 3 5; 0 2 0 ";
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

#endif

