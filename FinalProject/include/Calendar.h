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
        void addEvent(std::string date, std::string title, std::string description, std::string timeStart, std::string timeEnd); //Finished!
        // void addEvent(std::string title, int timeStart, int timeEnd); I don't know that this function overload was a good idea after all
        void showTodaysEvents(std::string date);//Finished!
        void showOtherDayEvents(std::string date);
        void printWeek();//Finished!
        void printSlots(std::string date, std::string hourStart, std::string hourEnd);
        void deleteEvent(std::string title);//Finished!
        void eventDetails(std::string title);
        void clearDay(std::string date);
        void getTodaysDate();//Finished!
    protected:
    private:
        int convertDate(std::string date);
        int* convertTime(std::string timeString);
        double timeDouble(int time[]);
        Event *findEvent(std::string title);//Finished!
        std::vector<Event*> days;
};

#endif // CALENDAR_H
