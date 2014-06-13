#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "DTO.h"

// Purpose: To initialize needed variables to default date
// Parameters: none
// Returns: None
// Pre-conditions: None
// Post-conditions: Specific variables initialized
// -----------------------------------------------------------------
DueDate::DueDate(){
	month = 1;
	day = 1;
	year = 9999;

}

// Purpose: To initialize needed variables
// Parameters: None
// Returns: None
// Pre-conditions: None
// Post-conditions: Specific variables initialized
// -----------------------------------------------------------------
DueDate::DueDate(int m,int d,int y)
{
  if(m>12 || m<1 || d<1 || d>31)
    throw runtime_error("invalid date");
  month = m;
  day = d;
  year = y;
}

int DueDate::GetMonth()
{
  return month;
}

int DueDate::GetDay()
{
  return day;
}

int DueDate::GetYear()
{
  return year;
}

DueDate::~DueDate()
{
}

//define constructors and function implementations here
// The constructor
// Purpose: To initialize needed variables
// Parameters: None
// Returns: None
// Pre-conditions: None
// Post-conditions: Specific variables initialized
// -----------------------------------------------------------------
Patron::Patron(string fName, string lName,bool isAdult)
{
  patronFirstName = fName;
  patronLastName = lName;
  adult = isAdult;
  bookList = new vector<int>();
  idAssigned = false;
}

// The GetBookList Method
// Purpose: To see which books a certain patron has checked out
// Parameters: 1 int (int patronID)
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
  if(!idAssigned)
    {
      idAssigned = true;
      patronID = id;
    }
  else
    {
      throw runtime_error("Can't reassign user id");
    }
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

Patron Patron::ReadPatron(istream& is){
	PatronRec inputRec;
	is.read(reinterpret_cast<char*>(&inputRec), sizeof(inputRec));
	
	Patron user(inputRec.firstName, inputRec.lastName, inputRec.adult);
	user.AssignPatronId(inputRec.id);
	int i = 0;
	while (inputRec.book[i] != 0)
		user.bookList.push_back(inputRec.book[i]);

	return user;	
}

void Patron::SavePatron(ostream& os){
	if (!os)
		throw runtime_error("error saving patron information 2");
	PatronRec outputRec;
	outputRec.adult = adult;
	outputRec.id = patronID;
	outputRec.age = age;
	strncpy(outputRec.lastName, patronLastName.c_str(), 15)[15] = '\0';
	strncpy(outputRec.firstName, patronFirstName.c_str(), 15)[15] = '\0';
	for (int i = 0; i < bookList.size(); ++i)
		outputRec.book[i] = bookList[i];
	for (int i=bookList.size(); i<6; ++i)
		outputRec.book[i] = 0;
	os.write(reinterpret_cast<const char*>(&outputRec), sizeof(outputRec));
} 

Book::Book(string auth, string ttl, int _type)
{
	author = auth;
	title = ttl;
	idAssigned = false;
	checkedIn = true;
	type=_type;
}

// The GetAuthor Method
// Purpose: To get the author of a certain book
// Parameters: None
// Returns: string
// Pre-conditions: There is a valid author wanted for a specific book
// Post-conditions: Author of specific book is returned to the user interface
// -----------------------------------------------------------------
string Book::GetAuthor()
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
string Book::GetTitle()
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
bool Book::GetCheckedInStatus()
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
void Book::CheckIn()
{
	checkedIn = true;
}

// The CheckedOut Method
// Purpose: To set the bool variable checkedIn to false
// Parameters: None
// Returns: None
// Pre-conditions: The book exist within the library
// Post-conditions: The book's checkedIn value is set to false
// -----------------------------------------------------------------
void Book::CheckOut()
{
	checkedIn = false;
}

void AssignId(int id)
{
  if(!idAssigned)
    {
      bookId = id;
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
Book::~Book()
{
}

void Media::Save(ostream& os){
	MediaRec outputRec;
	outputRec.checkIn = checkedIn;
	outputRec.id = mediaID;
	strncpy(outputRec.author, author.c_str(), 15)[15] = '\0';
	strncpy(outputRec.title, title.c_str(), 30)[30] = '\0';
	outputRec.type = type;
	outputRec.due = due;
	
	os.write(reinterpret_cast<const char*>(&outputRec), sizeof(outputRec));
}

Media Media::read(istream& is){
	MediaRec inputRec;
	is.read(reinterpret_cast<char*>(&inputRec), sizeof(inputRec));
	//MediaRec inputRec = *(reinterpret_cast<MediaRec*>(data));
	Media item (inputRec.author, inputRec.title, inputRec.type);
	item.AssignId(inputRec.id);
	if (!inputRec.checkIn) item.checkedIn = false;

	return item;
}

int Media::getID(){
	return mediaID;
}
