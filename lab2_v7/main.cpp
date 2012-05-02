#include "main.h"
#include <cassert>

using namespace std;


int main(int argc,char * argv[]){

    char dummy = 0;
    dummy++;

    #ifdef OPERATIONS
//**************************************************************************
    lab2::Gregorian d1(2010,10,11);
    cout <<"in main: d1=" << d1 << endl;

    cout<<"in main: Week day="<< d1.week_day() << d1.week_day_name() << endl;
    cout<<"in main: days_this_month()="<< d1.days_this_month() << endl;
    cout<<"in main: months_per_year()="<< d1.months_per_year()<<endl;


    lab2::Gregorian d2 = d1;
    d2.add_month();
    cout <<"in main: d2=" << d2 << endl;
    cout<<"in main: d2-d1="<< d2-d1 << endl;

    //int num = d2.mod_julian_day(); //vi kan inte skriva detta längre när vi har satt const på slutet av mod_julian_day(), blev tvungen att göra det för att vi anropade denna fkn med const referenser
    cout <<"d2: julian day number=" << d2.mod_julian_day() << endl;

    lab2::Gregorian d3(1989,5,2);
    cout <<"in main: d3="<< ++d3 << endl; //obs ++d3
    d1=d3;
    cout<<"in main: d1="<< d1 << endl;
    cout<<"in main: (d1==d3) ="<< (d1==d3) << endl;
    d3.add_month(9);
    cout<<"in main: d3="<< d3 << endl;

    cout<<"in main: (d1!=d3) ="<< (d1!=d3) <<endl;
    cout<<"in main: (d1<d3) ="<< (d1<d3) <<endl;
    cout<<"in main: (d1>d3) ="<< (d1>d3) <<endl;
    cout<<"in main: (d1<=d3) ="<< (d1<=d3) <<endl;
    cout<<"in main: (d1>=d3) ="<< (d1>=d3) <<endl;

//************************************************************************
    #endif




    #ifdef ADDSUB
//************************************************************************

    lab2::Gregorian da(11,5,31); //a day on a year before a leapyear (oh yeah)

    cout << "+/- i=0:10" << endl;


    cout << "current date:" << da << endl;
    for(int i=0;i<10;i++){
        da+=i;
        cout <<"[+" << i << "]" << endl;
        cout << da<< endl;
    }

    for(int i=0;i<10;i++){
        da-=i;
        cout <<"[-" << i << "]" << endl;
        cout << da<< endl;
    }

    cout << "+/- 31/20 test " << endl;

    for(int i=0;i<10;i++){
        da+=31;
        cout <<"[+" << 31 << "]" << endl;
        cout << da<< endl;
    }

    for(int i=0;i<10;i++){
        da-=20;
        cout <<"[-" << 20 << "]" << endl;
        cout << da << endl;
    }


//************************************************************************
    #endif

    #ifdef TEST365

    lab2::Gregorian dt(11,5,31);
    cout << "current date:" << dt << endl;
    cout << "365day test" << endl;

    for(int i=0;i<365;i++){
        ++dt;
        cout << dt <<"[++]" << endl;
    }

    cin >> dummy;

    for(int i=0;i<365;i++){
        --dt;
        cout << dt <<"[--]" << endl;
    }

    dt+=365;
    cout << dt <<"[+=365]" << endl;
    dt-=365;
    cout << dt <<"[-=365]" << endl;


//*************************************************************************
    #endif



    #ifdef ADDMONTH

//*************************************************************************

    lab2::Gregorian dr(2012,4,30);
    cout << "current date" << dr << endl;

    int adds[] = {1,1,1,43,-43,-24,24,-3,-7};

    for(int i = 0;i!=len(adds);i++){
        cout <<"[add_month(" << adds[i]  << ")]..."; cout.flush();
        dr.add_month(adds[i]);
        cout << "OK" << endl;
        cout << dr << endl;
        cin >> dummy;
    }


//*************************************************************************

    #endif


    #ifdef ADDYEAR

//*************************************************************************

    lab2::Gregorian dy(800,2,29);

    int addsy[] = {400,1,-1,4,96};

    for(int i = 0;i!=len(addsy);i++){
        dy.add_year(addsy[i]);
        cout << dy <<"[add_year(" << addsy[i]  << ")]" << endl;
    }


//*************************************************************************

    #endif

    #ifdef GREGJUL
    //Test between Greg and Jul
    lab2::Gregorian gt(1,1,1);
    lab2::Julian jt(1,1,3);
    cout << "gt week day = "<< gt.week_day() << " jt week day = "<< jt.week_day() << endl;

    lab2::Gregorian g;
    lab2::Julian j;
    cout << "Today it is " << g << " gregorian and " << j << " julian"<< endl;;
    cout << "Greg JDN = "<< g.mod_julian_day() << " Jul JDN = "<< j.mod_julian_day() << endl;
    cout << "Greg week day = "<< g.week_day_name() << " Jul week day = "<< j.week_day_name() << endl;
    if(g - j == 0){
        cout << "It is the same date" << endl;
    }
    g = j;
    if (g == j){
        cout << "It is still the same date" << endl;
        cout << "g = " << g << " j = " << j << endl;
    }
    lab2::Julian j2(12,2,29);
    lab2::Gregorian g2(j2);
    if (g2 == j2){
        cout << "Jul to Greg works" << endl;
        cout << "g2 = " << g2 << " j2 = " << j2 << endl;
    }
    cout << g2.week_day() << endl;
    if (j2.week_day() == 5){
        cout << "Freaky Friday!!!" << endl;
    }
    lab2::Gregorian g3(1600,2,29);
    lab2::Julian j3;
    j3 = g3;
    if (j3 == g3){
        cout << "Greg to Jul works as well" << endl;
    }
    g2 = g3;
    
    lab2::Julian jkat(2319,1,23);
    lab2::Julian* jptr = &jkat;
    lab2::Gregorian gkat(&jkat);
    cout<<"gkat: "<< gkat <<"jkat: "<< jkat << endl;
    lab2::Gregorian gtest;
    cout<<gtest<<endl;
    gtest = jptr;
    cout<<gtest<<endl;

    #endif
//*************************************************************************

    #ifdef CAL

    lab2::Calendar<lab2::Gregorian> cal;
    cout << cal.cur_date << endl;

    cal.set_date(2000,12,2);
    cout << cal.cur_date << endl;
    cal.add_event("Basket",4,12,2000);
    cal.add_event("Basket",11,12,2000);
    cal.add_event("Nyår",1,1,2001);
    cal.add_event("Första advent",1);
    cal.add_event("Vårdagsjämning",20,3);
    cal.add_event("Julafton",24,12);

    cal.add_event("Kalle Anka",24);
    cal.add_event("Julafton",24);
    cal.add_event("Min första cykel",20,12,2000);
    cal.remove_event("Basket",4);
    cout << cal << endl;
    cout << "---------------------------"<< endl;
    cal.remove_event("Vårdagsjämning",20,3,2000);
    cal.remove_event("Kalle Anka",24,12,2000);
    cal.set_date(2000,11,2);
    if(!cal.remove_event("Julafton",24)){
        cout<<"cal.remove_event(\"Julafton\",24) tar inte"<< endl << " bort något eftersom aktuell månad är november" << endl;
    }
    cout << "---------------------------"<< endl;
    cout << cal;


    lab2::Event<lab2::Gregorian> e1("Leet",13,3,7);

    lab2::Event<lab2::Gregorian> e2("Leet",13,3,7);

    cout << "is equal = " << (e1==e2) << endl;

    lab2::Calendar<lab2::Julian> cal2(cal);
    cout << cal2 << endl;
    lab2::Calendar<lab2::Gregorian> cal3;
    cal3 = cal2;
    cout << cal3 << endl;

    #endif

    return 0;
};
