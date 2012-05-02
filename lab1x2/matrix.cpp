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

Matrix::Matrix(int size): m_vectors(), m_rows(size), m_cols(size){ //identity matrix
#ifdef DMATRIX
    std::cout << "in Matrix::Matrix(int size):" << std::endl;
#endif

    int idpos;
    for(std::size_t i = m_rows; i>0; --i){
        m_vectors.push_back(matrix_row(m_cols));
        //m_vectors[i](m_cols);
        idpos = m_rows-i;
        m_vectors[idpos][idpos] = 1;
    }
}

Matrix::~Matrix(){
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

Matrix& Matrix::read(const char** data){
    m_vectors.clear();
    m_rows = 0;
    while(data[m_rows]!='\0'){
        m_rows++;
    }
    m_cols = strlen(data[0]);

    for(std::size_t i=0; i<m_rows; i++){
        m_vectors.push_back(matrix_row(m_cols));
        for(std::size_t j=0; j<m_cols; j++){
            (*this)[i][j] = data[i][j];
        }
    }
    return *this;
}

bool Matrix::solve(){ //order of search: up, left, down, right
    std::size_t rownr = 0;
    std::size_t colnr = 0;
    bool foundStart = false;
    this->mark_exit();
    for(std::size_t i=0; i<m_rows; i++){
        for(std::size_t j=0; j<m_cols; j++){
            if((*this)[i][j] == 'E'){
                rownr=i;
                colnr=j;
                (*this)[i][j] = 'S'; //start
                foundStart = true;
                break;
            }
        }
        if(foundStart){
            break;
        }
    }
    if(foundStart){
        return goto_path(rownr, colnr);
    }
    else{
        std::cerr<<"in solve: no entrance found"<<std::endl;
        return false;
    }
}

bool Matrix::goto_path(size_t rownr, size_t colnr){
    std::string dummy;
#ifdef DMAZE
    std::cout <<"in goto_path: "<<"rownr="<< rownr <<" colnr="<< colnr << std::endl;
#endif
    // std::cout << (*this) << std::endl;
    // std::cin >> dummy;

    if(rownr<0 || rownr>(m_rows-1) || colnr<0 || colnr>(m_cols-1) ){ //out_of_range, important to check first before trying to access a certain element in the matrix
        return false;
    }

    char* path = &(*this)[rownr][colnr];
    if(*path == '#' || *path == '.'){ //invalid paths
        return false;
    }
    if(*path == 'E'){ //found the exit
        *path = '.';
        return true;
    }
    else{ //only option left is path == ' ' (whitespace)
        *path = '.';

        if(goto_path(rownr-1, colnr)){ //up
            return true;
        }
        if(goto_path(rownr, colnr-1)){ //left
            return true;
        }
        if(goto_path(rownr+1, colnr)){ //down
            return true;
        }
        if(goto_path(rownr, colnr+1)){ //right
            return true;
        }
        *path = ' ';
        return false;
    }
}
Matrix& Matrix::mark_exit(){
    for(std::size_t i=0; i<m_cols; i++){
        if((*this)[0][i] == ' '){
            (*this)[0][i] = 'E'; //entrance/exit represented with E
        }
        if((*this)[m_rows-1][i] == ' '){
            (*this)[m_rows-1][i] = 'E';
        }
    }
    for(std::size_t i=0; i<m_rows; i++){
        if((*this)[i][0] == ' '){
            (*this)[i][0] = 'E'; //entrance/exit represented with E
        }
        if((*this)[i][m_cols-1] == ' '){
            (*this)[i][m_cols-1] = 'E';
        }
    }
    return *this;
}
