#ifndef CALENDAR_H
#define CALENDAR_H
#include <iostream>
#include <vector>

struct Event{
    std::string name;
    std::string description;
    int timeStart[3];
    int timeEnd[3];
    int urgency;
};

// This is the header file. More detailed descriptions of the functions are in the .cpp file
class Calendar
{
    public:
        Calendar();
        virtual ~Calendar();
        void addEvent(std::string title, std::string description, std::string timeStart, std::string timeEnd);
        // void addEvent(std::string title, int timeStart, int timeEnd); I don't know that this function overload was a good idea after all
        void showTodaysEvents();
        void showOtherDayEvents(std::string date);
        void printWeek();
        void printSlots(std::string date, std::string hourStart, std::string hourEnd);
        void deleteEvent(std::string title);
        void eventDetails(std::string title);
        void clearDay(std::string date);
    protected:
    private:
        Event *findEvent(std::string title);
        std::vector<Event> days;
};

#endif // CALENDAR_H
