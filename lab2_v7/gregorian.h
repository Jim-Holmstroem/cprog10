#ifndef GREGORIAN_H
#define GREGORIAN_H

#include<iostream>
#include<ctime>
#include<math.h>
#include "date.h"
#include "kattistime.h"

namespace lab2{
    class Gregorian;
    
    class Gregorian : public Date {

        void setCurrentDate();

    public:
        Gregorian(); //Gives todays date
        Gregorian(int year,int month,int day); //Gives the date year-month-day
        Gregorian(const Date&);
        Gregorian(const Date*);
        ~Gregorian();
        Gregorian& operator=(const Date&);

        const int days_per_week() const;
        const int months_per_year() const;
        int days_this_month() const;
        int week_day() const;
        string week_day_name() const;
        string month_name() const;
        int mod_julian_day() const;

    protected:
        int month_jump() const;

    private:
        bool leap_year() const;

    };
}
#endif
