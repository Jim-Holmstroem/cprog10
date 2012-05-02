#include "date.h"

using namespace std;

lab2::Date::Date(){
    #ifdef DEBUG
    cout << "in Date(): ";
    #endif
};

lab2::Date::Date(int year,int month,int day){ // den här körs inte när man skapar en Gregorian utan det är först default Date constructor och sen Gregorian(int,int,int)
    #ifdef DEBUG
    cout << "in Date(int,int,int): ";
    #endif
    _year = year;
    _month = month;
    _day = day;

    /*

    @NOTE must have a boundary check but it calls days_this_month,months_per_year (further down the trace) that are virtual functions and cant be called from the constructor, so it must be added in all the derived (int,int,int)-constructors

    */
};

lab2::Date::Date(const Date& d) {
    #ifdef DEBUG
    cout << "in Date(const Date&): ";
    #endif
    _year = d.year();
    _month = d.month();
    _day = d.day();
};

lab2::Date::~Date(){};

bool lab2::Date::isDateOutOfRange(){
    return (_year<1||_year>3000||month2small()||day2small()||month2big()||day2big()||mod_julian_day()<(-678575) ); //week_day will return incorrect(maybe negative) values for days smaller than Gregorian(0001,01,01) resp. Julian(0001,01,03)
};

lab2::Date& lab2::Date::operator=(const Date& d){
    #ifdef DEBUG
    cout<<"in Date::operator="<<endl;
    #endif
    if(this != &d){ //to avoid self assignment
        _year = d.year();
        _month = d.month();
        _day = d.day();
        *this += (d.mod_julian_day() - this->mod_julian_day() ); //convert date in case if different derived classes
    }
    
    return *this;
};


/*
*	Adds one day to this date
*
*	@NOTE uses operator+=(n=1)
*/

lab2::Date& lab2::Date::operator++(){ //prefix
    #ifdef DEBUG
    //cout<<"operator++(): ";
    #endif
    *this+=1;
    return *this;
};
lab2::Date& lab2::Date::operator--(){
	*this+=(-1);
	return *this;
};

lab2::Date& lab2::Date::operator-=(const int n){
	*this+=(-n);
	return *this;
};

/*
*	Adds n days to this date and wraps both month and years if necessary
*
*
*	@NOTE dependent on that add_month() will update the return value of days_this_month (TODO check it)
    @NOTE all date manipulating functions should check for "out of range" when wrapping around some value
*/

lab2::Date& lab2::Date::operator+=(const int n){
	_day += n;

	while(day2big()){   //while the _day > the number of days "this" month
						//(@NOTE if n requares to update multiple month it
						//will use the different "days_this_month"
						//ex. jan then add_month and the uses feb's days_this_month()  ..)
		_day -= days_this_month();
		_month++;		//must use add_month since it could be necessary to wrap a year
						//go to the next month and start over with the same thing
		if(month2big()){
		    _year++;
		    _month = 1;
		}
	}

	while(day2small()){ //if the days of the week wraps back (day 0 is outside as well as <0)
		_month--; //the inverse of the above @NOTE (since (d+=n)-=n == d)

		if(month2small()){
		    _year--;
		    _month = months_per_year();
		}
		_day += days_this_month();
	}

	return *this;
};

void lab2::Date::add_year(const int n){
	_year+=n;
    if(day2big()){ //days_this_month() will check if it is leap year
        _day = days_this_month();
    }
};

void lab2::Date::add_year(){
    lab2::Date::add_year(1);
}

/*
*	Adds one month to current date and adds a year if necessary fixes leap year
*
*	@NOTE adds a month and if the same date in the next month doesn't exist then subtract a month and add 30 days instead
*/

void lab2::Date::add_month(){
    _month++;
    if(month2big()){
        _year++;  // do not call add_year() instead of _year++ since if the first and last month has different number of days then e.g. 31/12 => 28/1 instead of 31/12 => 30/1 (+=month_jump)
        _month = 1;
    }
    #ifdef ADDMONTH
    cout << " in add_month(): _month++;=" << _month << endl;
    #endif

    if(day2big()){
        #ifdef ADDMONTH
        cout << "day2big()" << endl;
        #endif

        _month--;
        if(month2small()){
            _year--;
            _month = months_per_year();
        }

        #ifdef ADDMONTH
        cout << "_month--;=" << _month;
        cout << " /w month_jump" << month_jump() << endl;
        #endif

        *this += month_jump();
    }
    #ifdef ADDMONTH
    cout << *this << endl;
    #endif
};

void lab2::Date::sub_month(){
    _month--;
    if(month2small()){
        _year--;
        _month = months_per_year();
    }

    #ifdef ADDMONTH
    cout << " in sub_month(): _month--;=" << _month << endl;
    #endif

    if(day2big()){
        #ifdef ADDMONTH
        cout << "day2big()" << endl;
        #endif

        _month++;
        if(month2big()){
        _year++;
        _month = 1;
        }

       #ifdef ADDMONTH
        cout << "_month++;=" << _month;
        cout << " /w month_jump -" << month_jump() << endl;
        #endif

        *this -= month_jump();
    }
    #ifdef ADDMONTH
    cout << *this << endl;
    #endif
};

/*
*	Adds n months to the current date, and adds years if its necessary
*
*
*/

void lab2::Date::add_month(const int n){
    #ifdef ADDMONTH
    cout << "Date::add_month(const int n): n=" << n << "..."<< endl; cout.flush();
    #endif
    if(n>0){
        for(int i = 0;i<n;i++){
            #ifdef ADDMONTH
            cout << "i=" << i; cout.flush();
            #endif
            add_month();
        }
    }
    else if(n<0){
        int negn = -n;
        for(int i = 0;i < negn;i++){
            #ifdef ADDMONTH
            cout << "i=" << i; cout.flush();
            #endif
            sub_month();
        }
    }
    //if(n==0) does nothing

};


bool inline lab2::Date::day2big(){
    return (_day > days_this_month());
}
bool inline lab2::Date::day2small(){
    return (_day <= 0);
}
bool inline lab2::Date::month2big(){
    return (_month > months_per_year());
}
bool inline lab2::Date::month2small(){
    return (_month <= 0);
}


/*void Date::add_month(const int n){
	_month+=n;

	//@NOTE this only works because the number of months in one year is constant,
	//compare with += where the wrap-n is dynamic

	if(month2big()){ //if the month is bigger then it should be
		_year += (_month / months_per_year()); //add the number of years that its bigger then
		_month %= months_per_year(); // then wrap the month to fit into ordinary domain

	}
	if(month2small()){//if the months of the years wraps back (month 0 is outside as well as <0)
		int years_decreased = 1 - _month / months_per_year();
		_year -= years_decreased;		//0,-1,-2,..,-11 -> _year-=1
									//    -12,..,-23 -> _year-=2
							//@NOTE DONT use / or % with negative numbers
							//because of undefined behavior (free to truncate up or down)
		_month = _month + years_decreased * months_per_year();
	}

	//TODO leap boundary check shit

};*/

/*
*	Compares the dates and returns the difference
*
*	@NOTE uses mod_julian_day() function as reference to compare the dates
*
*/

int lab2::Date::operator-(const Date& d) const{
    #ifdef DEBUG
    cout<<"in operator-: ";
    #endif
    return (this->mod_julian_day() - d.mod_julian_day());
};

/*
*	Checks if d is equal to this
*
*	@NOTE uses operator- to get the result
*
*/

bool lab2::Date::operator==(const Date& d) const{
    #ifdef DEBUG
    cout<<"operator==: ";
    #endif
    return (*this-d==0);
};

bool lab2::Date::operator!=(const Date& d) const{
	return (*this-d!=0);
};
bool lab2::Date::operator<(const Date& d) const{
	return (*this-d<0);
};
bool lab2::Date::operator<=(const Date& d) const{
	return (*this-d<=0);
};
bool lab2::Date::operator>(const Date& d) const{
	return (*this-d>0);
};
bool lab2::Date::operator>=(const Date& d) const{
	return (*this-d>=0);
};

int lab2::Date::numOfDigits(const int n) const{
    return (1+(int)log10((float)n));
};

/*
*	Prints the date in the right format
*
*	@NOTE Friend of Date so it can access protected variables
*
*/


ostream& lab2::operator<<(ostream& os, const lab2::Date& d){
    os << setfill('0') << setw(4) << d.year() <<  "-" << setw (d.numOfDigits(d.months_per_year())) << d.month() <<"-" << setw (d.numOfDigits(d.months_per_year())) << d.day();
    return os;
};


