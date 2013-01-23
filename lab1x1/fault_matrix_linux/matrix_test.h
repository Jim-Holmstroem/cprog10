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

//If you need to comment out tests, use C++-style comments. Also, if you just don't want CxxTest to run a specific test function, you can temporarily change its name, e.g. by prefixing it with x


class MatrixTestSuite : public CxxTest::TestSuite
{
  private:
    int max_size;

	bool checkEqualMatrix(Matrix m1, Matrix m2)
	{
        if(m1.rows() != m2.rows() ){throw std::out_of_range("Unequal rows");}
        if(m1.cols() != m2.cols() ){throw std::out_of_range("Unequal columns");}

		for(int i = 0 ; i<m1.rows() ; i++){
			for(int j = 0 ; j<m1.cols() ; j++){
				if(m1[i][j] != m2[i][j]){return false;}
			}
		}

	return true;
	}
	
    Matrix a_matrix_3by2()
    {
        Matrix m;
        std::stringstream s("[ 1 3 5 ; 0 2 0 ]");
        s >> m;
        return m;
    }
    
    void init_matrix(Matrix& m, const char* file)
    {
        std::stringstream stream( file );
        stream >> m;
    }
	
  public:
    //cxxtest will run this function first
    void setUp(void)
    {
        max_size = 5;
    }
    
    void testIndexOperator()
    {
        Matrix m( 2, 2 );
		//std::cout << m;
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );

        m = a_matrix_3by2();
		//std::cout << m;
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        init_matrix(m, "[ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        std::stringstream ss;
        ss << m;
        ss >> m;
		//std::cout << m;
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );
    }

    void testSquareConstructor(void)
    {
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

    void testNormalConstructor(void)
    {
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
    
	void test_default_constructor(){
		Matrix m1;
		//std::cout << m1;

		TS_ASSERT( m1.rows() == 0 );
		TS_ASSERT( m1.cols() == 0 );
				


	}

	void test_size_constructor(){
		Matrix m2(2,3);

		//std::cout << m2;

		TS_ASSERT( m2.rows() == 2 );
		TS_ASSERT( m2.cols() == 3 );
		
		TS_ASSERT( m2[0][0] == 0 );
		TS_ASSERT( m2[0][1] == 0 );
		TS_ASSERT( m2[0][2] == 0 );
		TS_ASSERT( m2[1][0] == 0 );
		TS_ASSERT( m2[1][1] == 0 );
		TS_ASSERT( m2[1][2] == 0 );

	}



	void test_copy_constructor(){
		Matrix m1(2,3);
		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");

		//std::cout << m1;

		Matrix m2 = m1;
		TS_ASSERT( m2[0][0] == 1 );
		TS_ASSERT( m2[0][1] == 2 );
		TS_ASSERT( m2[0][2] == 3 );
		TS_ASSERT( m2[1][0] == 3 );
		TS_ASSERT( m2[1][1] == 4 );
		TS_ASSERT( m2[1][2] == 5 );
		
		TS_ASSERT( m2.rows() == 2 );
		TS_ASSERT( m2.cols() == 3 );

		//std::cout << m1;

		Matrix m3(m1);



		TS_ASSERT( m3[0][0] == 1 );
		TS_ASSERT( m3[0][1] == 2 );
		TS_ASSERT( m3[0][2] == 3 );
		TS_ASSERT( m3[1][0] == 3 );
		TS_ASSERT( m3[1][1] == 4 );
		TS_ASSERT( m3[1][2] == 5 );
		
		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
	
		m3[0][0] = 100;

		TS_ASSERT( m1[0][0] != 100 );


	}

	void test_size_constructor_quad(){
		Matrix m2(3);

		TS_ASSERT( m2[0][0] == 1 );
		TS_ASSERT( m2[0][1] == 0 );
		TS_ASSERT( m2[0][2] == 0 );
		TS_ASSERT( m2[1][0] == 0 );
		TS_ASSERT( m2[1][1] == 1 );
		TS_ASSERT( m2[1][2] == 0 );
		TS_ASSERT( m2[2][0] == 0 );
		TS_ASSERT( m2[2][1] == 0 );
		TS_ASSERT( m2[2][2] == 1 );
		
		TS_ASSERT( m2.rows() == 3 );
		TS_ASSERT( m2.cols() == 3 );
	}

    void testElementwiseOperations(void)
    {
        //check invalid combinations, but since they don't handle it we can't check it..

        for(int N=1;N<max_size;N++){
            for(int M=1;M<max_size;M++){
                Matrix addA(M,N);
                Matrix subA(M,N);
                Matrix scaleA(M,N);
                Matrix minusA(M,N);
                Matrix addB(M,N);
                Matrix subB(M,N);

                //set up matrices
                for(int k=0;k<N;k++){
                    for(int l=0;l<M;l++){
                        int numA = l + M*k - (M*N)/2; //labels all the positions in the matrix beginning in the first dimension (rows)
                        int numB = k + M*l - (M*N)/2; //labels all the positions in the matrix beginning in the SECOND dimension (COLS)
                        addA[l][k] = numA;
                        subA[l][k] = numA;
                        scaleA[l][k] = numA;
                        minusA[l][k] = numA;
                        addB[l][k] = numB;
                        subB[l][k] = numB;
                    }
                }

                Matrix addRes = addA+addB;
                Matrix subRes = subA-subB;
                Matrix scaleRes = 17*scaleA; //17 is the most godtyckliga tal you can find
                Matrix minusRes = -minusA;
                
                //check the result sizes
                TS_ASSERT_EQUALS(addRes.rows(),M);
                TS_ASSERT_EQUALS(addRes.cols(),N);
                TS_ASSERT_EQUALS(subRes.rows(),M);
                TS_ASSERT_EQUALS(subRes.cols(),N);
                TS_ASSERT_EQUALS(scaleRes.rows(),M);
                TS_ASSERT_EQUALS(scaleRes.cols(),N);
                TS_ASSERT_EQUALS(minusRes.rows(),M);
                TS_ASSERT_EQUALS(minusRes.cols(),N);
                
                //check the calculations
                for(int k=0;k<N;k++){
                    for(int l=0;l<M;l++){
                        TS_ASSERT_EQUALS(addRes[l][k],(l+M*k-(M*N)/2)+(k+M*l-(M*N)/2));
                        TS_ASSERT_EQUALS(subRes[l][k],(l+M*k-(M*N)/2)-(k+M*l-(M*N)/2));
                        TS_ASSERT_EQUALS(scaleRes[l][k],17*(l+M*k-(M*N)/2));
                        TS_ASSERT_EQUALS(minusRes[l][k],-(l+M*k-(M*N)/2));
                    }
                } 
            }
        }    
    }


    void xtestMultiplication(void){ //TODO make this not hang, could possible be the "symetric"-formulae

        //TODO, do you have to check chaining in operations ?

        //NOTE none of the implemented matrices has support for this, sadface
        //dimension checks
        //for(int N=1;N<max_size;N++){ // [M*k]x[kp*N] => [M*N] if and only if k=kp should it work else it should throw an error
        //  for(int kp=1;kp<max_size;kp++){
        //      for(int k=1;k<max_size;k++){
        //          for(int M=1;M<max_size;M++){
        //              Matrix a(M,k);
        //              Matrix b(kp,N);
        //              if(k==kp){
        //                  TS_ASSERT_THROWS_NOTHING(a*b);
        //              }else{
        //                  TS_ASSERT_THROWS_ANYTHING(a*b);    
        //              }
        //          }
        //      }
        //  }

        //}

        for(int N=1;N<max_size;N++){
            for(int M=1;M<max_size;M++){
                for(int R=1;R<max_size;R++){//test for all legit matrix-combinations
                    Matrix c(M,R);
                    for(int k=0;k<R;k++){
                        for(int l=0;l<M;R++){
                            c[l][k] = l + M*k - (M*R)/2; //labels all the positions in the matrix beginning in the first dimension (rows)
                        }
                    }
                    Matrix d(R,N);
                    for(int k=0;k<N;k++){
                        for(int l=0;l<R;l++){
                            d[l][k] = l + R*k - (R*N)/2; //labels all the positions in the matrix beginning in the first dimension (rows)
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
                                ref[i][j]+=(i+M*r-(M*R)/2)*(r+N*j-(N*R)/2);//c[i][r]*d[r][j];  
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

  
    void testTranspose(void){

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

    void testOutput(void){
        std::stringstream ss;
        ss<<"ref_matrices_";
        ss<<max_size;
        ss<<".dat";
        std::string ref_name = ss.str();
        std::string tmp_name = "matrix.tmp";

        std::ifstream ref_matrices;
        ref_matrices.open(ref_name.c_str(),std::fstream::in);

        if (ref_matrices.fail()) {
            std::cerr << "unable to open referencefile \""<<ref_name<<"\" for reading" << std::endl;
            exit(1);
        }
        
        for(int j=1;j<max_size;j++){
            for(int i=1;i<max_size;i++){
                
                //Generate the correct data
                Matrix c(i,j);
                for(int k=0;k<c.cols();k++){ //fill it up as i should be
                    for(int l=0;l<c.rows();l++){
                        c[l][k] = l + c.rows()*k + 1; //labels all the positions in the matrix beginning in the first dimension (rows)
                    }
                }
                

                std::ofstream tmp_out;
                tmp_out.open(tmp_name.c_str(),std::fstream::out);
                
                tmp_out << c; //OUTPUT
                tmp_out.close();

                //check output with reference
                std::ifstream tmp_in;
                tmp_in.open(tmp_name.c_str(),std::fstream::in);
                
                int n,m;
                while(tmp_in>>n){
                    ref_matrices>>m;
                    TS_ASSERT_EQUALS(n,m); //should have the same output as reference
                }
                tmp_in.close();
            }
        }
    }

    void xtestInput(void){
        std::stringstream ss;
        ss<<"ref_matrices_";
        ss<<max_size;
        ss<<".dat";
        std::string ref_name = ss.str();
        std::string tmp_name = "matrix.tmp";

        std::ifstream ref_matrices;
        ref_matrices.open(ref_name.c_str(),std::fstream::in);

        if (ref_matrices.fail()) {
            std::cerr << "unable to open reference file for reading" << std::endl;
            exit(1);
        }

        for(int j=1;j<max_size;j++){
            for(int i=1;i<max_size;i++){
                Matrix c(i,j);
                
                ref_matrices >> c; //INPUT

                TS_ASSERT_EQUALS(i,c.rows());//check the size
                TS_ASSERT_EQUALS(j,c.cols());

                for(int k=0;k<c.cols();k++){
                    for(int l=0;l<c.rows();l++){
                       TS_ASSERT_EQUALS(c[l][k],l+c.rows()*k+1); 
                    }
                }
            }
        }
    }
    
    
    	void test_dot_product ( )
    {
        Matrix m( 1, 5 );
		Matrix m2( 5, 1);
		init_matrix(m, "[ 1 2 3 4 5 ]");
		init_matrix(m2, "[ 1 ; 2 ; 3 ; 4 ; 5 ]");
		//std::cout << m;
		//std::cout << m2;
		Matrix m3 = m*m2;
       TS_ASSERT( m3[0][0] == 55 );
    }


	void test_matrix_multiplication_quadratic ( )
    {

        Matrix m1( 2, 2 );
		Matrix m2( 2, 2);

		init_matrix(m1, "[ 1 2 ; 3 4 ]");
		init_matrix(m2, "[ 5 6 ; 7 8 ]");
		//std::cout << m1;
		//std::cout << m2;
		Matrix m3 = m1*m2;


    	TS_ASSERT( m3[0][0] == 19 );
		TS_ASSERT( m3[0][1] == 22 );
		TS_ASSERT( m3[1][0] == 43 );
		TS_ASSERT( m3[1][1] == 50 );


		TS_ASSERT( m1[0][0] == 1 );
		TS_ASSERT( m1[0][1] == 2 );
		TS_ASSERT( m1[1][0] == 3 );
		TS_ASSERT( m1[1][1] == 4 );

		TS_ASSERT( m2[0][0] == 5 );
		TS_ASSERT( m2[0][1] == 6 );
		TS_ASSERT( m2[1][0] == 7 );
		TS_ASSERT( m2[1][1] == 8 );

    }


void test_matrix_multiplication_rectangular ( )
    {
        Matrix m1( 2, 3 );
		Matrix m2( 3, 3);

		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");
		init_matrix(m2, "[ 6 7 3 ; 8 9 3 ; 3 4 5 ]");
		//std::cout << m1;
		//std::cout << m2;

		Matrix m3 = m1*m2;
    	TS_ASSERT( m3[0][0] == 31 );
		TS_ASSERT( m3[0][1] == 37 );
		TS_ASSERT( m3[0][2] == 24 );
		TS_ASSERT( m3[1][0] == 65 );
		TS_ASSERT( m3[1][1] == 77 );
		TS_ASSERT( m3[1][2] == 46 );

    	TS_ASSERT( m1[0][0] == 1 );
		TS_ASSERT( m1[0][1] == 2 );
		TS_ASSERT( m1[0][2] == 3 );
		TS_ASSERT( m1[1][0] == 3 );
		TS_ASSERT( m1[1][1] == 4 );
		TS_ASSERT( m1[1][2] == 5 );

    	TS_ASSERT( m2[0][0] == 6 );
		TS_ASSERT( m2[0][1] == 7 );
		TS_ASSERT( m2[0][2] == 3 );
		TS_ASSERT( m2[1][0] == 8 );
		TS_ASSERT( m2[1][1] == 9 );
		TS_ASSERT( m2[1][2] == 3 );
		TS_ASSERT( m2[2][0] == 3 );
		TS_ASSERT( m2[2][1] == 4 );
		TS_ASSERT( m2[2][2] == 5 );

		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
	
    }

	void test_zero_size_multiplication ( )
    {
		////std::cin.ignore();
        Matrix m1(0,0);
		Matrix m2(0,0);
		////std::cout << m2;
		////std::cout << m1;
		Matrix m3 = m1*m2;

		TS_ASSERT( m3.rows() == 0 );
		TS_ASSERT( m3.cols() == 0 );
		////std::cin.ignore();
    }


void test_zero_size_addition ( )
    {
        Matrix m1(0,0);
		Matrix m2( 0, 0);
		////std::cout << m1;
		////std::cout << m2;	
		Matrix m3 = m1+m2;

		TS_ASSERT( m3.rows() == 0 );
		TS_ASSERT( m3.cols() == 0 );
		////std::cin.ignore();
    }

	void test_zero_size_subtraction ( )
    {
        Matrix m1(0,0);
		Matrix m2( 0, 0);
		////std::cout << m1;
		////std::cout << m2;
		Matrix m3 = m1-m2;

		TS_ASSERT( m3.rows() == 0 );
		TS_ASSERT( m3.cols() == 0 );
		////std::cin.ignore();
    }


	
	void test_one_size_multiplication ( )
    {
        Matrix m1(1,1);
		Matrix m2( 1, 1);
		m1[0][0] = 4;
		m2[0][0] = 10;
		//std::cout << m1;
		//std::cout << m2;
		Matrix m3 = m1*m2;
		TS_ASSERT( m3.rows() == 1 );
		TS_ASSERT( m3.cols() == 1 );


		TS_ASSERT( m3[0][0] == 40 );
		TS_ASSERT( m1[0][0] == 4 );
		TS_ASSERT( m2[0][0] == 10 );
		////std::cin.ignore();
		
    }




	

	
	void test_one_size_addition ( )
    {
        Matrix m1(1,1);
		Matrix m2( 1, 1);
		m1[0][0] = 4;
		m2[0][0] = 10;
		//std::cout << m1;
		//std::cout << m2;
		Matrix m3 = m1+m2;
		TS_ASSERT( m3.rows() == 1 );
		TS_ASSERT( m3.cols() == 1 );


		TS_ASSERT( m3[0][0] == 14 );


		TS_ASSERT( m1[0][0] == 4 );
		TS_ASSERT( m2[0][0] == 10 );
		//std::cin.ignore();		
    }

	void test_one_size_subtraction ( )
    {
        Matrix m1(1,1);
		Matrix m2( 1, 1);
		m1[0][0] = 4;
		m2[0][0] = 10;
		//std::cout << m2;
		//std::cout << m1;
		Matrix m3 = m1-m2;
		TS_ASSERT( m3.rows() == 1 );
		TS_ASSERT( m3.cols() == 1 );

		TS_ASSERT( m3[0][0] == -6 );

		TS_ASSERT( m2[0][0] == 10 );
		TS_ASSERT( m1[0][0] == 4 );
		//std::cin.ignore();
		
    }


	void test_chain_mult ( )
    {
		Matrix m1( 2, 3 );
		Matrix m2( 3, 3);
		Matrix m3( 2, 2);		

		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");
		init_matrix(m2, "[ 6 7 3 ; 8 9 3 ; 3 4 5 ]");
		init_matrix(m3, "[ 8 5 ; 33 42 ]");

		//std::cout << m1;
		//std::cout << m2;
		//std::cout << m3;


		Matrix m4 = m3*m1*m2;

		TS_ASSERT( m4[0][0] == 573 );
		TS_ASSERT( m4[0][1] == 681 );
		TS_ASSERT( m4[0][2] == 422 );
		TS_ASSERT( m4[1][0] == 3753 );
		TS_ASSERT( m4[1][1] == 4455 );
		TS_ASSERT( m4[1][2] == 2724 );

		TS_ASSERT( m4.rows() == 2 );
		TS_ASSERT( m4.cols() == 3 );	
		//std::cin.ignore();	
    }
	
	void test_addition()
	{
		Matrix m1( 2, 3 );
		Matrix m2( 2, 3);
		Matrix m3( 2, 3);

		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");
		init_matrix(m2, "[ 6 7 3 ; 8 9 3 ]");

		//std::cout << m1;
		//std::cout << m2;

		m3 = m2+m1;

		TS_ASSERT( m3[0][0] == 7 );
		TS_ASSERT( m3[0][1] == 9 );
		TS_ASSERT( m3[0][2] == 6 );
		TS_ASSERT( m3[1][0] == 11 );
		TS_ASSERT( m3[1][1] == 13 );
		TS_ASSERT( m3[1][2] == 8 );
	
		
		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
		//std::cin.ignore();
	}


	void test_chain_addition()
	{
		Matrix m1( 2, 3 );
		Matrix m2( 2, 3 );
		Matrix m3( 2, 3 );

		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");
		init_matrix(m2, "[ 6 7 3 ; 8 9 3 ]");
		
		//std::cout << m1;
		//std::cout << m2;

		m3 = m2+m1+m1;

		TS_ASSERT( m3[0][0] == 8 );
		TS_ASSERT( m3[0][1] == 11 );
		TS_ASSERT( m3[0][2] == 9);
		TS_ASSERT( m3[1][0] == 14 );
		TS_ASSERT( m3[1][1] == 17 );
		TS_ASSERT( m3[1][2] == 13 );
	
		
		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
		//std::cin.ignore();
	}

	void test_matrix_negation()
	{
		Matrix m1( 2, 3 );
		init_matrix(m1, "[ 1 2 3 ; 4 5 6 ]");

		//std::cout << m1;
		
		Matrix m3 = -m1;

		TS_ASSERT( m3[0][0] == -1 );
		TS_ASSERT( m3[0][1] == -2 );
		TS_ASSERT( m3[0][2] == -3 );
		TS_ASSERT( m3[1][0] == -4 );
		TS_ASSERT( m3[1][1] == -5 );
		TS_ASSERT( m3[1][2] == -6 );

		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
	}
	

	void test_subtraction()
	{
		Matrix m1( 2, 3 );
		Matrix m2( 2, 3);
		Matrix m3( 2, 3);

		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");
		init_matrix(m2, "[ 6 7 3 ; 8 9 3 ]");

		//std::cout << m1;
		//std::cout << m2;


		m3 = m1-m2;

		TS_ASSERT( m3[0][0] == -5 );
		TS_ASSERT( m3[0][1] == -5 );
		TS_ASSERT( m3[0][2] == 0  );
		TS_ASSERT( m3[1][0] == -5 );
		TS_ASSERT( m3[1][1] == -5 );
		TS_ASSERT( m3[1][2] == 2 );
		
		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
	}


	void test_chain_subtraction()
	{
		Matrix m1( 2, 3 );
		Matrix m2( 2, 3 );
		Matrix m3( 2, 3 );

		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");
		init_matrix(m2, "[ 6 7 3 ; 8 9 3 ]");
		
		//std::cout << m1;
		//std::cout << m2;

		m3 = m2-m1-m1;

		TS_ASSERT( m3[0][0] == 4 );
		TS_ASSERT( m3[0][1] == 3 );
		TS_ASSERT( m3[0][2] == -3 );
		TS_ASSERT( m3[1][0] == 2 );
		TS_ASSERT( m3[1][1] == 1 );
		TS_ASSERT( m3[1][2] == -7 );
		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
	}


	void test_matrix_mult_int()
	{
		Matrix m1( 2, 3 );
		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");
		
		//std::cout << m1;

		Matrix m3 = m1 * 5;

		TS_ASSERT( m3[0][0] == 5 );
		TS_ASSERT( m3[0][1] == 10 );
		TS_ASSERT( m3[0][2] == 15 );
		TS_ASSERT( m3[1][0] == 15 );
		TS_ASSERT( m3[1][1] == 20 );
		TS_ASSERT( m3[1][2] == 25 );
		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
	}

	void test_int_mult_matrix()
	{
		Matrix m1( 2, 3 );
		init_matrix(m1, "[ 1 2 3 ; 3 4 5 ]");


		//std::cout << m1;

		Matrix m3 = 5 * m1 ;
		TS_ASSERT( m3[0][0] == 5 );
		TS_ASSERT( m3[0][1] == 10 );
		TS_ASSERT( m3[0][2] == 15 );
		TS_ASSERT( m3[1][0] == 15 );
		TS_ASSERT( m3[1][1] == 20 );
		TS_ASSERT( m3[1][2] == 25 );
		TS_ASSERT( m3.rows() == 2 );
		TS_ASSERT( m3.cols() == 3 );
	}
	
	void test_transpose(){
		Matrix m2(2,3);
		init_matrix(m2, "[ 1 -2 3 ; 3 4 -5 ]");

		//std::cout << m2;

		m2.transpose();
		
		TS_ASSERT( m2[0][0] == 1 );
		TS_ASSERT( m2[0][1] == 3 );

		TS_ASSERT( m2[1][0] == -2 );
		TS_ASSERT( m2[1][1] == 4 );

		TS_ASSERT( m2[2][0] == 3 );
		TS_ASSERT( m2[2][1] == -5 );

		
		TS_ASSERT( m2.rows() == 3 );
		TS_ASSERT( m2.cols() == 2 );
	}
	
	void test_assignment_operator(){
		Matrix m1(2,3);
		init_matrix(m1, "[ 1 -2 3 ; 3 4 -5 ]");
		Matrix m2(2,2); 
		init_matrix(m2, "[ 1 3 ; 3 -5 ]");

		//std::cout << m1;
		//std::cout << m2;

		m2 = m1;
		
		TS_ASSERT( m2[0][0] == 1 );
		TS_ASSERT( m2[0][1] == -2 );
		TS_ASSERT( m2[0][2] == 3 );

		TS_ASSERT( m2[1][0] == 3 );
		TS_ASSERT( m2[1][1] == 4 );
		TS_ASSERT( m2[1][2] == -5 );
		
		TS_ASSERT( m2.rows() == 2 );
		TS_ASSERT( m2.cols() == 3 );

		m2[0][0] = 100;

		TS_ASSERT( m1[0][0] == 1 );
		TS_ASSERT( m1[0][1] == -2 );
		TS_ASSERT( m1[0][2] == 3 );

		TS_ASSERT( m1[1][0] == 3 );
		TS_ASSERT( m1[1][1] == 4 );
		TS_ASSERT( m1[1][2] == -5 );
		
		TS_ASSERT( m1.rows() == 2 );
		TS_ASSERT( m1.cols() == 3 );

	}

	void test_utskrift(){
		Matrix m2(2,3);
		init_matrix(m2, "[ 1 -2 3 ; 3 4 -5 ]");
	

		std::cout<<m2;
		std::cout<<m2;
		TS_ASSERT( m2[0][0] == 1 );
		TS_ASSERT( m2[0][1] == -2 );
		TS_ASSERT( m2[0][2] == 3 );

		TS_ASSERT( m2[1][0] == 3 );
		TS_ASSERT( m2[1][1] == 4 );
		TS_ASSERT( m2[1][2] == -5 );
		
		TS_ASSERT( m2.rows() == 2 );
		TS_ASSERT( m2.cols() == 3 );
	}

	void test_plus_then_plus(){
		Matrix m1,m2,m3,m_o1,m_o2,m_result;

		init_matrix(m1, "[ 2 3 ; 3 4 ]");
		init_matrix(m2, "[ 7 3 ; 4 2 ]");		
		init_matrix(m3, "[ 3 4 ; 1 4 ]");

		init_matrix(m_result, "[ 12 10 ; 8 10 ]");
		
		m_o1 = m1 + m2;
		m_o2 = m_o1 + m3;


		TS_ASSERT( checkEqualMatrix(m_o2, m_result ) );
	}

	void test_plus_then_times(){
		Matrix m1,m2,m3,m_o1,m_o2,m_result;


		init_matrix(m1, "[ 2 3 ; 3 4 ]");
		init_matrix(m2, "[ 7 3 ; 4 2 ]");	
		init_matrix(m3, "[ 2 2 3 ; 1 3 7 ]");

		init_matrix(m_result, "[ 24 36 69 ; 20 32 63 ]");
		
		m_o1 = m1 + m2;
		m_o2 = m_o1 * m3;


		TS_ASSERT( checkEqualMatrix(m_o2, m_result ) );
	}

	void test_plus_then_minus(){
		Matrix m1,m2,m3,m_o1,m_o2,m_result;

		init_matrix(m1, "[ 2 3 ; 3 4 ]");
		init_matrix(m2, "[ 7 3 ; 4 2 ]");		
		init_matrix(m3, "[ 3 4 ; 1 4 ]");

		init_matrix(m_result, "[ 6 2 ; 6 2 ]");
		
		m_o1 = m1+m2;
		m_o2 = m_o1-m3;

		TS_ASSERT( checkEqualMatrix(m_o2, m_result ) );
	}

	void test_times_then_plus(){
		Matrix m1,m2,m3,m_o1,m_o2,m_result;

		init_matrix(m1, "[ 2 2 3 ; 1 3 7 ]");
		init_matrix(m2, "[ 5 3 ; 6 7 ; 3 6 ]");		
		init_matrix(m3, "[ 3 4 ; 1 4 ]");

		init_matrix(m_result, "[ 34 42 ; 45 70 ]");
		
		m_o1 = m1*m2;
		m_o2 = m_o1 + m3;


		TS_ASSERT( checkEqualMatrix(m_o2, m_result ) );
	}
};

#endif // MATRIX_TEST_H_INCLUDED
