#include"Utility.h"
//include class prototypes/headers here

#pragma once
#include <string>

using namespace std;

// This class models a DueDate. It contains key information
// about a checked-out-item and methods to manage that data
class DueDate
{
public:
	DueDate(string,string,string);
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
