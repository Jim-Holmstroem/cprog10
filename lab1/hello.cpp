#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>

using namespace std;

void helloRepeat(int n=1, string str="world"){
    string repeat = "";
    for(int i=0;i<n;i++)
        repeat+=(' '+str);
    cout << "Hello" << repeat << endl;
}

bool isNumber(const char * a){
    if(atoi(a)==0)
        if(strcmp(a, "0") == 0)
            return true;
        else
            return false;
    else
        return true;
}

int main(int argc, char *argv[]) {

    cout <<"argv0: " << argv[0] << endl;

    switch(argc){
        case 3:
            if(isNumber(argv[1]) && !isNumber(argv[2])){
                helloRepeat(atoi(argv[1]),argv[2]);
            }else{
                cout << "invalid params" << endl;
            }
            break;
        case 2:
            if(isNumber(argv[1])){
                helloRepeat(atoi(argv[1]),"world");
            }else{
                helloRepeat(1,argv[1]);
            }
            break;
        case 1:
            helloRepeat();
            break;
        default:
            cout << "wrong number of arguments" << endl;
            return 1;
            break;
    }

    return 0;

}
