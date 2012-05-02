#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<math.h>
#include<iomanip>
#include<stdexcept>
using namespace std;

namespace lab2{
    class Date;
    std::ostream& operator<<(ostream&, const Date&);
    class Date{
      private:
        bool day2big();
        bool day2small();
        bool month2big();
        bool month2small();
      protected:
        int _year;
        int _month;
        int _day;
        virtual int month_jump() const = 0; //the number of days to jump if the jump to date fails to exist
      public:
        Date();
        Date(int,int,int);
        Date(const Date&);
        //Date(const Date*);
        ~Date();

        Date& operator=(const Date&);
        //Mutators
        Date& operator++(); //prefix
        Date& operator--();
        Date& operator+=(const int);
        Date& operator-=(const int);

        void add_year(const int); //lämplig returtyp? motivera
        void add_year();
        void add_month(const int);
        void add_month();
        void sub_month();

        //Comparisons
        int operator-(const Date&) const; //used for all compare operators

        bool operator==(const Date&) const;
        bool operator!=(const Date&) const;
        bool operator<(const Date&) const;
        bool operator<=(const Date&) const;
        bool operator>(const Date&) const;
        bool operator>=(const Date&) const;

        //Access functions
        int inline year() const {return _year;};
        int inline month() const {return _month;};
        int inline day() const {return _day;};
        virtual void setCurrentDate() = 0;
        virtual int week_day() const = 0;
        virtual const int days_per_week() const = 0; //
        virtual int days_this_month() const = 0; //not const since its calcultad not a var
        virtual const int months_per_year() const = 0; //
        virtual string week_day_name() const = 0;
        virtual string month_name() const = 0;
        virtual int mod_julian_day() const = 0;

        //friend ostream& lab2::operator<<(ostream&, const Date&);

        virtual bool isDateOutOfRange();

        int numOfDigits(const int) const;
    };
}
#endif
