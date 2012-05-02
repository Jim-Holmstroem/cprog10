#ifndef MATRIX_H
#define MATRIX_H
#include "../losn/Vector.h"    //  CHANGE HERE !!
// #include "Vector.h"         //
#include <iostream>

//using namespace std;

class Matrix
{
 public:
    typedef unsigned int index;
    
    class matrix_row : private Vector< int >
    {
    public:
        matrix_row( std::size_t s = 0) : Vector< int >( s ) {}
        using Vector<int>::operator [];
    private:
        friend std::istream& operator>>( std::istream&, Matrix& );
    };
    
    Matrix( );
    Matrix( std::size_t, std::size_t );
    Matrix( const Matrix& );
    Matrix(int size);
    ~Matrix( );
    
    Matrix& operator= ( const Matrix& );
    Matrix operator+ ( const Matrix& ) const;
    Matrix operator* ( const Matrix& ) const;
    Matrix operator* ( int ) const;
    Matrix operator-( const Matrix& ) const;
    Matrix operator-( ) const;
    
    Matrix& transpose( );
    
    matrix_row& operator[]( index i );
    const matrix_row& operator[]( index i ) const;
    
    std::size_t rows() const;
    std::size_t cols() const;
    
 protected:
 private:
    Vector< matrix_row >        m_vectors;
    std::size_t                 m_rows;
    std::size_t                 m_cols;
    
    void add_row( );            // Non mandatory help function
    friend std::istream& operator>> ( std::istream&, Matrix& );
};

std::istream& operator>> ( std::istream&, Matrix& );
std::ostream& operator<< ( std::ostream&, Matrix& );
Matrix operator* ( int, const Matrix& );

#endif // MATRIX_H
