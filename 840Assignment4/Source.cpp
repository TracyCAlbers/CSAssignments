//Tracy Albers
//CS 840
//880081954

#include <iostream>
#include <iomanip>//for formatting outputs
#include <conio.h>//for getch()
#include "Header.h"
using namespace std;

int main()
{
	/*In main, create an array of Appointment pointers and ask the user repeatedly if they want to enter 
	a ClientSession or CourSession. In either case, create the requested session, read the required information, 
	save the pointer in the array of Appointment pointers, and when done, list all created sessions, printing 
	all their information. Also, print the calculated charge for each session.*/
	
	const int maxAppointments = 100; //set max appointments to whatever wanted, 100 seemed good
	char ClientVsCourt = '1'; //need a char to determine what they would like to enter and if they would like to be finished, initialized to '1' to enter the loop

	Appointment* ptrAppointments[maxAppointments]; //in main, create an array of Appointment Pointers
	int SessionCount = 0; //keep track of added Sessions


	cout << "Thank you for using the Court and Client Appointment Tracker!";
	cout << "\nBy Tracy Albers, CS 840\n\n";//it was fun seeing my name on Assignment 3.  :)

	for (int i = 0; i < maxAppointments && (ClientVsCourt == '1' || ClientVsCourt == '2'); i++)
	{
		cout << "Make a Selection \n[ 1 ] Client Session \n[ 2 ] Court Session \nAny other key to display entries\nChoice: ";
		cin >> ClientVsCourt;
		system("cls");//clear screen before every new entry or display
		if (ClientVsCourt == '1')
		{
			ptrAppointments[i] = new ClientSession;
		}
		else if (ClientVsCourt == '2')
		{
			ptrAppointments[i] = new CourtSession;
		}
		else
		{
			break;
		}
		ptrAppointments[i]->get();
		SessionCount++;
	}
	cout << "\nSessions: \n";
	
	for (int i = 0; i < SessionCount; i++)
	{
		cout << endl;
		ptrAppointments[i]->print(); //call print function from pointer
	}

	cout << "\nPress any key to exit.\n";
	_getch();
	delete[] ptrAppointments; //delete the entire array before exiting to avoid a memory leak
	return 0;
}

//Class Functions///////////////////////////////////////////////////////////////

//DATE CLASS

Date::Date(int d, int m, int y)
{
	set(d, m, y);
}

void Date::set(int d, int m, int y)
{
	if (d >= 1 && d <= 31)
		day = d;
	else
	{
		cout << "\ninvalid day";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
	if (m >= 1 && m <= 12)
		month = m;
	else
	{
		cout << "\ninvalid month";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
	if (y >= 1900 && y <= 3000)
		year = y;
	else
	{
		cout << "\ninvalid year";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
}

void Date::get()
{
	char ch;

	cout << "Enter date in mm/dd/yyyy format: ";
	cin >> month >> ch >> day >> ch >> year;

	while (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 3000)
	{
		cout << "\nInvalid date entered" << endl;
		cout << "\nEnter date in mm/dd/yyyy format: ";
		cin >> day >> ch >> month >> ch >> year;
	}
}

void Date::print() const
{
	cout << day << "/" << month << "/" << year;
}

bool Date::operator==(const Date &d) const
{
	return day == d.day && month == d.month && year == d.year;
}

//TIME CLASS

Time::Time(int h, int m)
{
	set(h, m);
}

void Time::set(int h, int m)
{
	if (h >= 0 && h <= 24)
		hour = h;
	else
	{
		cout << "\nInvalid hour";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}

	if (m >= 0 && m <= 60)
		minute = m;
	else
	{
		cout << "\nInvalid minute";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
}

void Time::get()
{
	char ch;

	cout << "Enter time in military [hour:minute] format: ";
	cin >> hour >> ch >> minute;

	while (hour < 0 || hour > 24 || minute < 0 || minute > 60)
	{
		cout << "\nInvalid time entered";
		cout << "\nEnter time in military [hour:minute] format: ";
		cin >> hour >> ch >> minute;
	}
}

void Time::print() const
{
	cout << setw(2) << setfill('0') << hour //changed original code to show leading zeros of hour
		<< ':'								//colon
		<< setw(2) << setfill('0') << minute;//changed original code to show leading zeros of minute
}

int Time::get_hour() const
{
	return hour;
}

int Time::get_minute() const
{
	return minute;
}

Time Time::operator-(const Time &t) const
{
	if (minute >= t.minute)   // check minutes before creating the temp object
		return Time(hour - t.hour, minute - t.minute);
	else
		return Time(hour - t.hour - 1, minute + 60 - t.minute);
}

bool Time::operator==(const Time &t) const
{
	return hour == t.hour && minute == t.minute;
}

bool Time::operator<(const Time &t) const
{
	if (hour < t.hour)
		return true;
	else if ((hour == t.hour) && (minute < t.minute))
		return true;
	else
		return false;
}

bool Time::operator>(const Time &t) const
{
	return !(*this == t) && !(*this < t); // if not equal and not less, it must be greater
}

float Time::operator*(float hourlyCharge) const //outputs a float, acts on a Time object, takes in a regular float to do the math
{ // Need to multiply hours and minutes by a number and return a double
	float total = 0;//must initialize to zero each time function is called
	total += this->get_hour() * hourlyCharge; //multiple hourly charge by hour, straight multiplication
	total += (float(this->get_minute()) / 60) * hourlyCharge;//multiply hourley charge by minute but divide by 60 to 
	return total;
}

//APPOINTMENT CLASS

Appointment::Appointment() : date(), start_time(), end_time()
{
	strcpy(description, "");
	strcpy(location, "");
}

void Appointment::get()
{
//	char c; only used for description and location

	date.get();

	do
	{
		cout << "Start time - ";
		start_time.get();

		cin.ignore(20, '\n');

		cout << "End time - ";
		end_time.get();

		cin.ignore(20, '\n');

		if (start_time.get_hour() > end_time.get_hour())
			cout << "\nEnd time cannot be earlier than start time" << endl;

	} while (start_time.get_hour() > end_time.get_hour());
	//The prompt for this assignment does not use desc or location
	/*
	cout << "Enter description: ";
	int i = 0;
	cin.get(c);
	while (c != '\n') 
	{
		description[i++] = c;
		cin.get(c);
	}
	description[i] = '\0';

	cout << "Enter location: ";
	i = 0;
	cin.get(c);
	while (c != '\n')
	{
		location[i++] = c;
		cin.get(c);
	}
	location[i] = '\0';*/ 
}

void Appointment::print() const
{ //modified for this assignment to simply print date and time
/*	cout << "\nAppointment Date: ";
	date.print();
	cout << "\nStart time: ";
	start_time.print();
	cout << "\nEnd time: ";
	end_time.print();
	cout << "\nDescription: " << description;
	cout << "\nLocation: " << location;*/
	cout << "Date: ";
	date.print();
	cout << " Time: ";
	start_time.print();
}

Date Appointment::get_date() const
{
	return date;
}

Time Appointment::get_start_time() const
{
	return start_time;
}

Time Appointment::get_end_time() const
{
	return end_time;
}

//CLIENT SESSION CLASS

ClientSession::ClientSession() : Appointment() //called the appointment constructor
{
	strcpy(fname, ""); //set's first name to null
	strcpy(lname, ""); //set's last name to null
	strcpy(id, ""); //set's ID to null
	charge = 0; // set charge to zero
}

float ClientSession::calc_charge() const
{
	return ((end_time - start_time) * this->charge);
}

void ClientSession::get()
{
	char c;
	Appointment::get();//reuse code :)

	cout << "Enter client I.D.: ";
	//Experimenting with a different way to get c-string, works great
	//memset(id, 0, sizeof(id));//clears whole array to zero
	//scanf("%10s", id);// "get from a user, something that is treated as a string", and stored in ID
	//fgets(id, sizeof(id), stdin);//gets id to the size of id until null terminator from std in
	int i = 0;
	cin.get(c);
	while (c != '\n')
	{
		id[i++] = c;
		cin.get(c);
	}
	id[i] = '\0';

	cout << "Enter client first name: ";
	i = 0;
	//cin.ignore();
	cin.get(c); //grab the first char
	while (c != '\n') // check if it equals newline
	{
		fname[i++] = c; //set the char to the location 
		cin.get(c); //grab the next char to start the loop again
	}
	fname[i] = '\0';

	cout << "Enter client last name: ";
	i = 0;
	cin.get(c);
	while (c != '\n')
	{
		lname[i++] = c;
		cin.get(c);
	}
	lname[i] = '\0';

	cout << "Enter hourly charge: ";
	cin >> charge;
}

void ClientSession::print() const
{/*
	Appointment::print();
	cout << "\nClient I.D.: " << id << endl
		<< "Client name: " << fname << ' ' << lname << endl
		<< "Charges: " << showpoint << setprecision(2) << fixed << this->calc_charge() << endl; //need to show actual charges
*/
	cout << "\nClient I.D.: " << id << ", "
		<< "Client Name: " << fname << ' ' << lname << ", ";
	Appointment::print();//prints date and start time
	Time elapsed = end_time - start_time; 
	cout << "\n\tHours Spent: ";
	elapsed.print();
	cout << ", Cost per Hour: $" << showpoint << setprecision(2) << fixed << charge <<
			", Total Charges: $" << showpoint << setprecision(2) << fixed << this->calc_charge() << endl;
}

//COURT SESSION

CourtSession::CourtSession() : ClientSession() //Call the ClientSession constructor
{
	strcpy(courtName, "");//set court name to NULL
	strcpy(courtLocation, ""); //set court location to NULL
}

void CourtSession::get()
{
	ClientSession::get(); //call the get of ClientSession to reuse code

	/*printf("Enter Court Name: \0");//printf works just like cout in this case
	cin.ignore();//needed to clear the keyboard buffer
	memset(courtName, 0, sizeof(courtName));//clears courtName to zero if not already
	fgets(courtName, sizeof(courtName), stdin); //gets the characters until enter is pressed
	printf("Enter Court Location: \0"); //also works like cout in this case
	memset(courtLocation, 0, sizeof(courtLocation)); //clears courtLocation to zero if not already
	fgets(courtLocation, sizeof(courtLocation), stdin);//gets the characters until enter is pressed
	this is equivalent to*/

	cout << "Enter Court Name: ";
	char c; // a character c to grab the characters one at a time
	int i = 0; // int i for the while loop
	cin.ignore(); //clear the keyboard buffer
	cin.get(c); //grab the first character
	while (c != '\n') //continue as long as character does not = \n
	{
		courtName[i++] = c; //put the character in the c-string, increment i
		cin.get(c); //grab the next character
	}
	courtName[i] = '\0';//set the last character to the null terminator
	cout << "Enter Court Address: ";
	i = 0; //reset i to zero
	cin.get(c); //grab the first char
	while (c != '\n') //continue as long as character does not = \n
	{
		courtLocation[i++] = c; //save char to c-string, increment i
		cin.get(c); //grab the next character
	}
	courtLocation[i] = '\0'; //set last character to the null terminator 
}

void CourtSession::print() const
{
	cout << "\nClient I.D.: " << id << ", "
		<< "Client Name: " << fname << ' ' << lname << endl 
		<< "Court: " << courtName << ", "//this print is different from Client Session because of courtName and Location
		<< "Location: " << courtLocation << ", ";
	Appointment::print();//prints date and start time
	Time elapsed = (end_time - start_time);//creates a new time object, uses overloaded -
	cout << "\n\tHours Spent: ";
	elapsed.print();
	cout << ", Cost per Hour: $" << showpoint << setprecision(2) << fixed << charge <<
		", Total Charges: $" << showpoint << setprecision(2) << fixed << this->calc_charge() << endl;
}



