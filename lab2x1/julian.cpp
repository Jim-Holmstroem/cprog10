#include "julian.h"

using namespace std;

const int MONTHS_PER_YEAR = 12;
const int DAYS_PER_WEEK = 7;
enum Month_days {january=31,february=28,march=31,april=30,may=31,june=30,july=31,august=31,september=30,october=31,november=30,december=31};

lab2::Julian::Julian(){
#ifdef DEBUG
    cout << "in Julian()" << endl;
#endif

    setCurrentDate();
};

lab2::Julian::Julian(int year,int month,int day):Date(year,month,day){
#ifdef DEBUG
    cout << "in Julian(int,int,int): "<< endl;
#endif

    if(isDateOutOfRange() ){
        throw out_of_range("OOR!");
    }
};

lab2::Julian::Julian(const Date& d) {
#ifdef DEBUG
    cout << "in Julian(const Date&): "<<endl;
#endif
    _year = d.year();
    _month = d.month();
    _day = d.day();
    *this += (d.mod_julian_day() - this->mod_julian_day() ); //convert from arbitrary Date class(e.g. Gregorian) to Julian
};

lab2::Julian::Julian(const Date* d) {
#ifdef DEBUG
    cout << "in Julian(const Date*): "<<endl;
#endif
    _year = d->year();
    _month = d->month();
    _day = d->day();
    *this += (d->mod_julian_day() - this->mod_julian_day() );
};

lab2::Julian::~Julian(){};

lab2::Julian& lab2::Julian::operator=(const Date& d){
#ifdef DEBUG
    cout<<"in Julian::operator="<< endl;
#endif
    if(this != &d){ //to avoid self assignment
        _year = d.year();
        _month = d.month();
        _day = d.day();

#ifdef DEBUG
        cout << "The difference is " << d.mod_julian_day() - this->mod_julian_day() << " days" << endl;
#endif

        *this += ( d.mod_julian_day() - this->mod_julian_day() ); //convert to Julian
    }
    return *this;
};

void lab2::Julian::setCurrentDate(){
    time_t mytime;
    time(&mytime);
#ifndef DEBUG //OBS if not DEBUG
    //manually set the kattistime(kattis will handle this later)
    set_k_time(mytime);
    k_time(&mytime);
    struct tm* t = gmtime(&mytime);
    _year  = t->tm_year + 1900;
    _month = t->tm_mon + 1;      // index from 0
    _day   = t->tm_mday;         // index from 1
#else
    //local code to get current Gregorian time
    //http://www.utas.edu.au/infosys/info/documentation/C/CStdLib.html#time.h
    struct tm* timeinfo = localtime(&mytime);
    _year = timeinfo->tm_year + 1900;
    _month = timeinfo->tm_mon + 1;
    _day = timeinfo->tm_mday;
#endif
    //convert from Gregorian to Julian by adding the difference of number of days by looking at MJD
    *this += ( this->mod_julian_day_for_greg() - this->mod_julian_day() );
};

int lab2::Julian::week_day() const{
    //since mod_julian_day is negative for dates before Julian(1858-11-5) we use an early monday (in this case 01-01-03) as a reference
    int mjd_010103 = -678575;
    return (mod_julian_day() - mjd_010103 )% 7 + 1;
};

const int lab2::Julian::days_per_week() const{
    return DAYS_PER_WEEK;
};

const int lab2::Julian::months_per_year() const{
    return MONTHS_PER_YEAR;
};

string lab2::Julian::week_day_name() const{
    switch( week_day() ){
        case 1: return "monday";
        case 2: return "tuesday";
        case 3: return "wednesday";
        case 4: return "thursday";
        case 5: return "friday";
        case 6: return "saturday";
        case 7: return "sunday";
        default: cerr << "not a week day" << endl; return "not_a_weekday!!1";
    }
};

string lab2::Julian::month_name() const{
    switch(_month){
        case 1: return "january";
        case 2: return "february";
        case 3: return "march";
        case 4: return "april";
        case 5: return "may";
        case 6: return "june";
        case 7: return "july";
        case 8: return "august";
        case 9: return "september";
        case 10: return "october";
        case 11: return "november";
        case 12: return "december";
        default: cerr << "not a month" << endl;return "not_a_month!!1";
    }
};

int lab2::Julian::days_this_month() const{
    switch(_month){
        case 1: return Month_days(january);
        case 2: if(leap_year())
            return Month_days(february) + 1;
        else
            return Month_days(february);
        case 3: return Month_days(march);
        case 4: return Month_days(april);
        case 5: return Month_days(may);
        case 6: return Month_days(june);
        case 7: return Month_days(july);
        case 8: return Month_days(august);
        case 9: return Month_days(september);
        case 10: return Month_days(october);
        case 11: return Month_days(november);
        case 12: return Month_days(december);
        default: cerr << "not a month" << endl; return -1;
    }
};

int lab2::Julian::month_jump() const{
    return 30;
};

int lab2::Julian::mod_julian_day() const{ // valid for _year >= 0
//http://scienceworld.wolfram.com/astronomy/JulianDate.html
    float jd = 367.0f*(float)_year - floor( 7.0f*( (float)_year + floor((float)(_month+9)/12.0f)) / 4.0f ) + floor(275.0f/9.0f*(float)_month) + _day + 1721026.5;

    return (int)floor(jd - 2400000.5f);
};

int lab2::Julian::mod_julian_day_for_greg() const{ //same algorithm as mod_julian_day in class Gregorian

    int a;
    int y;
    int m;
    int jdn; // julian day number
    a = (14-_month) / 12;
    y = _year + 4800 - a;
    m = _month + 12*a - 3;
    jdn = _day + (153*m + 2) / 5 + 365*y + y/4 - y/100 + y/400 - 32045;
    float mjd = jdn - 2400000.5;

    return (floor(mjd));
};

bool lab2::Julian::leap_year() const{
    return(_year%4 == 0);
};
