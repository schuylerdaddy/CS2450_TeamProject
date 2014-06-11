#include"Utility.h"
//include class prototypes/headers here

#pragma once
#include <string>
#include <vector>

using namespace std;

// This class models a DueDate. It contains key information
// about a checked-out-item and methods to manage that data
class DueDate
{
public:
	DueDate(int,int,int);
	string GetDueDate(int); // I set this method with a bookID number because I still don't know if we are dealing with multiple of the same book.
	string GetDueDate(string, string);
	void SetDueDate(int); // I set this method with a bookID number because I still don't know if we are dealing with multiple of the same book.
	void SetDueDate(string, string);
	string ExtendDueDate(int); // This method is for a little extra if we want to look at the possibility to extend the due date once the book is out.
	string ExtendDueDate(string, string); // Same as line above
	~DueDate();
private:
	int month;
	int day;
	int year;
};

// This class models a DueDate. It contains key information
// about a checked-out-item and methods to manage that data
class Patron
{
public:
	Patron(string,string, bool);
	vector<int> GetBookList(int);
        void AssignPatronId();
	~Patron();
private:
    bool idAssigned;
	bool adult;
	vector<int> bookList;
	string patronFirstName;
	string patronLastName;
	int patronID; // In case there are 2 people with the same name we can use their library id card number
	int age;
};
