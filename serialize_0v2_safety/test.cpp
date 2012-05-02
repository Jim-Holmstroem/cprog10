#include<iostream>
#include<fstream>
#include "test.h"



int main(){

    A a = A(13,37,"leet");
    A a_cp;

    B b;
    B b_cp;
    A* ba = new B();

    MiniA miniA;
    MiniA miniA_cp;

/*
    std::cout << b << std::endl;

    std::ofstream outFile("saved/test_b.dat");
    outFile << b;
    outFile.close();
    
    std::ifstream inFile("saved/test_b.dat");
    inFile >> b_cp;
    inFile.close();


    std::cout << b_cp << std::endl;
*/

    std::cout << b << std::endl;

    std::ofstream outFile("saved/test_miniA.dat");
    outFile << miniA;
    outFile.close();
    
    std::ifstream inFile("saved/test_miniA.dat");
    inFile >> miniA_cp;
    inFile.close();


    std::cout << b_cp << std::endl;

   // std::cout << *ba << std::endl; //TODO y u mad ?




    //std::cout << b << std::endl;    
    //std::cout << ba << std::endl;    

    delete ba;

}


