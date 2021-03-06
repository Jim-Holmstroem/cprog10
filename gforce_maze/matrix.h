#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
#include<iostream>
#include<cstring>

//using namespace std;

class Matrix{
  public:
    typedef unsigned int index;

    class matrix_row : private Vector< char >{
      public:
      matrix_row(std::size_t s = 0) : Vector< char >( s ){}
        using Vector<char>::operator[];

      private:
        friend std::istream& operator>>( std::istream&, Matrix& ); //class matrix_row can access everything in class Vector
    };

    Matrix( );
    Matrix( std::size_t, std::size_t );
    Matrix( const Matrix& );
    Matrix(int size);  //should be std::size_t as argument since the other size uses that
    ~Matrix( );

    Matrix& operator= ( const Matrix& ); //tested when overwriting matrix with different dimension
    
    Matrix& transpose( ); //tested

    matrix_row& operator[]( index i ); // arg type is unsigned int
    const matrix_row& operator[]( index i ) const;

    std::size_t rows() const;
    std::size_t cols() const;

    //for lab1.2 maze
    Matrix& read(const char**);
    bool solve();

//these should be private
    std::string text;
    int shift;

  protected:
  private:
    Vector< matrix_row >        m_vectors;
    std::size_t                 m_rows;
    std::size_t                 m_cols;

    const Vector<char> dispseq;

    //for lab1.2 maze
    bool goto_path(std::size_t, std::size_t);
    bool fill_disp(std::size_t, std::size_t);
    Matrix& mark_exit();

    friend std::istream& operator>> ( std::istream&, Matrix& ); // tested when overwriting matrix with different dimension
};

std::istream& operator>> ( std::istream&, Matrix& );
std::ostream& operator<< ( std::ostream&, Matrix& ); // should have const Matrix& or else cannot compile cout << (m*m2) << endl;

#endif // MATRIX_H
