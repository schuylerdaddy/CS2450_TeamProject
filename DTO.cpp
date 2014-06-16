#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "DTO.h"
#include <iostream>

using namespace std;

// Purpose: To initialize needed variables to default date
// Parameters: none
// Returns: None
// Pre-conditions: None
// Post-conditions: Specific variables initialized
// -----------------------------------------------------------------
Date::Date(){
	string current = Utility::GetCurrentDate();
	//parse current string to set date
	int pos = current.find("-");
	month = stoi(current.substr(0, pos ));
	int pos2 = current.find("-", pos + 1);
	day = stoi(current.substr(pos + 1, pos2 - pos));
	year = stoi(current.substr(pos2 + 1));
}

Date::Date(int _day){
	day = _day;
}
// Purpose: To initialize needed variables
// Parameters: month, day, year as integers
// Returns: None
// Pre-conditions: None
// Post-conditions: Specific variables initialized
// -----------------------------------------------------------------
Date::Date(int m, int d, int y)
{
	if (m>12 || m<1 || d<1 || d>31)
		throw runtime_error("invalid date");
	month = m;
	day = d;
	year = y;
}

void Date::SetDefaultDate(){
	month = 1;
	day = 1;
	year = 9999;
}



Date Date::operator+=(const Date& date){
	day += date.day;
	map<int, int> numday = Utility::GetDayCountbyMonth(year);
	if (day > numday[month]){ 
		day = day - numday[month];
		month++;
		if (month > 12){
			month = 1;
			year++;
		}
	}
	return *this;
}

bool Date::operator> (const Date& date){
	if (year > date.year)
		return true;
	else if (year < date.year)
		return false;
	else if (month>date.month)
		return true;
	else if (month < date.month)
		return false;
	else if (day>date.day)
		return true;
	else
		return false;

}

void Date::display(){
	cout << month << "/" << day << "/" << year;
}

//getters

int Date::GetMonth(){
	return month;
}

int Date::GetDay(){
	return day;
}

int Date::GetYear(){
	return year;
}

//Patron class
//define constructors and function implementations here
// The constructor
// Purpose: To initialize needed variables
// Parameters: None
// Returns: None
// Pre-conditions: None
// Post-conditions: Specific variables initialized
// -----------------------------------------------------------------
Patron::Patron(string fName, string lName, bool isAdult)
{
	patronFirstName = fName;
	patronLastName = lName;
	adult = isAdult;
	idAssigned = false;
}

// The GetBookList Method
// Purpose: To see which books a certain patron has checked out
// Parameters: none
// Returns: string
// Pre-conditions: Valid parameter values in order to see which books a certain patron has checked out
// Post-conditions: A list of books that the patron currecntly has checked out is returned to the user interface
// -----------------------------------------------------------------
vector<int> Patron::GetBookList()
{
	return bookList;
}

void Patron::AssignPatronId(int id)
{
	if (!idAssigned){
		idAssigned = true;
		patronID = id;
	}
	else{
		throw runtime_error("Can't reassign user id");
	}
}


Patron Patron::ReadPatron(istream& is){
	PatronRec inputRec;
	is.read(reinterpret_cast<char*>(&inputRec), sizeof(inputRec));
	
	Patron user(inputRec.firstName, inputRec.lastName, inputRec.adult);
	user.AssignPatronId(inputRec.id);
	int i = 0;
	while (inputRec.book[i] != 0){
		user.bookList.push_back(inputRec.book[i]);
		++i;
	}

	return user;	
}

void Patron::SavePatron(ostream& os){
	if (!os)
		throw runtime_error("error saving patron information 2");
	PatronRec outputRec;
	outputRec.adult = adult;
	outputRec.id = patronID;
	//outputRec.age = age;
	strncpy(outputRec.lastName, patronLastName.c_str(), 15)[15] = '\0';
	strncpy(outputRec.firstName, patronFirstName.c_str(), 15)[15] = '\0';
	for (size_t i = 0; i < bookList.size(); ++i)
		outputRec.book[i] = bookList[i];
	for (int i=bookList.size(); i<6; ++i)
		outputRec.book[i] = 0;
	os.write(reinterpret_cast<const char*>(&outputRec), sizeof(outputRec));
} 

void Patron::checkinBook(int itemID){
	bool found = false;
	for (size_t i = 0; i < bookList.size(); ++i){
		if (bookList[i] == itemID){
			bookList.erase(bookList.begin() + i);
			found = true;
			break;
		}
	}
	if (!found)
		throw runtime_error("Book not borrowed by patron");
}

void Patron::checkoutBook(int itemID){
	if (bookList.size() < MAXBOOKSCHECKOUT)
		bookList.push_back(itemID);
	else
		throw runtime_error("Too many books checked out.");
}

bool Patron::canBorrow(){
	if (adult){
		if (bookList.size() < MAXBOOKSCHECKOUT)
			return true;
		else return false;
	}
	else
	if (bookList.size() < CHILDLIMIT)
		return true;
	else
		return false;
}

void Patron::displayPatronInfo(){
	cout << patronID << ": " << patronFirstName << " " << patronLastName<<endl;
}
// The Patron Destructor
// Purpose: To delete a patron
// Parameters: None
// Returns: None
// Pre-conditions: Patron that we are attempting to delete exist and can be deleted
// Post-conditions: Correct patron deleted
// -----------------------------------------------------------------
Patron::~Patron()
{

}

Media::Media(string auth, string ttl, MediaTypes _type)
{
	author = auth;
	title = ttl;
	type = _type;
	due.SetDefaultDate();
	idAssigned = false;
	checkedIn = true;
}

// The GetAuthor Method
// Purpose: To get the author of a certain book
// Parameters: None
// Returns: string
// Pre-conditions: There is a valid author wanted for a specific book
// Post-conditions: Author of specific book is returned to the user interface
// -----------------------------------------------------------------
string Media::GetAuthor()
{
	return author;
}

// The GetTitle Method
// Purpose: To get the title of a certain book
// Parameters: None
// Returns: string
// Pre-conditions: There is a valid title wanted for a specific book
// Post-conditions: Title of specific book is returned to the user interface
// -----------------------------------------------------------------
string Media::GetTitle()
{
	return title;
}

// The GetCheckedInStatus Method
// Purpose: To see if the book in question is checked in or checked out
// Parameters: None
// Returns: bool
// Pre-conditions: The book exist in the library
// Post-conditions: Wheather the book is checked in or checked out is returned to the user interface
// -----------------------------------------------------------------
bool Media::GetCheckedInStatus()
{
	return checkedIn;
}

// The CheckedIn Method
// Purpose: To set the bool variable checkedIn to true
// Parameters: None
// Returns: None
// Pre-conditions: The book exist within the library
// Post-conditions: The book's checkedIn value is set to true
// -----------------------------------------------------------------
void Media::CheckIn()
{
	checkedIn = true;
	due.SetDefaultDate();
}

// The CheckedOut Method
// Purpose: To set the bool variable checkedIn to false
// Parameters: None
// Returns: None
// Pre-conditions: The book exist within the library
// Post-conditions: The book's checkedIn value is set to false
// -----------------------------------------------------------------
void Media::CheckOut(Date date)
{
	checkedIn = false;
	//need to change date
	due = date;
}

void Media::AssignId(int id)
{
	if (!idAssigned)
	{
		mediaID = id;
		idAssigned = true;
	}
	else
		throw runtime_error("can't reassign book's id");
}

// The Book destructor
// Purpose: To destroy a book
// Parameters: None
// Returns: None
// Pre-conditions: The book actually exist within the library
// Post-conditions: The book is deleted
// -----------------------------------------------------------------
Media::~Media()
{
}

void Media::Save(ostream& os){
	MediaRec outputRec;
	outputRec.checkIn = checkedIn;
	outputRec.id = mediaID;
	strncpy(outputRec.author, author.c_str(), 15)[15] = '\0';
	strncpy(outputRec.title, title.c_str(), 50)[50] = '\0';
	outputRec.type = type;
	outputRec.due = due;
	
	os.write(reinterpret_cast<const char*>(&outputRec), sizeof(outputRec));
}

Media Media::read(istream& is){
	MediaRec inputRec;
	is.read(reinterpret_cast<char*>(&inputRec), sizeof(inputRec));
	
	Media item (inputRec.author, inputRec.title, MediaTypes(inputRec.type));
	item.AssignId(inputRec.id);
	if (!inputRec.checkIn){
		item.checkedIn = false;
		item.due = inputRec.due;
	}
	else{
		item.checkedIn = true;
		item.due.SetDefaultDate();
	}

	return item;
}

int Media::getID(){
	return mediaID;
}

void Media::display(){
	cout << mediaID << ": " << author << " " << title;
	if (checkedIn)
		cout << " Available";
	else{
		cout << " Checked out";
		due.display();
	}
	cout << endl;
}

bool Media::isOverdue(Date today){
	return (today > due);
}

int Media::getLoanTime(){
	return Utility::DaysByItemType[type];
}
