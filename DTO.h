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
	int GetMonth();
	int GetDay();
	int GetYear();
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

#include <string>

using namespace std;

// This class models a Book. It contains key information
// about a book and methods to manage that data
class Book
{
	public:
		Book(string, string);
		string GetAuthor(); // What should I pass here? bookID? or title?
		string GetTitle(); // What should I pass here? bookID?
		bool GetCheckedInStatus(); // What should I pass here? bookID? Title?
		void CheckIn(); // Should there be a value passed here? bookID? Title?
		void CheckOut(); // Should there be a value passed here? bookID? Title?
		void AssignId(int);
		~Book();
		// Do we want SetBookID() if we plan on adding books, movies, etc.? 
		// maybe, just below the iceburg line
	private:
		bool idAssigned;
		string author;
		string title;
		int bookID;
		bool checkedIn;
};
