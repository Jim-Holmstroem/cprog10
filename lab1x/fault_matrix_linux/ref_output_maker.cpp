#ifndef REF_OUTPUT_MAKER
#define REF_OUTPUT_MAKER

#include "matrix.h"
#include <iostream>
#include <sstream>

int main( int argc, const char* argv[]){

    if(argc!=2){
        std::cerr << (argc-1) << " isn't the right number of arguments, need to have =1" << std::endl;
        return 1;
    }
    
    int max_size = 0;
    std::stringstream max_size_str(argv[1]);
    max_size_str >> max_size;
   
    for(int j=1;j<max_size;j++){
        for(int i=1;i<max_size;i++){
            Matrix c(i,j);
            for(int k=0;k<c.cols();k++){
                for(int l=0;l<c.rows();l++){
                    c[l][k] = l + c.rows()*k + 1; //labels all the positions in the matrix beginning in the first dimension (rows)
                }
            }
            std::cout << c;
        }
    }
    
    return 0;    

}
#endif
