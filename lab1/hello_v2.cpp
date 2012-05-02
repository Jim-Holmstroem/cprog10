#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

void helloRepeat(int n=1, char* str[]="world") { //"world" == pekaren på {"h", "e", ....} 
	cout << "Hello";	
	for(int i=0;i<n;i++)
		cout << str;
	cout << endl;
}

bool isNumber(const char * a){
	if(atoi(a)==0)
		if(a=="0")
			return true;
		else
			return false;
	else
		return true;
			
			//if atoi==0
				//if =="0"
					//handle as n=0
				//else 
					//handle as text
			//if atoi==n
				//handle as number

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
				helloRepeat( ,argv[1]);
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











/*	if(argc==1)
		cout<<"Hello world!"<<endl;
	else if( atoi(argv[1]) ==0)
		cout<<"Hello "<<argv[1]<<"!"<<endl;
	else if( atoi(argv[1]) !=0) {
		cout<<"Hello";
		for(int i=0; i<atoi(argv[1]); i++)
			cout<<" world";
		cout<<"!"<<endl;
		}
	else if(atoi(argv[1])!=0 && atoi(argv[2])==0) {
		cout<<"Hello ";
		for(int i=0; i<atoi(argv[1]); i++)
			cout<<" "<<argv[2];
		cout<<"!"<<endl;
		}
	else
		return 0;
	return 0;*/

