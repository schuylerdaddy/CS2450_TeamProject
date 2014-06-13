#pragma once
#include <string>
#include <vector>

using namespace std;


// This class models a DueDate. It contains key information
// about a checked-out-item and methods to manage that data
class DueDate
{
public:
	DueDate();
	DueDate(int, int, int);
	int GetMonth();
	int GetDay();
	int GetYear();
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
	Patron(string, string, bool);
	vector<int> GetBookList(int);
	void AssignPatronId(int);
	static Patron ReadPatron(istream&);
	void SavePatron(ostream&);
	int getID(){ return patronID; };
	~Patron();
private:
	struct PatronRec{
			int id;
			char lastName[15];
			char firstName[15];
			int age;
			bool adult;
			int book[6];
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
	Media(string, string, int);
	string GetAuthor();
	string GetTitle(); // What should I pass here? bookID?
	bool GetCheckedInStatus(); // What should I pass here? bookID? Title?
	void CheckIn(); // Should there be a value passed here? bookID? Title?
	void CheckOut(); // Should there be a value passed here? bookID? Title?
	void AssignId(int);
	int getID();
	void Save(ostream&);
	static Media read(istream&);
	~Media();

private:
	bool idAssigned;
	string author;
	string title;
	int mediaID;
	bool checkedIn;
	int type;
	DueDate due;
	struct MediaRec{
		int id;
		char author[15];
		char title[30];
		bool checkIn;
		int type;
		DueDate due;
	};
};
