#include "main.h"
#include "vector.h"
#include <iomanip>

int main(int argc,char * argv[]){

    char buff[33];
/*
  for(unsigned int i=0;i<2048;++i){
  helper::itoa2rev(buff,i);
  std::cout << std::setw(4) << i << " in binary: " << buff << std::endl;
  }
*/
    Vector<bool> vb;
    for(unsigned int i=0;i<2048;i++){
        vb.clear();
        vb = i;
        helper::itoa2(buff,static_cast<unsigned int>(vb));
        std::cout << std::setw(4) << i << "set and back-casted to " << static_cast<unsigned int>(vb) << " : " << buff << std::endl;
        vb.print();
    }

    vb.clear();
    vb.print();
    std::cout << "Back-casted to " << static_cast<unsigned int>(vb) << std::endl;

/*
  for(unsigned int i=0;i<32;i++){
  unsigned int mask = -1; //biggest number
  mask <<= i;
  mask = ~mask;
  helper::itoa2(buff,mask);
  std::cout << std::setw(2) << i << "'s mask is: " << buff << std::endl;
  }
*/
    Vector<bool> vec;
    vec = 1337;
    vec.print();//should print out #32/32[00000000000000000000010100111001] //but it doesnt

    helper::itoa2(buff,1337);
    std::cout << "helper::itoa2(1337): " << buff << std::endl;

    unsigned int a;
    vec.clear();

    while(1){
        std::cin >> a;
        vec.push_back(static_cast<bool>(a));
        std::cout << "static_cast<insigned int>(vec): " << static_cast<unsigned int>(vec) << std::endl;
        vec.print();


        //Vector<bool> test(vec);
        //test.print();


        //for (std::size_t i = 0;i < 32; i++){
        //    buff[i] = (i%10+48);
        //}
        //buff[32] = '\000';

        //helper::itoa2(buff,a);
        //std::cout << ">" << buff << std::endl;


        // for(std::size_t i = 0;i!=vec.size();++i){
        //     std::cout << i << ">" << vec[i] << std::endl;
        // }

    }
    return 0;
}
