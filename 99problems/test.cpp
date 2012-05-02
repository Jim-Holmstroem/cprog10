#include <iostream>
#include <string>


using namespace std;

class ISerializable
{

public:
    class Content
    {
    };
    Content content;

    friend ostream& operator << (ostream& out,const Content& cont)
    {
        out << "Content";
        return out;
    };

    friend ostream& operator << (ostream& out,const ISerializable& obj){
        out << "{ " << obj.content << " }" ;
        return out;
    };
};
/*
ostream& operator << (ostream& out,const ISerializable& obj)
{
    out << "{ " << obj.content << " }" ;
    return out;
};
*/

class A : virtual public ISerializable{

public:
    friend ostream& operator << (ostream& out,const A::Content& cont){
        out << "A::Content";
        return out;
    };

};
/*
  ostream& operator << (ostream& out,const A::Content& cont)
  {
  out << "A::Content";
  return out;
  };
*/
class AB : public A{

public:
    friend ostream& operator << (ostream& out,const AB::Content& cont){
        out << "AB::Content";
        return out;
    };

};
/*
  ostream& operator << (ostream& out,const AB::Content& cont)
  {
  out << "AB::Content";
  return out;
  };
*/


int main(int argc,const char* argv[]){
    A a;

    std::cout << a << std::endl;


    return 0;
}
