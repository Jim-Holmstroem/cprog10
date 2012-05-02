#include "main.h"


using namespace std;


int main(int argc, char **argv){

    #ifdef DEBUG
        cout << "DEBUGGING ON!!1" << endl;
    #endif

    Vector<int> v(10,8); //noll vector

    v.print();

    for(size_t i=0;i<2;++i)
        v.push_back(8+i+1);

  // v[2] = 's';

    Vector<int> b = v;

    Vector<int> a;
    v = v;
    a = v;
    a[0] = 1337;

    v.print();
    //a.print();

    v.insert(5,5);
    v.insert(1,1);

    //RV
    v.insert(0,0);
    v.insert(v.size(),1337);

    v.sort(true);

    v.print();

  //  v.clear();

  //  v.print();

//    for(size_t i=0;i<20;++i){
//        v.erase(0);
//    }






    try{

        cout << "in main v[2]=" <<  v[2] << endl;

       } catch(std::out_of_range e){

       cout<<"OUT OF RANGE DUDE!!1oneoneeleven"<<endl;
   }

    return 0;
}
