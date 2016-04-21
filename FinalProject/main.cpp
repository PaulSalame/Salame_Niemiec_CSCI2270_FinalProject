#include <iostream>
#include "Calendar.h"
// This is a test comment to make sure I know what I'm doing
using namespace std;

int main()
{
    cout << "Welcome to Matt and Paul's Calendar!" << endl << endl;
    string response;

    Calendar schedule;

    string title;
    string description;
    string timeStart;
    string timeEnd;
    string date;

    while(true){
        cout << "======MAIN MENU======"<<endl;
        cout << "What would you like to do?" << endl;
        cout << "Press 'a' to add an event" << endl;
        cout << "Press 't' to show a day's events" << endl;
        cout << "Press 'w' to show the week's events" << endl;
        cout << "Press 's' to show the slots for a specific time period" << endl;
        cout << "Press 'd' to delete a specific event" << endl;
        cout << "Press 'l' to look for an event" << endl;
        cout << "Press 'c' to clear all events for a day" << endl;
        cout << "Press 'q' to exit the program" << endl;
        getline(cin, response);
        if(response == "a"){
            cout<< "What day is your event on (ex. Monday)"<<endl;
            getline(cin,date);
            cout << "What is the title of your event?" << endl;
            getline(cin, title);
            cout << "Give a brief description of the event: " << endl;
            getline(cin, description);
            cout << "Enter starting hour (ex. 14:30): " << endl;
            getline(cin, timeStart);
            cout << "Enter finishing hour (ex. 9:15)" << endl;
            getline(cin, timeEnd);

            schedule.addEvent(date,title, description, timeStart, timeEnd);
        }
        else if(response == "t"){
            cout<<"Enter a day (eg. Monday)"<<endl;
            getline(cin,date);
            schedule.showTodaysEvents(date);
        }
        else if(response == "w"){
            schedule.printWeek();
        }
        else if(response == "s"){
            cout << "Enter the date you want to check: " << endl;
            getline(cin, date);
            cout << "Enter a starting time you want to check:" << endl;
            getline(cin, timeStart);
            cout << "Enter a finishing time:" << endl;
            getline(cin, timeEnd);

            schedule.printSlots(date, timeStart, timeEnd);
        }
        else if(response == "d"){
            cout << "Enter the title of the event you would like to delete:" << endl;
            getline(cin, date);

            schedule.deleteEvent(date);
        }
        else if(response == "l"){
            cout << "Enter the title of the event:" << endl;
            getline(cin, date);

            schedule.eventDetails(date);
        }
        else if(response == "c"){
            cout << "Enter the day you'd like to clear:" << endl;
            getline(cin, date);

            schedule.clearDay(date);
        }
        else if(response == "q"){
            cout << "'Bout time. Have a nice day. Or something." << endl;
            break;
        }
        else{
            cout << "You're dead to me" << endl;
        }
    }

    return 0;
}
