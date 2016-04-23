#include "Calendar.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;

Calendar::Calendar()
{

    //cout << "Calendar created!" << endl;
    //showTodaysEvents();
    for (int i = 0; i<7;i++){ //Initialize the pointers to NULL
        days.push_back(NULL);
    }
    // The constructor will need to be what reads in the text file, should we choose to create one
}

int* convertTime(string timeString){ //Function to convert string time to integer array
    int * time = new int[2];
    string token = timeString.substr(0,timeString.find(':'));
    time[0] = stod(token);
    token = timeString.substr(timeString.find(':')+1,5);
    time[1] = stod(token);
    return time;
}

int convertDate(string date){ //Lets have the days vector start with Sunday as index[0]
        if (date == "Sunday"){
            return 0;
        }
        else if (date == "Monday"){
            return 1;
        }
        else if (date == "Tuesday"){
            return 2;
        }
        else if (date == "Wednesday"){
            return 3;
        }
        else if (date == "Thursday"){
            return 4;
        }
        else if (date == "Friday"){
            return 5;
        }
        else if (date == "Saturday"){
            return 6;
        }



}

void Calendar::getTodaysDate(){
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    tm timeStruct = {};
    timeStruct.tm_year = now->tm_year;
    timeStruct.tm_mon = now->tm_mon;
    timeStruct.tm_mday = now->tm_mday;
    timeStruct.tm_hour = 12;    //  To avoid any doubts about summer time, etc.
    mktime( &timeStruct );
    string day;
    if(timeStruct.tm_wday == 0){
        day = "Sunday";
    }else if(timeStruct.tm_wday == 1){
        day = "Monday";
    }else if(timeStruct.tm_wday == 2){
        day = "Tuesday";
    }else if(timeStruct.tm_wday == 3){
        day = "Wednesday";
    }else if(timeStruct.tm_wday == 4){
        day = "Thursday";
    }else if(timeStruct.tm_wday == 5){
        day = "Friday";
    }else if(timeStruct.tm_wday == 6){
        day = "Saturday";
    }

    cout << "Today's date is " << day << " on "
         << (now->tm_mon + 1) << '/'
         << now->tm_mday << '/'
         <<  (now->tm_year + 1900)
         << endl;
}

void Calendar::addEvent(std::string date, std::string title, std::string description, string timeStart, string timeEnd){
    cout << endl << "Your event:" << endl << title << endl << description << endl << timeStart << endl << timeEnd << endl;
    int * startTime=convertTime(timeStart);
    int * endTime=convertTime(timeEnd);
    int day = convertDate(date);
    Event * newEvent = new Event(title,description,startTime,endTime); //new event
    newEvent->date=date;

    if (days[day]==NULL){ //if the list is empty
        days[day]=newEvent;
    }
    else{
        //if the list already has a head
    }

}

void Calendar::showTodaysEvents(string date){ //Show the events for a day that the user inputs
    cout << date<<" events showed!" << endl;
    int day = convertDate(date);
    Event *temp = days[day];
    if (temp==NULL){
        cout<<"No events on "<<date<<endl;
    }
    while (temp!=NULL){
        cout<<"Event: "<<temp->name<<"  "<<"Start Time: "<<temp->timeStart[0]<<":"<<temp->timeStart[1]<<"  ";
        cout<<"End Time: "<<temp->timeEnd[0]<<":"<<temp->timeEnd[1]<<endl;
        temp=temp->next;
    }
}

void Calendar::showOtherDayEvents(string date){
    cout << "Here's what's up on " << date << ":" << endl;

}

void Calendar::printWeek(){
    cout << "Here's watchur doin' this week: " << endl;
    Event *temp;
    for (int i = 0; i<days.size();i++){

        temp = days[i];
        if (temp!=NULL){
            cout<<"==="<<temp->date<<"==="<<endl; //print the day
        }
        while (temp!=NULL){
            cout<<"Event: "<<temp->name<<"  "<<"Start Time: "<<temp->timeStart[0]<<":"<<temp->timeStart[1]<<"  ";
        cout<<"End Time: "<<temp->timeEnd[0]<<":"<<temp->timeEnd[1]<<endl;
            temp=temp->next;
        }

    }


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
    //cout << "Calendar burned!" << endl;
    // The constructor will be what writes the information to the text file, if we do make it that far.
}
