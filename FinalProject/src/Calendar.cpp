#include "Calendar.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

Calendar::Calendar()
{
    cout << "Calendar created!" << endl;
    showTodaysEvents();
    // The constructor will need to be what reads in the text file, should we choose to create one
}

int* convertTime(string timeString){
    int * time = new int[2];
    string token = timeString.substr(0,timeString.find(':'));
    time[0] = stod(token);
    token = timeString.substr(timeString.find(':')+1,5);
    time[1] = stod(token);
    return time;

}

void Calendar::addEvent(std::string title, std::string description, string timeStart, string timeEnd){
    cout << endl << "Your event:" << endl << title << endl << description << endl << timeStart << endl << timeEnd << endl << endl;
    int * startTime=convertTime(timeStart);
    cout<<startTime[0]<<" "<<startTime[1]<<endl;;
    int * endTime=convertTime(timeEnd);
    cout<<endTime[0]<<" "<<endTime[1]<<endl;


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
