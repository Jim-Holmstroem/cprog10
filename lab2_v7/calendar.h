#ifndef CALENDAR_H
#define CALENDAR_H

#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

namespace lab2{

    template<typename T>
        struct Event{
            T date;
            string text;

            Event<T>(){};
            Event<T>(string txt,T d): text(txt),date(d){};
            Event<T>(string txt,int d,int m,int y): date(y,m,d),text(txt){};
            Event<T>(const Event<T>& evt){
                date = evt.date; //should convert the date if different class
                text = evt.text;
            };
            ~Event<T>(){};

            Event<T>& operator=(const Event<T>& evt){
                date = evt.date;
                text = evt.text;
                return *this;
            };
            bool operator==(const Event<T>& e) const{
                return(date == e.date && text == e.text);
            };
            friend ostream& operator<<(ostream& out, const Event<T>& e){
                out << e.date << " : " << e.text;
                return out;
            };
        };

    template<typename T>
        class Calendar;

    template<typename T>
        ostream& operator<<(ostream& out, const Calendar<T>& cal);

    template<typename T>
        class Calendar{
      private:
      protected:
      public:
        vector< Event<T> > event_list;
        Calendar<T>();
        ~Calendar<T>();

        template<typename T2>
            Calendar<T>(const Calendar<T2>&);
        template<typename T2>
            Calendar<T>& operator=(const Calendar<T2>&);

        T cur_date;

        bool set_date(int,int,int);

        bool add_event(string);
        bool add_event(string,int);
        bool add_event(string,int,int);
        bool add_event(string,int,int,int);

        bool remove_event(string);
        bool remove_event(string,int);
        bool remove_event(string,int,int);
        bool remove_event(string,int,int,int);

        //friend std::ostream& operator<<(std::ostream& out, const Calendar<T>& cal);
    };

    template<typename T>
        Calendar<T>::Calendar(){
#ifdef DEBUG
        cout << "in Calendar()" ; cout.flush();
#endif
        T d;
        cur_date = d;
    }

    template<typename T>
        Calendar<T>::~Calendar(){};

    template<typename T>
        template<typename T2>
        Calendar<T>::Calendar(const Calendar<T2>& cal){
        cur_date = cal.cur_date;
        typename vector< lab2::Event<T2> >::const_iterator it = cal.event_list.begin();
        while(it != cal.event_list.end()){
            Event<T> evt;
            evt.date = it->date; //to avoid the use of multiple templates in Event<T>
            evt.text = it->text;
#ifdef DEBUG
            cout << "converted event" << evt << endl;
#endif
            event_list.push_back(evt); //the event list we copy from is already sorted
            ++it;
        }
    }

    template<typename T>
        template<typename T2>
        Calendar<T>& lab2::Calendar<T>::operator=(const lab2::Calendar<T2>& cal){
        cur_date = cal.cur_date;
        typename vector< lab2::Event<T2> >::const_iterator it = cal.event_list.begin();
        while(it != cal.event_list.end()){
            lab2::Event<T> evt;
            evt.date = it->date; //to avoid the use of multiple templates in Event<T>
            evt.text = it->text;
#ifdef DEBUG
            cout << "converted event" << evt << endl;
#endif
            event_list.push_back(evt); //the event list we copy from is already sorted
            ++it;
        }
        return *this;
    }

    template<typename T>
        bool Calendar<T>::set_date(int year,int month,int day){
        try{
            cur_date = T(year,month,day);
        }catch(exception e){
#ifdef DEBUG
            cout<<"in set_date: out of range"<<endl;
#endif
            return false;
        }
        return true;
    }

    template<typename T>
        bool inline Calendar<T>::add_event(string text){
        return add_event(text, cur_date.day(), cur_date.month(), cur_date.year());
    }
    template<typename T>
        bool inline Calendar<T>::add_event(string text, int day){
        return add_event(text,    day, cur_date.month(), cur_date.year());
    }
    template<typename T>
        bool inline Calendar<T>::add_event(string text, int day, int month){
        return add_event(text,    day,    month, cur_date.year());
    }
    template<typename T>
        bool inline Calendar<T>::add_event(string text, int day, int month, int year){
        try{
            Event<T> e(text,day,month,year);
            typename vector< Event<T> >::iterator it = event_list.begin();
            while(it!=event_list.end() && it->date <= e.date){ //fastforward into the date that are bigger
                if(*it==e){//if the event already exists then do not add
#ifdef DEBUG
                    cout << "e==*it for :" << e << " == " << *it << endl;
#endif
                    return false;
                }
                ++it;
            }
            if(it!=event_list.end()){
                event_list.insert(it,e);
            }else{
                event_list.push_back(e);
            }
            return true;
        }
        catch(exception exc){
#ifdef DEBUG
            cout<<"in add_event: out of range"<< endl;
#endif
            return false;
        }
    }

    template<typename T>
        bool inline Calendar<T>::remove_event(string text){
        return remove_event(text, cur_date.day(), cur_date.month(), cur_date.year());
    }
    template<typename T>
        bool inline Calendar<T>::remove_event(string text, int day){
        return remove_event(text,    day, cur_date.month(), cur_date.year());
    }
    template<typename T>
        bool inline Calendar<T>::remove_event(string text, int day, int month){
        return remove_event(text,    day,    month, cur_date.year());
    }
    template<typename T>
        bool inline Calendar<T>::remove_event(string text, int day, int month, int year){
        try{
            Event<T> e(text,day,month,year);
            typename vector< Event<T> >::iterator it = event_list.begin();
            while(it!=event_list.end()){
                if(e == *it){
                    event_list.erase(it);
                    return true; //since there is only one unique event
                }
                ++it;
            }
            return false;
        }
        catch(exception exc){
#ifdef DEBUG
            cout<<"in remove_event: out of range"<< endl;
#endif
            return false;
        }
    }

    template<typename T>
        ostream& operator<<(ostream& out, const Calendar<T>& cal) {
        typename std::vector< Event<T> >::const_iterator it = cal.event_list.begin();
        while(it != cal.event_list.end()){
            if(it->date > cal.cur_date){
                out << *it << endl;
            }
            ++it;
        }
        return out;
    }
}

#endif
