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
	Date();
	Date(int);//conversion constructor;
	Date(int, int, int);
	void SetDefaultDate();
	int GetMonth();
	int GetDay();
	int GetYear();
	Date operator+=(const Date&);
	bool operator>(const Date&);
	string display();
private:
	int month;
	int day;
	int year;
};

inline Date operator+(Date date1, const Date& date2){
	return date1 += date2;
}

// This class models a Date. It contains key information
// about a checked-out-item and methods to manage that data
class Patron
{
public:
	Patron(string, string, bool);
	vector<int> GetBookList();
	void AssignPatronId(int);
	static Patron ReadPatron(istream&);
	void SavePatron(ostream&);
	int getID(){ return patronID; };
	void checkinBook(int);
	void checkoutBook(int);
	bool canBorrow();
	bool isAdult(){ return adult; };
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
	string GetAuthor();
	string GetTitle(); // What should I pass here? bookID?
	bool GetCheckedInStatus(); // What should I pass here? bookID? Title?
	void CheckIn(); // Should there be a value passed here? bookID? Title?
	void CheckOut(Date); // Should there be a value passed here? bookID? Title?
	void AssignId(int);
	int getID();
	bool isChildrenBook();
	void Save(ostream&);
	static Media read(istream&);
	~Media();
	string display();
	bool isOverdue(Date);
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
