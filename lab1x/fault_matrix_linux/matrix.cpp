#include "matrix.h"
#include<cstdlib>

Matrix::Matrix(): m_vectors(), m_rows(0), m_cols(0){
    #ifdef DMATRIX
  std::cout << "in Matrix::Matrix()" << std::endl;
  #endif
}

Matrix::Matrix(std::size_t rows, std::size_t cols): m_vectors(), m_rows(rows), m_cols(cols){
       if((m_cols==0 || m_rows==0)){
	 m_cols = m_rows = 0;
       }
    #ifdef DMATRIX
    std::cout << "in Matrix::Matrix(size_t, size_t):" << std::endl;
    std::cout << "m_rows=" << m_rows << " m_cols=" << m_cols << std::endl;
    #endif
        
    for(std::size_t i = m_rows; i>0; --i){
        #ifdef DMATRIX
        
        #endif
        m_vectors.push_back(matrix_row(m_cols));
        //m_vectors[i](m_cols);
    }
}

Matrix::Matrix(const Matrix& copy){
    #ifdef DMATRIX
    std::cout << "in Matrix::Matrix(const Matrix&):" << std::endl;
    #endif
    m_rows = copy.rows();
    m_cols = copy.cols();
    m_vectors = m_rows;
    for(std::size_t i=0; i<m_rows; i++){
        #ifdef DMATRIX
        std::cout<<":" << i;
        std::cout.flush();
        #endif
                
        m_vectors[i] = copy[i];
    }
}


Matrix::Matrix(int size): m_vectors(), m_rows(size), m_cols(size) { //identity matrix
    #ifdef DMATRIX
    std::cout << "in Matrix::Matrix(int size):" << std::endl;
    #endif

    int idpos;
    for(std::size_t i = m_rows; i>0; --i){
        #ifdef DMATRIX
        
        #endif
        m_vectors.push_back(matrix_row(m_cols));
        //m_vectors[i](m_cols);
	idpos = m_rows-i;
	m_vectors[idpos][idpos] = 1;
    }
    
}

Matrix::~Matrix(){

}

Matrix& Matrix::transpose(){ 
      Vector< matrix_row > m_trans; //create a new matrix with the switched dimension
      for(std::size_t i=0; i<m_cols; i++){ // dimension of matrix pre-transpose
      m_trans.push_back(matrix_row(m_rows));
      }
      for(std::size_t i=0; i<m_rows; i++){ // dimension of matrix pre-transpose
	for(std::size_t j=0; j<m_cols; j++){
	  m_trans[j][i] = (*this)[i][j];
	}
      }
      int tmp;
      tmp = m_rows;
      m_rows = m_cols; // change the dimension to matrix pro-transpose
      m_cols = tmp;
      m_vectors = m_trans;
      return *this;
}


Matrix& Matrix::operator=(const Matrix& copy){ 
  #ifdef DMATRIX
  std::cout << "in Matrix::operator=" << std::endl;
  #endif

    m_rows = copy.rows();
    m_cols = copy.cols();
    
    Vector<matrix_row> temp(m_rows);
    for(std::size_t i=0; i<m_rows; i++){
        temp[i] = copy[i];
    }
    
    m_vectors = temp;
    
    return *this;
}
//addition
Matrix Matrix::operator+ (const Matrix& m) const{
  #ifdef DMATRIX
  std::cout << "in Matrix::operator+" << std::endl;
  #endif
  if(this->m_rows != m.rows() || this->m_cols != m.cols()){
    throw std::out_of_range("operator+: different matrix sizes");
  }
  Matrix tmp(m.rows(), m.cols());

  for(std::size_t i=0; i<m.rows(); i++){
    for(std::size_t j=0; j<m.cols(); j++){
      tmp[i][j] = (*this)[i][j] + m[i][j];
    }
  }
  return tmp;
}
//matrix multiplication
Matrix Matrix::operator* (const Matrix& m) const{
  #ifdef DMATRIX
  std::cout << "in Matrix::operator*(const Matrix&)" << std::endl;
  #endif
  if(this->m_cols != m.rows()){
    throw std::out_of_range("operator*(const Matrix&): matrix sizes not supported");
  }
  std::size_t r(this->m_cols);
  Matrix tmp(this->m_rows, m.cols());
  
  for(std::size_t i=0; i<tmp.rows(); i++){ //for all (i,k)
    for(std::size_t k=0; k<tmp.cols(); k++){
      
      for(std::size_t j=0; j<r; j++){ //sum over j: T_ij*T_jk
	       tmp[i][k] += (*this)[i][j] * m[j][k];
      }
    }
  }
  return tmp;
}
//scalar multiplication
Matrix Matrix::operator* (int a) const{
  #ifdef DMATRIX
  std::cout << "in Matrix::operator*(int)" << std::endl;
  #endif
  Matrix tmp(this->m_rows, this->m_cols); //TODO: if possible do not use tmp and return *this
  for(std::size_t i=0; i<this->m_rows; i++){
    for(std::size_t j=0; j<this->m_cols; j++){
      tmp[i][j] = a * (*this)[i][j];
      //(*this)[i][j] = a * (*this)[i][j];
      //(*this)[i][j] *= a;
    }
  }
  return tmp;
}
//subtraction
Matrix Matrix::operator-(const Matrix& m) const{
  #ifdef DMATRIX
  std::cout << "in Matrix::operator-(const Matrix&)" << std::endl;
  #endif
  if(this->m_rows != m.rows() || this->m_cols != m.cols()){
    throw std::out_of_range("operator-(const Matrix&): different matrix sizes");
  }
  return( *this + (-m) );
}
//negative operation
Matrix Matrix::operator-( ) const{
  #ifdef DMATRIX
  std::cout << "in Matrix::operator-():" << std::endl;
  #endif
  return (-1)*(*this); //uses operator*(int, const Matrix&)
}

Matrix::matrix_row& Matrix::operator[](index i){
    return m_vectors[i];
}

const Matrix::matrix_row& Matrix::operator[](index i) const{
    return m_vectors[i];
}

std::size_t Matrix::rows() const{
    return m_rows;
}

std::size_t Matrix::cols() const{
    return m_cols;
}

//global operator
Matrix operator*(int a, const Matrix& m){
  #ifdef DMATRIX
  std::cout << "in Matrix::operator*(int, const Matrix&)" << std::endl;
  #endif
  return m*a; //uses Matrix::operator*(int)
}

std::ostream& operator<<(std::ostream& out, Matrix& m){
    
    out << "[ ";
    for(std::size_t i=0; i<m.rows(); i++){
        if(i!=0){
            out << "; ";
        }
        for(std::size_t j=0; j<m.cols(); j++){
            out << m[i][j] << ' ';
        }
        if(i!=(m.rows()-1)){
            out << std::endl;
        }
    }
    out << "]" << std::endl;
    
    return out;

}


std::istream& operator>>(std::istream& in, Matrix& m){
  std::string tmp;
  in >> tmp;
  /*while(strcmp(tmp.c_str(), "]") != 0){
    if(strcmp(tmp.c_str(), "[") == 0){
        m.m_vectors.clear();
	m.m_rows = 0;
	m.m_cols = 0;
        m.m_vectors.push_back( Matrix::matrix_row() );
    }
    else if(strcmp(tmp.c_str(), ";") == 0){
        m.m_vectors.push_back( Matrix::matrix_row() );
    }
    else{
        m.m_vectors[m.m_vectors.size()-1].push_back( atoi(tmp.c_str()) );
pp    }
    in >> tmp;
  }
  m.m_rows = m.m_vectors.size();
  m.m_cols = m.m_vectors[0].size();
  return in;*/

     if(strcmp(tmp.c_str(), "]") == 0){
       m.m_rows = m.m_vectors.size();
       m.m_cols = m.m_vectors[0].size(); //size of the first matrix_row, so if input [ 1 2 ; 3 ] then calling m[1][1] will throw out_of_range
      
       if((m.m_cols==0||m.m_rows==0)){ // if input [ ; ; ; ] then it should be a 0x0 matrix
	 m.m_cols = m.m_rows = 0;
	 m.m_vectors.clear();
       }

       return in; // när man kommer till slutet av matrisen returnera det som är kvar :)
    }
    else if(strcmp(tmp.c_str(), "[") == 0){
        m.m_vectors.clear();
        m.m_vectors.push_back( Matrix::matrix_row() ); // if input "[ ]" (empty matrix) then m_vectors.cur_size = 1. bad? otherwise m.m_cols = m.m_vectors[0].size() won't work
        return(in >> m);
    }
    else if(strcmp(tmp.c_str(), ";") == 0){
        m.m_vectors.push_back( Matrix::matrix_row() );
        return(in >> m);
    }
    else{ // read a number
        m.m_vectors[m.m_vectors.size()-1].push_back( atoi(tmp.c_str()) );
        return(in >> m);
    }
}
