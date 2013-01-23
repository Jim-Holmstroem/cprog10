#ifndef MATRIX_H
    #define MATRIX_H
    #include "vector.h"
    #include <iostream>

    //using namespace std;

    class Matrix{
     public:
        typedef unsigned int index;
        
        class matrix_row : private Vector< int >{
        public:
            matrix_row(std::size_t s = 0) : Vector< int >( s ){}
            using Vector<int>::operator[];
            
        private:
            friend std::istream& operator>>( std::istream&, Matrix& ); //class matrix_row can access everything in class Vector
        };
        
        Matrix( );
        Matrix( std::size_t, std::size_t );
        Matrix( const Matrix& );
        Matrix(int size);  //should be std::size_t as argument since the other size uses that
        ~Matrix( );
        
        Matrix& operator= ( const Matrix& ); //tested when overwriting matrix with different dimension
        Matrix operator+ ( const Matrix& ) const; //tested (with 0x0 matrix)
        Matrix operator* ( const Matrix& ) const; //tested with chains (with 0x0 matrix)
        Matrix operator* ( int ) const; // tested (with 0x0 matrix)
        Matrix operator-( const Matrix& ) const; //tested (with 0x0 matrix)
        Matrix operator-( ) const; //tested
        
        Matrix& transpose( ); //tested
        
        matrix_row& operator[]( index i ); // arg type is unsigned int
        const matrix_row& operator[]( index i ) const;
        
        std::size_t rows() const;
        std::size_t cols() const;
        
     protected:
     private:
        Vector< matrix_row >        m_vectors;
        std::size_t                 m_rows;
        std::size_t                 m_cols;
        
        void add_row( );            // Non mandatory help function
        friend std::istream& operator>> ( std::istream&, Matrix& ); // tested when overwriting matrix with different dimension
    };

    std::istream& operator>> ( std::istream&, Matrix& );
    std::ostream& operator<< ( std::ostream&, Matrix& ); // should have const Matrix& or else cannot compile cout << (m*m2) << endl;
    Matrix operator* ( int, const Matrix& );

#endif // MATRIX_H
