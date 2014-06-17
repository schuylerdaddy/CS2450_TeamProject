#include"Utility.h"
//include class prototypes/headers here

#pragma once
#include <string>
#include <vector>

using namespace std;

int const MAXBOOKSCHECKOUT=6;
int const CHILDLIMIT = 3;

// This class models a Date. It contains key information
// about a checked-out-item and methods to manage that data
class Date
{
public:
	//set Date to today's date
	Date();
	Date(int);//conversion constructor
	//set the date
	//parameter: month, day, year as int
	Date(int, int, int);
	//set default date for books not checked out
	//date set as 1/1/9999
	void SetDefaultDate();
	
	//getters, shoudl we delete them, never used
	int GetMonth();
	int GetDay();
	int GetYear();
	//overloaded operator
	Date operator+=(const Date&);
	bool operator>(const Date&);
	//provides string to display date
	//return strings
	string display();
private:
	int month;
	int day;
	int year;
};
//overloaded + operator
inline Date operator+(Date date1, const Date& date2){
	return date1 += date2;
}

// This class models a Date. It contains key information
// about a checked-out-item and methods to manage that data
class Patron
{
public:
	Patron(string, string, bool);
	//return list of book borrowed by patron as a vector of int (itemID)
	vector<int> GetBookList();
	void AssignPatronId(int);
	
	//read Patron, called from DataAccess
	//parameter: input stream as a reference
	static Patron ReadPatron(istream&);
	//save patron, called from DataAccess
	//parameter: output stream as a reference
	void SavePatron(ostream&);
	int getID(){ return patronID; };
	
	//checkin book, modifies booklist
	//parameter: book being returned
	//return: nothing
	void checkinBook(int);
	//checkout book, modifies booklist
	//parameter: book being checked out
	//return: nothing
	void checkoutBook(int);
	
	//check is user has reached borrowing limit
	//returns: bool, true is under limit, false otherwise
	bool canBorrow();
	bool isAdult(){ return adult; };
	//display patron info
	//returns: string
	string displayPatronInfo();
	~Patron();
private:
	struct PatronRec{
			int id;
			char lastName[15];
			char firstName[15];
			int age;
			int adult;
			int book[MAXBOOKSCHECKOUT];
	};
	bool idAssigned;
	bool adult;
	vector<int> bookList;
	string patronFirstName;
	string patronLastName;
	int patronID; // In case there are 2 people with the same name we can use their library id card number
	int age;
};


// This class models a Book. It contains key information
// about a book and methods to manage that data
class Media
{
public:
	Media(){};
	Media(string, string, MediaTypes);
	//getters not used
	string GetAuthor();
	string GetTitle(); // What should I pass here? bookID?
	bool GetCheckedInStatus(); 
	//change checkin status of the book
	//set due date to default date, year 9999
	void CheckIn(); 
	//checkout book
	//parameter: due date
	void CheckOut(Date); 
	void AssignId(int);
	int getID();
	bool isChildrenBook();
	void Save(ostream&);
	static Media read(istream&);
	~Media();
	string display();
	//check if book is overdue
	//parameter: today's date
	bool isOverdue(Date);
	//returns loan time for the book depending on its type
	int getLoanTime();
private:
	bool idAssigned;
	string author;
	string title;
	int mediaID;
	bool checkedIn;
	MediaTypes type;
	Date due;
	struct MediaRec{
		int id;
		char author[15];
		char title[50];
		int checkIn; //0 false, 1 true
		int type;
		Date due;
	};
};
