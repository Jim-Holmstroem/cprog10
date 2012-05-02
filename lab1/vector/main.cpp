#include "main.h"


using namespace std;
typedef unsigned int uint;


int main(int argc, char **argv){

    Vector v(4);
    
    try{
    
      cout << "in main: v[1]=" << v[1] << endl;
        
    } catch(std::out_of_range e){   
    
       cout<<"OUT OF RANGE DUDE!!1oneoneeleven"<<endl;
   }


    v[2] = 1337;
    
    Vector b = v;
    
    Vector a;
    v = v;
    a = v;
    a[0] = 13;

    

    return 0;
}
