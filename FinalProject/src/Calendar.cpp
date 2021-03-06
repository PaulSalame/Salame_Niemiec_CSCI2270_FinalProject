#include "Calendar.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>


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

int* Calendar::convertTime(string timeString){ //Function to convert string time to integer array
    int * time = new int[2];
    string token = timeString.substr(0,timeString.find(':'));
    time[0] = atoi( token.c_str() );
    token = timeString.substr(timeString.find(':')+1,5);
    time[1] = atoi( token.c_str() );
    return time;
}

//ADDED
string Calendar::convertDateBack(int day){ //Added to convert back to string format for deleteALL and searching purposes
    if(day==0){
        return "Sunday";
    }
    else if (day == 1){
        return "Monday";
    }
    else if (day == 2){
        return "Tuesday";
    }
    else if (day == 3){
        return "Wednesday";
    }
    else if (day ==4){
        return "Thursday";
    }
    else if (day == 5){
        return "Friday";
    }
    else if(day ==6){
        return "Saturday";
    }
}
int Calendar::convertDate(string date){ //Lets have the days vector start with Sunday as index[0]
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

double Calendar::timeDouble(int time[]){ //Function to convert the array time into a double (easier to use for calculating conflicts in schedule)
    double a = double(time[0]) + double(time[1])/60;
    return a;

}

void Calendar::addEvent(std::string date, std::string title, std::string description, string timeStart, string timeEnd){
    cout << endl << "Your event:" << endl << title << endl << description << endl << timeStart << endl << timeEnd << endl;
    int * startTime=convertTime(timeStart);
    int * endTime=convertTime(timeEnd);
    int day = convertDate(date);
    bool conflict = false;
    Event * newEvent = new Event(title,description,startTime,endTime); //new event
    newEvent->date=date;

    if (days[day]==NULL){ //if the list is empty
        days[day]=newEvent;
    }
    else{
        //if the list already has a head

        //first check for conflicting events
        Event *temp = days[day];
        while (temp!=NULL){ //loop through each event in the day
            //CASE 1: IF NEW EVENT START TIME IS DURING AN EXISTING EVENT
            if (timeDouble(newEvent->timeStart) > timeDouble(temp->timeStart) && timeDouble(newEvent->timeStart) < timeDouble(temp->timeEnd)){
                conflict = true;
                cout<<"Event: "<<temp->name<<" overlaps with this time interval"<<endl;
            }
            //CASE 2: IF NEW EVENT END TIME IS DURING AN EXISTING EVENT
            else if (timeDouble(newEvent->timeEnd) < timeDouble(temp->timeEnd) && timeDouble(newEvent->timeEnd) > timeDouble(temp->timeStart)){
                 conflict = true;
                cout<<"Event: "<<temp->name<<" overlaps with this time interval"<<endl;
            }
            //CASE 3: EXISTING EVENT STARTS DURING THE NEW EVENT
            /*else if (timeDouble(temp->timeStart) >= timeDouble(newEvent->timeStart) && timeDouble(temp->timeStart) <= timeDouble(newEvent->timeEnd)){
                 conflict = true;
                cout<<"Event: "<<temp->name<<" overlaps with this time interval"<<endl;
            }*/ // This isn't necessary - if existing event starts during new event, then new event end time will be during existing event

            temp=temp->next;
        }
        if (conflict == false){
            //IF NO CONFLICT IS FOUND, WE ADD EVENT IN ITS CORRECT ORDER IN THE LIST
            Event * right;;
            temp=days[day];

            if (temp->next==NULL){ //if the only existing node is the head of the list (is in the array)
                if (timeDouble(newEvent->timeStart) > timeDouble(temp->timeEnd)){//if the new event starts after the existing one
                    temp->next=newEvent;
                    newEvent->prev=temp;
                }
                else{ //if the new event starts before the existing one
                    // cout<<"TRUUU"<<endl;
                    temp->prev=newEvent;
                    newEvent->next=temp;
                    days[day]=newEvent; //new Event is now the head of the linked list
                }
            }

            else{ //IF THERE ARE MORE ELEMENTS THAN JUST THE HEAD
                    right=days[day];
                    while (timeDouble(right->timeStart)<timeDouble(newEvent->timeEnd)){ //get a pointer to the first event that starts after our new event ends
                    right=right->next;
                        if (right==NULL){
                            break;
                        }
                    }

                if (right==NULL){//IF THERE IS NO NODE THAT STARTS AFTER OUR NEW NODE... ADD NEW NODE TO END OF LINKED LIST
                        temp=days[day];
                        while (temp->next!=NULL){
                            temp=temp->next; //get a pointer to end of list
                        }
                        temp->next=newEvent;
                        newEvent->prev=temp;

                }
                else if (right==days[day]){//if our new event is before the head of list
                    right->prev=newEvent;
                    newEvent->next=right;
                    days[day]=newEvent; //new Event is now the head of the linked list
                }
                else{ //if we are inserting before an element that is not the head
                    right->prev->next=newEvent;
                    right->prev=newEvent;
                    newEvent->next=right;
                    newEvent->prev=right->prev;
                }
        }
        }
    }

}

void Calendar::showTodaysEvents(string date){ //Show the events for a day that the user inputs
    string zeroHour;
    string zeroMinute;
    cout << date<<" events showed!" << endl;
    int day = convertDate(date);
    Event *temp = days[day];
    if (temp==NULL){
        cout<<"No events on "<<date<<endl;
    }
    while (temp!=NULL){
        zeroHour = "";
        zeroMinute = "";
        if(temp->timeStart[0] == 0){
            zeroHour = "0";
        }
        if(temp->timeStart[1] < 10){
            zeroMinute = "0";
        }
        cout<<"Event: "<<temp->name<<"  "<<"Start Time: "<<zeroHour<<temp->timeStart[0]<<":"<<zeroMinute<<temp->timeStart[1]<<"  ";
        zeroHour = "";
        zeroMinute = "";
        if(temp->timeEnd[0] == 0){
            zeroHour = "0";
        }
        if(temp->timeEnd[1] < 10){
            zeroMinute = "0";
        }
        cout<<"End Time: "<<zeroHour<<temp->timeEnd[0]<<":"<<zeroMinute<<temp->timeEnd[1]<<endl;
        temp=temp->next;
    }
}

void Calendar::showOtherDayEvents(string date){
    cout << "Here's what's up on " << date << ":" << endl;

}

void Calendar::printWeek(){
    string zeroHour;
    string zeroMinute;
    cout << "Here's watchur doin' this week: " << endl;
    Event *temp;
    for (int i = 0; i<days.size();i++){
        temp = days[i];
        if (temp!=NULL){
            cout<<"==="<<temp->date<<"==="<<endl; //print the day
        }
        while (temp!=NULL){
            zeroHour = "";
            zeroMinute = "";
            if(temp->timeStart[0] == 0){
                zeroHour = "0";
            }
            if(temp->timeStart[1] < 10){
                zeroMinute = "0";
            }
            cout<<"Event: "<<temp->name<<"  "<<"Start Time: "<<zeroHour<<temp->timeStart[0]<<":"<<zeroMinute<<temp->timeStart[1]<<"  ";
            zeroHour = "";
            zeroMinute = "";
            if(temp->timeEnd[0] == 0){
                zeroHour = "0";
            }
            if(temp->timeEnd[1] < 10){
                zeroMinute = "0";
            }
            cout<<"End Time: "<<zeroHour<<temp->timeEnd[0]<<":"<<zeroMinute<<temp->timeEnd[1]<<endl;
            temp=temp->next;
        }

    }


}

void Calendar::printSlots(string date, string hourStart, string hourEnd){
    int *opening = convertTime(hourStart);
    int *closing = convertTime(hourEnd);
    bool isFree = false;

    int day = convertDate(date);
    Event *temp = days[day];
    cout << "On " << date << " you are free between " << endl;
    if (temp==NULL){ // If there are no events, then they are free the whole time
        cout << hourStart << " and " << hourEnd << endl;
        return;
    }
    do{
        if(((temp->timeStart[0] < opening[0]) || (temp->timeStart[0]==opening[0] && temp->timeStart[1] < opening[1])) && (((temp->timeEnd[0] > closing[0]) || (temp->timeEnd[0]==closing[0] && temp->timeEnd[1] > closing[1])))){
            cout << "Just kidding. You have no time open." << endl; // Sorry it's so long. Basically this is in the case the there is an event that starts before the period and ends after the period
        }
        else if((temp->timeStart[0] > opening[0]) || (temp->timeStart[0]==opening[0] && temp->timeStart[1] > opening[1])){ // The case where the start of the first event is after the start time given
            if((temp->timeStart[0] > closing[0]) || (temp->timeStart[0]==closing[0] && temp->timeStart[1] > closing[1])){ // Checking if the first event is after the time slot
                cout << hourStart << " and " << hourEnd << endl; // Then they will be free the whole time
                return;
            }
            else if((temp->timeEnd[0] > closing[0]) || (temp->timeEnd[0]==closing[0] && temp->timeEnd[1] > closing[1])){
                cout << hourStart << " and " << temp->timeStart[0] << ':' << temp->timeStart[1] << endl;
                return;
            }
            cout << hourStart << " and ";
            cout << temp->timeStart[0] << ':' << temp->timeStart[1] << endl;
            cout << temp->timeEnd[0] << ':' << temp->timeEnd[1] << " and ";
            isFree = true;
        }
        else if((temp->timeStart[0] < opening[0]) || (temp->timeStart[0]==opening[0] && temp->timeStart[1] < opening[1])){ // The case where the start is before the time slot
            if((temp->timeEnd[0] > opening[0]) || (temp->timeEnd[0]==opening[0] && temp->timeEnd[1] > opening[1])){ // If the end of the event falls after the beginning of the slot
                cout << temp->timeEnd[0] << ':' << temp->timeEnd[1] << " and ";
                isFree = false;
            }
            else{
                cout << hourStart << " and " << hourEnd << endl;
                return;
            }
        }
        temp = temp->next;

    }while(!isFree && temp != NULL);

    while (temp!=NULL){
        cout << temp->timeStart[0] << ':' << temp->timeStart[1] << endl;

        if((temp->timeEnd[0] > closing[0]) || (temp->timeEnd[0]==closing[0] && temp->timeEnd[1] > closing[1])){
            return;
        }
        cout << temp->timeEnd[0] << ':' << temp->timeEnd[1] << " and ";
        temp=temp->next;
    }
    cout << hourEnd << endl;
}

void Calendar::deleteEvent(string title){
    cout << title << ". Deleted." << endl;
    Event *node = findEvent(title);
    if (node->prev==NULL){ //if the node to be deleted is the head of list
            cout<<"true"<<endl;
        days[convertDate(node->date)]=node->next;
        if (node->next!=NULL){
        node->next->prev=NULL;
        }
        delete node;
    }
    else if (node->next==NULL){ //if we are deleting the end of the list
        node->prev->next=NULL;
        delete node;
    }
    else{ //if we are deleting a middle node
        node->prev->next=node->next;
        node->next->prev=node->prev;
        delete node;
    }
}

void Calendar::eventDetails(string title){
    Event *node=findEvent(title);
    cout << "Event title: " << node->name << endl;
    cout << "Description: "<<node->description << endl;
    cout << "Day: "<<node->date<<endl;
    cout << "Start time: "<<node->timeStart[0]<<":"<<node->timeStart[1]<<endl;
    cout << "End time: "<<node->timeEnd[0]<<":"<<node->timeEnd[1]<<endl;
}

void Calendar::clearDay(string date){


    if(isDateInCalender(date)!= false){ //ADDED because you get a seg fault if you enter a date that is not in the week
            cout << date << ". Has. Been. Cleared." << endl;
            int day;
            day = convertDate(date);
            Event *right=days[day];
            Event *left;
        while (right->next!=NULL){ //pointer to end of list
        right=right->next;
        }
            left=right->prev;
        while(left!=NULL){
            left=right->prev;
            delete right;
            right = left;
        }
        days[day]=NULL;
    }
    else{
        cout<< date<< ". Is. Already. Empty."<<endl;
    }


}
//ADDED:
bool Calendar::isDateInCalender(string date){
// This is needed since you cannot delete or call on a day that is not in the week
    int day;
    day = convertDate(date);
    if(days[day]!=NULL){
        return true;
    }
    else{
        return false;
    }
}
//ADDED:
void Calendar::deleteAll(){
//thought you guys would need a deconstructer
    for(int i=0; i<7; i++){
        Event *temp = days[i];
        string day;
        day = convertDateBack(i);
        clearDay(day);

    }
}

Event *Calendar::findEvent(string title){

    for (int i=0; i<7;i++){
        Event *temp = days[i];
        while (temp!=NULL){
            if (temp->name==title){
                return temp;
            }
            temp=temp->next;
        }
    }
}

Calendar::~Calendar()
{
    deleteAll();
    //cout << "Calendar burned!" << endl;
    // The constructor will be what writes the information to the text file, if we do make it that far.
}
