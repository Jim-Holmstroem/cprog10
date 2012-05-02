#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "matrix.h"
#include "../cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>
#include <iostream> //added for istream
#include <cmath>
#include <vector>
#include <numeric>
#include <exception>


//TS_FAIL just fails the test. It is like an assert(false) with an error message. For example:
//void testSomething( void )
//{
//    TS_FAIL( "I don't know how to test this!" );
//}

//TS_ASSERT is the basic all-around tester. It works just like the well-respected assert() macro (which I sincerely hope you know and use!) An example:
//void testSquare( void )
//{
//    MyFileLibrary::createEmptyFile( "test.bin" );
//    TS_ASSERT( access( "test.bin", 0 ) == 0 );
//}

//This is the second most useful tester. As the name hints, it is used to test if two values are equal.
//    void testSquare( void )
//{
//    TS_ASSERT_EQUALS( square(-5), 25 );
//}

//The opposite of TS_ASSERT_EQUALS(), this macro is used to assert that two values are not equal.
//    void testNumberGenerator( void )
//{
//    int first = generateNumber();
//    int second = generateNumber();
//    TS_ASSERT_DIFFERS( first, second );
//}

//This macro asserts that the first operand is less than the second.
//void testFindLargerNumber( void )
//{
//    TS_ASSERT_LESS_THAN( 23, findLargerNumber(23) );
//}
// or TS_ASSERT_LESS_THAN_EQUALS

//These assertions are used to test whether an expression throws an exception. TS_ASSERT_THROWS is used when you want to verify the type of exception thrown, and TS_ASSERT_THROWS_ANYTHING is used to just make sure something is thrown. As you might have guessed, TS_ASSERT_THROWS_NOTHING asserts that nothing is thrown. (v3.10.0) TS_ASSERT_THROWS_EQUALS checks the type of the exception as in TS_ASSERT_THROWS then allows you to compare two value (one of which will presumably be the caught object). TS_ASSERT_THROWS_ASSERT is the general case, and allows you to make any assertion about the thrown value. These macros may seem a little complicated, but they can be very useful; see below for an example.

//void testFunctionsWhichThrowExceptions( void )
//{
//    TS_ASSERT_THROWS_NOTHING( checkInput(1) );
//    TS_ASSERT_THROWS( checkInput(-11), std::runtime_error );
//    TS_ASSERT_THROWS_ANYTHING( thirdPartyFunction() );

//    TS_ASSERT_THROWS_EQUALS( validate(), const std::exception &e,
//                             e.what(), "Invalid value" );
//    TS_ASSERT_THROWS_ASSERT( validate(), const Error &e,
//                             TS_ASSERT_DIFFERS( e.code(), SUCCESS ) );
//}

//If you need to comment out tests, use C++-style comments. Also, if you just don't want CxxTest to run a specific test function, you can temporarily change its name, e.g. by prefixing it with x:

//     class MyTest : public CxxTest::TestSuite
//     {
//     public:
//     // void testFutureStuff()
//     // {
//     // }

//        void xtestFutureStuff()
//        {
//        }
//     };

class MatrixTestSuite : public CxxTest::TestSuite{

  public:

    Matrix m;
    int max_size;

    void setUp(void){
	    max_size = 5;

    }

    void xtestIndexOperator (void){

        std::filebuf fb;
        fb.open("matrices.dat",std::ios::in);
        std::istream ins(&fb);
        std::cerr << std::endl;
        while(ins){
            std::cerr<<(char)ins.get();
        }
        std::cerr << std::endl;

        ins >> m;

        TS_ASSERT( m[ 0 ][ 1 ] == 0 );
        const Matrix m_const(3,3);
        //TS_ASSERT_THROWS_ANYTHING(m_const[2][2] = 1337);
        //TS_ASSERT_EQUALS(m_const[2][2], 1337);

    }

    void xtestSquareConstructor(void){
        for(int N = 0;N<max_size;N++){//kvadratisk matriser
            Matrix a(N);
            TS_ASSERT_EQUALS(a.rows(),N);
            TS_ASSERT_EQUALS(a.cols(),N);
            for(int i = 0;i<N;i++){
                for(int j = 0;j<N;j++){//check if the matrix is a unitmatrix
                    if(i!=j){
                        TS_ASSERT_EQUALS(a[i][j],0); //check if all elements not on diagonal are 0
                    }else{
                        TS_ASSERT_EQUALS(a[i][j],1); //check if all elements on diagonal are 1  
                    }
                }    
            }
        }
    }

    void xtestNormalConstructor(void){
        //NOTE I dont test the 0x1 matrices since we are unclear on what dimension those should have
        for(int N = 1;N<max_size;N++){
            for(int M = 1; M<max_size;M++){
                Matrix a(M,N);
                TS_ASSERT_EQUALS(a.rows(),M); //check if all sizes are correct
                TS_ASSERT_EQUALS(a.cols(),N);
                 
                Matrix b = a;
                TS_ASSERT_EQUALS(b.rows(),M);
                TS_ASSERT_EQUALS(b.cols(),N);
                 
                Matrix c(a);
                TS_ASSERT_EQUALS(c.rows(),M);
                TS_ASSERT_EQUALS(c.cols(),N);

                for(int j = 1;j<N;j++){
                    for(int i = 1; i<M;i++){
                        TS_ASSERT_EQUALS(a[i][j],0) //check if everything is inited to zero
                        TS_ASSERT_EQUALS(b[i][j],0)
                        TS_ASSERT_EQUALS(c[i][j],0)
                    }
                }
            }
        }

    }

    void testMultiplication(void){


        //NOTE none of the implemented matrices has support for this, sadface
        //dimension checks
        //for(int N=1;N<max_size;N++){ // [M*k]x[kp*N] => [M*N] if and only if k=kp should it work else it should throw an error
        //    for(int kp=1;kp<max_size;kp++){
        //        for(int k=1;k<max_size;k++){
        //            for(int M=1;M<max_size;M++){
        //                Matrix a(M,k);
        //                Matrix b(kp,N);
        //                if(k==kp){
        //                    TS_ASSERT_THROWS_NOTHING(a*b);
 //                       }else{
 //                           TS_ASSERT_THROWS_ANYTHING(a*b);    
 //                       }
 //                   }
 //               }
   //         }
     //   }

        for(int N=1;N<max_size;N++){
            for(int M=1;M<max_size;M++){
                for(int R=1;R<max_size;R++){//test for all legit matrix-combinations
                    Matrix c(M,R);
                    for(int k=0;k<R;k++){
                        for(int l=0;l<M;l++){
                            c[l][k] = l + M*k + 1; //labels all the positions in the matrix beginning in the first dimension (rows)
                        }
                    }
                    Matrix d(R,N);
                    for(int k=0;k<N;k++){
                        for(int l=0;l<R;l++){
                            d[l][k] = l + R*k + 1; //labels all the positions in the matrix beginning in the first dimension (rows)
                        }
                    }

                    Matrix e = c*d;
                    
                    TS_ASSERT_EQUALS(e.rows(),M); //check if the product has the right dimension
                    TS_ASSERT_EQUALS(e.cols(),N);
                    
                    int ref[M][N];
                    //do the matrix multiplication by hand into ref[][]
                    for(int j=0;j<N;j++){
                        for(int i=0;i<M;i++){
                            ref[i][j]=0;
                            for(int r=0;r<R;r++){ //inner prod on the two vector
                                ref[i][j]+=c[i][r]*d[r][j];  
                            }
                        }
                    }
                    
                    //hard test if these two matrices are equal
                    for(int j=0;j<N;j++){
                        for(int i=0;i<M;i++){
                            //char msg[512]; //TODO something is weird here
                            //sprintf(msg,"(%d,%d)/(%d,%d)",i,j,M,N);
                            //TS_WARN(msg);
                            TS_ASSERT_EQUALS(ref[i][j],e[i][j]);
                        }
                    }
                }
            }
        }
        
    }

    void xtestMathOperators(void){


        
        //our 8loop to generate all the test cases and in the double-for checker and then check with tensor defintion



        //0
        Matrix a0(0);
        Matrix b0(0);

        Matrix big(5);

        Matrix c0;

        c0 = a0 + b0;
        
        TS_ASSERT_EQUALS(c0.cols(),0);
        TS_ASSERT_EQUALS(c0.rows(),0);

        TS_ASSERT_THROWS_ANYTHING(big + a0);

        c0 = a0 - b0;
        TS_ASSERT(c0.cols()==0 && c0.rows()==0);
        TS_ASSERT_THROWS_ANYTHING(big - a0);

        c0 = a0 * b0;
        TS_ASSERT(c0.cols()==0 && c0.rows()==0);
        TS_ASSERT_THROWS_ANYTHING(big * b0);
        TS_ASSERT_THROWS_ANYTHING(a0 * big);

        c0 = 3*b0;
        TS_ASSERT(c0.cols()==0 && c0.rows()==0);
        c0 = b0*3;
        TS_ASSERT(c0.cols()==0 && c0.rows()==0);
        c0 = -b0;
        TS_ASSERT(c0.cols()==0 && c0.rows()==0);

        //1

        Matrix a1(1);
        Matrix b1(1);

        a1 = 7 * a1;
        b1 = b1 * 3;

        TS_ASSERT(a1[0][0]==7); //tests int*matrix
        TS_ASSERT(b1[0][0]==3); //tests matrix*int

        Matrix c1;

        c1 = a1 + b1;
        TS_ASSERT(c1[0][0]==10);
        c1 = a1 - b1;
        TS_ASSERT(c1[0][0]==4);
        c1 = a1 * b1;
        TS_ASSERT(c1[0][0]==21);
        c1 = 3*b1;
        TS_ASSERT(c1[0][0]==9);
        c1 = a1*3;
        TS_ASSERT(c1[0][0]==21);
        c1 = -b1;
        TS_ASSERT(c1[0][0]==-3);

        //Test to check chaining-operations
        Matrix ac(2);
        Matrix bc(2);
        Matrix cc(2);

        Matrix dc(2);

        TS_ASSERT_THROWS_NOTHING(ac+ac+cc);
        dc = ac+bc+cc;
        TS_ASSERT(dc[0][0]==3);
        TS_ASSERT(dc[0][1]==0);
        TS_ASSERT(dc[1][0]==0);
        TS_ASSERT(dc[1][1]==3);

        dc = ac-bc-cc;
        TS_ASSERT(dc[0][0]==-1);
        TS_ASSERT(dc[0][1]==0);
        TS_ASSERT(dc[1][0]==0);
        TS_ASSERT(dc[1][1]==-1);

        dc = ac*bc*cc;

        TS_ASSERT(dc[0][0]==1);
        TS_ASSERT(dc[0][1]==0);
        TS_ASSERT(dc[1][0]==0);
        TS_ASSERT(dc[1][1]==1);


        //dimsions when matrix*matrix

        Matrix a13(1,3);
        Matrix b32(3,2);

        TS_ASSERT_THROWS_ANYTHING(b32*a13);
        TS_ASSERT_THROWS_NOTHING(a13*b32);

        //have already tested with empty matrices

    }

    void xtestTranspose(void){

        Matrix a(0);
        Matrix b;

        b = a.transpose(); //special case with 0-size matrix
        TS_ASSERT_EQUALS(a.rows(),0);
        TS_ASSERT_EQUALS(a.cols(),0);
        TS_ASSERT_EQUALS(b.rows(),0);
        TS_ASSERT_EQUALS(b.cols(),0);
        
        for(int j=1;j<max_size;j++){
            for(int i=1;i<max_size;i++){
                Matrix c(i,j);
                for(int k=0;k<c.cols();k++){
                    for(int l=0;l<c.rows();l++){
                        c[l][k] = l + c.rows()*k + 1; //labels all the positions in the matrix beginning in the first dimension (rows)
                    }
                }

                TS_ASSERT_EQUALS(c.rows(),i) //check if it has got the right dimension
                TS_ASSERT_EQUALS(c.cols(),j)

                c.transpose();
                TS_ASSERT_EQUALS(c.rows(),j) //check if it has got the right dimension
                TS_ASSERT_EQUALS(c.cols(),i)

                for(int k=0;k<c.cols();k++){
                    for(int l=0;l<c.rows();l++){
                        TS_ASSERT_EQUALS(c[l][k], k + c.cols()*l + 1); //the labels transposed formula
                    }
                }
                
            }
        }

    }

    void xtestOutput(void){
        Matrix mout(2,1);
        //ins >> mout;
        mout[0][0] = 42;
        TS_ASSERT(mout[0][0]==42);
        //std::cout << mout << std::endl;//skriver inte ut rätt.. : (
    }


    void xtestCopying(void){


        Matrix m2(m);
        TS_ASSERT(m2[0][0] == 1);
        TS_ASSERT(m2[0][1] == 2);
        TS_ASSERT(m2[1][0] == 3);
        TS_ASSERT(m2[1][1] == 4);
        TS_ASSERT(m2.rows() == 2);
        TS_ASSERT(m2.cols() == 2);

	    Matrix m3;
	    m3 = m;
    }

};

#endif // MATRIX_TEST_H_INCLUDED

