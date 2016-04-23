#include <iostream>
#include "Calendar.h"
#include <ctime>
#include <algorithm>
// This is a test comment to make sure I know what I'm doing
using namespace std;

bool isTime(string timeS){
    /*There are two general cases - one where the length is 4 chars long, as in 9:45, and one where the length is 5 chars long
    as in 19:30. If the string is not one of these two lengths, it is invalid. From these two cases, we can determine if the string
    is valid by type casting each char to an int and seeing if it matches the desired result. Quite tedious, but the only way I could
    think to do it without regular expressions, which are not supported by C++98 or Code::Blocks*/
    /*if(timeS.length() == 4){ // The case where the string is only 4 characters long
        if(int(timeS[0]) < 48 || int(timeS[0]) > 57){ // Checking that the first char is an int between 0 and 9
            cout << "Not a valid input" << endl;
            return false;
        }

        if(int(timeS[1]) != 58){ // Making sure the user included the semicolon
            cout << "Not a valid input" << endl;
            return false;
        }
        if(int(timeS[2]) < 48 || int(timeS[2]) > 53){ // Checking that the tens of minutes is the right size
            cout << "Not a valid input" << endl;
            return false;
        }
        if(int(timeS[3]) < 48 || int(timeS[3]) > 57){ // Checking the ones position of the minutes
            cout << "Not a valid input" << endl;
            return false;
        }
    }
    else*/ // THis was some code I needed, but I changed it to add a 0 if the length is 4. But it's still here if you want to change it
    if(timeS.length() == 5){ // The case when the string is 5 chars long
        if(int(timeS[0]) >= 48 && int(timeS[0]) <= 49){ // Making sure that the first char is between 0 and 1
            if(int(timeS[1]) < 48 || timeS[1] > 57){ // Checking the second char of the string
                cout << "Not a valid input" << endl;
                return false;
            }
        }
        else if(int(timeS[0]) == 50){ // When the first char is 2, the second char cannot be greater than 3
            if(int(timeS[1]) < 48 || timeS[1] > 51){ // Checking the second char of the string
                cout << "Not a valid input" << endl;
                return false;
            }
        }
        else{
            cout << "Not a valid input" << endl; // When the first char is not between 0 and 2
            return false;
        }

        if(int(timeS[2]) != 58){ // Making sure the user included the semicolon
            cout << "Not a valid input" << endl;
            return false;
        }
        if(int(timeS[3]) < 48 || int(timeS[3]) > 53){ // Checking that the tens of minutes is the right size
            cout << "Not a valid input" << endl;
            return false;
        }
        if(int(timeS[4]) < 48 || int(timeS[4]) > 57){ // Checking the ones position of the minutes
            cout << "Not a valid input" << endl;
            return false;
        }
    }
    else{ // If the user didn't even get the length right
        cout << "Your time was not the right size" << endl;
        return false;
    }
    return true;
}

bool isDate(string date){
    /*This function takes user input and makes sure that it is properly formatted as a day of the week. It's basically just a really long
    conditional operator. */

    if(date=="Sunday"||date=="Monday"||date=="Tuesday"||date=="Wednesday"||date=="Thursday"||date=="Friday"||date=="Saturday"){
        return true;
    }
    cout << "Not a valid input" << endl;
    return false;
}

int main()
{
    cout << "Welcome to Matt and Paul's Calendar!" << endl;

    string response;

    Calendar schedule;
    schedule.getTodaysDate();

    string title;
    string description;
    string timeStart;
    string timeEnd;
    string date;
    bool endLater = true;

    while(true){
        cout << "======MAIN MENU======"<<endl;
        cout << "What would you like to do?" << endl;
        cout << "Press 'g' to get today's date" << endl;
        cout << "Press 'a' to add an event" << endl;
        cout << "Press 't' to show a day's events" << endl;
        cout << "Press 'w' to show the week's events" << endl;
        cout << "Press 's' to show the slots for a specific time period" << endl;
        cout << "Press 'd' to delete a specific event" << endl;
        cout << "Press 'l' to look for an event" << endl;
        cout << "Press 'c' to clear all events for a day" << endl;
        cout << "Press 'q' to exit the program" << endl;

        getline(cin, response);

        if(response == "g"){
            schedule.getTodaysDate(); // A simple function that prints today's date
        }
        else if(response == "a"){ // This adds an event and uses all functionality in 'main.cpp'. For reference on why things are there, check here
            do{ // This do while loop repeatedly checks to make sure that the user had a good input
                cout<< "What day is your event on (eg. Monday)"<<endl; // Gets the day of the week
                getline(cin,date); // Takes the day of the week and stores it as date
                // The next two lines efficiently make the user's input case insensitive to create a smarter program
                transform(date.begin(), date.end(), date.begin(), ::tolower); // Makes the while string lowercase
                date[0] = toupper(date[0]); // converts the very first character to uppercase, as is standard
            }while(!isDate(date)); // Repeat while it is not a valid date
            cout << "What is the title of your event?" << endl; // No checks necessary - the user can call their event whatever they like
            getline(cin, title); // Takes the input of the event and stores it as title
            cout << "Give a brief description of the event: " << endl; // Again, the user can call their description whatever they want
            getline(cin, description);
            do{
                cout << "Enter starting hour (eg. 14:30 or 9:15): " << endl; // Tells the user what to enter
                getline(cin, timeStart); // Gets the event start time from the user
                if(timeStart.length() == 4){ // This adds a 0 at the beginning if necessary for comparison purposes
                    timeStart = "0" + timeStart;
                }
            }while(!isTime(timeStart));
            do{
                cout << "Enter finishing hour (eg. 14:30 or 9:15)" << endl;
                getline(cin, timeEnd); // Takes the event's finish time and stores it as timeEnd
                endLater = true; // This resets the boolean value to see if the end time is before the beginning time
                if(timeEnd.length() == 4){ // Adds a 0 if necessary. Again for comparison purposes
                    timeEnd = "0" + timeEnd;
                }
                if(timeStart > timeEnd){ // Checking to make sure the finish time is not before the start time
                    endLater = false; // This triggers the bool if the end is, in fact, before the beginning. Notice that they can be the same time
                    cout << "Your finishing time is sooner than your start time!" << endl; // Let the user know what's up
                }
            }while(!isTime(timeEnd) || !endLater); // If either condition is false, we need to repeat the loop until the user stops screwing up

            schedule.addEvent(date,title, description, timeStart, timeEnd); // Finally we add our perfected variables to our class
        }
        else if(response == "t"){
            do{
                cout<<"Enter a day (eg. Monday)"<<endl;
                getline(cin,date);
                transform(date.begin(), date.end(), date.begin(), ::tolower);
                date[0] = toupper(date[0]);
            }while(!isDate(date));

            schedule.showTodaysEvents(date);
        }
        else if(response == "w"){
            schedule.printWeek();
        }
        else if(response == "s"){
            do{
                cout << "Enter the day you want to check: " << endl;
                getline(cin, date);
                transform(date.begin(), date.end(), date.begin(), ::tolower); // Makes the while string lowercase
                date[0] = toupper(date[0]); // converts the very first character to uppercase, as is standard
            }while(!isDate(date));
            do{
                cout << "Enter starting hour (eg. 14:30 or 9:15): " << endl; // Tells the user what to enter
                getline(cin, timeStart); // Gets the event start time from the user
                if(timeStart.length() == 4){ // This adds a 0 at the beginning if necessary for comparison purposes
                    timeStart = "0" + timeStart;
                }
            }while(!isTime(timeStart));
            do{
                cout << "Enter finishing hour (eg. 14:30 or 9:15)" << endl;
                getline(cin, timeEnd); // Takes the event's finish time and stores it as timeEnd
                endLater = true; // This resets the boolean value to see if the end time is before the beginning time
                if(timeEnd.length() == 4){ // Adds a 0 if necessary. Again for comparison purposes
                    timeEnd = "0" + timeEnd;
                }
                if(timeStart > timeEnd){ // Checking to make sure the finish time is not before the start time
                    endLater = false; // This triggers the bool if the end is, in fact, before the beginning. Notice that they can be the same time
                    cout << "Your finishing time is sooner than your start time!" << endl; // Let the user know what's up
                }
            }while(!isTime(timeEnd) || !endLater);

            schedule.printSlots(date, timeStart, timeEnd);
        }
        else if(response == "d"){
            cout << "Enter the title of the event you would like to delete:" << endl;
            getline(cin, title);

            schedule.deleteEvent(title);
        }
        else if(response == "l"){
            cout << "Enter the title of the event:" << endl;
            getline(cin, title);

            schedule.eventDetails(title);
        }
        else if(response == "c"){
            do{
                cout << "Enter the day you'd like to clear:" << endl;
                getline(cin, date);
                transform(date.begin(), date.end(), date.begin(), ::tolower); // Makes the while string lowercase
                date[0] = toupper(date[0]); // converts the very first character to uppercase, as is standard
            }while(!isDate(date));

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
