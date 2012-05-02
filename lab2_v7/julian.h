#ifndef JULIAN_H
#define JULIAN_H

#include<iostream>
#include<ctime>
#include<math.h>
#include "date.h"
#include "kattistime.h"

namespace lab2{
    class Julian;
    
    class Julian : public Date {

        void setCurrentDate();

    public:
        Julian(); //Gives todays date
        Julian(int year,int month,int day); //Gives the date year-month-day
        Julian(const Date&);
        Julian(const Date*);
        ~Julian();
        Julian& operator=(const Date&);

        const int days_per_week() const;
        const int months_per_year() const;
        int days_this_month() const;
        int week_day() const;
        string week_day_name() const;
        string month_name() const;
        int mod_julian_day() const;
        int mod_julian_day_for_greg() const;

    protected:
        int month_jump() const;

    private:
        bool leap_year() const;

    };
}
#endif
