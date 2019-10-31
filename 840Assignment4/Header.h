
#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <typeinfo>
#include <iomanip>
using namespace std;

//////////////////////////////////////
//Class definitions
////////////////////////////////////

//DATE
class Date
{
private:
	int day, month, year;
public:
	Date(int = 1, int = 1, int = 1900);
	void set(int = 1, int = 1, int = 1900);
	void get();
	void print() const;
	bool operator==(const Date &) const;
};

//TIME
class Time
{
private:
	int hour, minute;
public:
	Time(int = 0, int = 0);
	void set(int = 0, int = 0);
	void get();
	void print() const;
	int get_hour() const;
	int get_minute() const;
	Time operator-(const Time &) const; // returns the difference of two Time objects
	bool operator==(const Time &) const; // compares two Time objects and returns True if first < second
	bool operator<(const Time &) const; // compares two Time objects and returns True if first < second
	bool operator>(const Time &) const; // compares two Time objects and returns True if first > second
	float operator*(float hourlyCharge) const; //hoping to overload the operator in order to do math with Time
};

//APPOINTMENT
class Appointment
{
protected:
	Date date;
	Time start_time, end_time;
	char description[40], location[40];
public:
	Appointment();
	virtual void get();//added virtual to get
	virtual void print() const;//added virtual to print
	Date get_date() const;
	Time get_start_time() const;
	Time get_end_time() const;
};

//CLIENTSESSION
class ClientSession : public Appointment
{
protected://change private to protected so I can inherite this class into CourtSession!
	char id[11];//client ID //teacher seems to want it as c-string
	char fname[21];//first name
	char lname[21];//last name
	float charge;//hourly charge
public:
	char* get_id() { return &id[0]; }//get_id() returns the address of the 0 position
	char* get_lname() { return &lname[0]; }
	char* get_fname() { return &fname[0]; }
	float get_charge() { return charge; };
	float calc_charge() const; //function to multiply time by a double
	virtual void get(); //added virtual to get
	virtual void print() const; //added virtual to print
	ClientSession();
};

//COURTSESSION
class CourtSession : public ClientSession //derived from ClientSession which is derived from Appointment
{
private:
	char courtName[51];
	char courtLocation[201];//longer c-string for a potential long address
public:
	char* getcourtName() { return &courtName[0]; }
	char* getcourtLocation() { return &courtLocation[0]; }
	void get(); //did NOT add virtual because this one does not get overwritten
	void print() const; //did NOT add virtual because this one does not get overwritten
	CourtSession();
};

#endif