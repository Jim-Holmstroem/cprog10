#include<iostream>
using namespace std;

class A{
	public:
		char * str;
		A()
			{cout<<"Object 1"<<endl;}
		A(const A &)
			{cout<<"Object 2"<<endl;}
		~A()	// destructor
			{cout<<"Object 3"<<endl;}
		A(char *s)
			{cout<<"Object 4"<<endl;}
		A &operator=(const A &s)
			{cout<<"Object 5"<<endl;
			return *this;}
};

	void no_ref(A a){}
	void with_ref(const A &a){}

int main() {

	int i = 0;

	cout << "seg" << i++ << endl;

	A a("my name is a"); //constructor nr 4
	cout << "&a: " << &a << endl;

	A b = a;			//direct-initialization
	cout << "&b: " << &b << endl;

	A c(a);				//copy-initialization, nästan aldrig någon skillnad kan bli annorlunda om du gör komplexa klasser, i dethär fallet är det ingen skillnad(förutom syntaxen^^)
	cout << "&c: " << &c << endl;

	A d;				// default constructor
	d = a;				// assignment operator
	cout << "&d: " << &d << endl;


	cout << "seg" << i++ << endl;

	A *aa = new A[5];   // 5 st obj 1

	cout << "seg" << i++ << endl;

	//delete aa;			//Vad kommer att hända? 3, segmentation fault (om man har tur som vi hade) odefinerat beteende att deleta en array korrekt vorre att skriva: delete [] aa;

    delete [] aa;

	cout << "seg" << i++ << endl;

	cout << "no_ref:" << endl;
	no_ref(a);			//Bildas temporära objekt? Ja det kommer bildas en kopia av objektet
	cout << "w_ref:";	
	with_ref(a);		//Bildas temporära objekt? Nej en kopia av pekaren till objektet skapas bara, det kommer alltså inte skapas ngt nytt A

	return 0;
}
