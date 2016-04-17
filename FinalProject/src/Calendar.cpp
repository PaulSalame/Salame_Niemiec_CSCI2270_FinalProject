#include "Calendar.h"
#include <iostream>

using namespace std;

Calendar::Calendar()
{
    cout << "Calendar created!" << endl;
    showTodaysEvents();
    // The constructor will need to be what reads in the text file, should we choose to create one
}

void Calendar::addEvent(std::string title, std::string description, string timeStart, string timeEnd){
    cout << endl << "Your event:" << endl << title << endl << description << endl << timeStart << endl << timeEnd << endl << endl;
}

void Calendar::showTodaysEvents(){
    cout << "Today's events showed!" << endl;
}

void Calendar::showOtherDayEvents(string date){
    cout << "Here's what's up on " << date << ":" << endl;
}

void Calendar::printWeek(){
    cout << "Here's watchur doin' this week: " << endl;
}

void Calendar::printSlots(string date, string hourStart, string hourEnd){
    cout << "Here's when you have time on " << date << " between " << hourStart << " and " << hourEnd << endl;
}

void Calendar::deleteEvent(string title){
    cout << title << ". Deleted." << endl;
}

void Calendar::eventDetails(string title){
    cout << "Event title: " << title << endl;
    cout << "Description: Something cool" << endl;
    cout << "Start time: Some time" << endl;
    cout << "End time: Some time later than the start time" << endl;
}

void Calendar::clearDay(string date){
    cout << date << ". Has. Been Cleared." << endl;
}

Event *Calendar::findEvent(string title){
    cout << title << ". Found." << endl;
}

Calendar::~Calendar()
{
    cout << "Calendar burned!" << endl;
    // The constructor will be what writes the information to the text file, if we do make it that far.
}
