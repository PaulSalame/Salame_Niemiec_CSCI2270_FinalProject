#ifndef CALENDAR_H
#define CALENDAR_H
#include <iostream>
#include <vector>
#include <string>
struct Event{
    std::string name;
    std::string description;
    int timeStart[2];
    int timeEnd[2];
    int urgency;
    std::string date;
    Event * next;
    Event * prev;
    Event(){};
    Event(std::string n, std::string des, int start[2],int end[2]) //constructor
    {
        name = n;
        description = des;
        timeStart[0] = start[0];
        timeStart[1] = start[1];
        timeEnd[0]=end[0];
        timeEnd[1]=end[1];
        next=NULL;
        prev=NULL;
    }
};

// This is the header file. More detailed descriptions of the functions are in the .cpp file
class Calendar
{
    public:
        Calendar();
        virtual ~Calendar();
        void addEvent(std::string date, std::string title, std::string description, std::string timeStart, std::string timeEnd);
        // void addEvent(std::string title, int timeStart, int timeEnd); I don't know that this function overload was a good idea after all
        void showTodaysEvents(std::string date);
        void showOtherDayEvents(std::string date);
        void printWeek();
        void printSlots(std::string date, std::string hourStart, std::string hourEnd);
        void deleteEvent(std::string title);
        void eventDetails(std::string title);
        void clearDay(std::string date);
        void getTodaysDate();
    protected:
    private:
        Event *findEvent(std::string title);
        std::vector<Event*> days;
};

#endif // CALENDAR_H
