#include <iostream>
#include "CLI.h"

// The CLI default constructor
// Purpose: To initialize needed variables
// Parameters: None
// Returns: None
// Pre-conditions: None
// Post-conditions: Specific variables initialized
// -----------------------------------------------------------------
CLI::CLI()
{
	br = BusinessRules();
}

// The CLI destructor
// Purpose: To destroy
// Parameters: None
// Returns: None
// Pre-conditions: None
// Post-conditions: None
// -----------------------------------------------------------------
CLI::~CLI()
{
}

// The GetIntegerInput Method
// Purpose: To get the input from the user and assign it to the variable "integerInput"
// Parameters: None
// Returns: 1 int
// Pre-conditions: None
// Post-conditions: The variable "integerInput" is returned
// -----------------------------------------------------------------
int CLI::GetIntegerInput()
{
	cin >> integerInput;
	return integerInput;
}

// The GetCharInput Method
// Purpose: To get the input from the user and assign it to the variable "charInput"
// Parameters: None
// Returns: 1 char
// Pre-conditions: None
// Post-conditions: The variable "charInput" is returned
// -----------------------------------------------------------------
char CLI::GetCharInput()
{
	cin >> charInput;
	return charInput;
}

string CLI::GetStringInput()
{
	cin >> stringInput;
	return stringInput;
}

// The MenuOptions Method
// Purpose: To display the Menu for the user
// Parameters: None
// Returns: None
// Pre-conditions: None
// Post-conditions: The variable "integerInput" is returned
// -----------------------------------------------------------------
void CLI::MenuOptions()
{
	cout << "Please choose one of the following options: " << endl;
	cout << "O -> Check out a book" << endl;
	cout << "I -> Check in a book" << endl;
	cout << "L -> List all books" << endl;
	cout << "D -> List overdue books" << endl;
	cout << "P -> List a patron's books" << endl;
	cout << "F -> Find a patron" << endl;
	cout << "A -> Advance the due date" << endl;
	cout << "Q -> Save and Quit this program" << endl;
	cout << "What would you like to do: ";
}

// The RunUserCommand Method
// Purpose: To handle the user input from the menu
// Parameters: 1 char and 1 DueDate& (char choise, DueDate& date)
// Returns: None
// Pre-conditions: User input valid option
// Post-conditions: The correct actions are executed
// -----------------------------------------------------------------
void CLI::RunUserCommand(char choice, Date& date) //How are we handeling the 'present' date?
{
	switch (choice)
	{
	case 'O':
		cout << "Enter patron ID: ";
		patronID = GetStringInput();
		cout << endl << "Enter book ID: ";
		mediaID = GetStringInput();
		//TODO: add the bookID to the correct patron with patronID (done below)
		CheckOutItem(patronID, mediaID);
		break;
	case 'I':
		cout << "Enter Book ID: " << endl;
		mediaID = GetIntegerInput();
		//TODO: Check in book by ID (done below)
		CheckInItem(patronID, mediaID);
		break;
	case 'L':
		cout << "All Books: " << endl;
		//TODO: List all books (done below)
		cout<<ListAllItems();
		break;
	case 'D':
		cout << "Overdue Books: " << endl;
		//TODO: List all overdue books that all patrons have (done below)
		cout<<ListAllOverdueItems();
		break;
	case 'P':
		patronID = GetIntegerInput();
		//TODO: Get patron by ID (done below)
		cout<<ListBooksByPatron(patronID);
		break;
	case 'F':
		cout << "Patrons: " << endl;
		//TODO: List all patrons
		//Nathan says: Do we want this option? Do we want patrons to see who all
		//has access to the library?
		break;
	case 'A':
		cout << "The day is now " << date->GetDay() << "/" << date.GetMonth() << "/" << date.GetYear() << endl;
		//TODO: How are we handeling the current date vs. due date? (done below)
		AdvanceItemDate(mediaID);
		break;
	case 'Q':
		cout << "Ridicule is the best test of truth." << endl;
		//TODO: Save all data to 'database' (Nathan says: do we really need to save? wouldn't we be saving as
		//we go? or do we actually need a save at the very end before we quit?)
		break;
	default:  cout << choice << " is invalid." << endl;
	}

	cout << endl;

}

// The CheckOutItem Method
// Purpose: To check out an item
// Parameters: 2 strings (string patronId, string itemId)
// Returns: None
// Pre-conditions: The item the user wants to check out is valid
// Post-conditions: Item is checked out
// -----------------------------------------------------------------
void CLI::CheckOutItem(string patronId, string itemId)
{

}

// The CheckInItem Method
// Purpose: To check in an item
// Parameters: 2 strings (string patronId, string itemId)
// Returns: None
// Pre-conditions: The item the user wants to check in is valid
// Post-conditions: Item is checked in
// -----------------------------------------------------------------
void CLI::CheckInItem(string patronId, string itemId)
{

}

// The ListAllItems Method
// Purpose: To list all items in library
// Parameters: None
// Returns: 1 string
// Pre-conditions: There are items in the library
// Post-conditions: List of items in library are returned
// -----------------------------------------------------------------
vector<string> CLI::ListAllItems()
{
	vector<string> cool;
	return cool;
}

// The ListAllOverdueItems Method
// Purpose: To list all the items that are overdue
// Parameters: None
// Returns: 1 string
// Pre-conditions: There are items that are overdue
// Post-conditions: List of overdue items are returned
// -----------------------------------------------------------------
vector<string> CLI::ListAllOverdueItems()
{
	vector<string> rad;
	return rad;
}

// The ListBooksByPatron Method
// Purpose: To list all the items a patron has checked out
// Parameters: 1 strings (string patronId)
// Returns: 1 string
// Pre-conditions: The patron is valid and has something checked out
// Post-conditions: A list of items the patron has checked out is returned
// -----------------------------------------------------------------
vector<string> CLI::ListBooksByPatron(string patronId)
{
	vector<string> awesome;
	return awesome;
}

// The AdvanceItemDate Method
// Purpose: To advance the due date of an item
// Parameters: 1 string (string itemId)
// Returns: None
// Pre-conditions: The item is checked out and needs to have an advanced due date
// Post-conditions: The due date of the item is advanced
// -----------------------------------------------------------------
void CLI::AdvanceItemDate(string itemId)
{

}

// The AddLibraryItem Method
// Purpose: To check out an item
// Parameters: 2 strings (string patronId, string itemId)
// Returns: None
// Pre-conditions: There is an item that needs to be added to the library
// Post-conditions: Item is added to the library
// -----------------------------------------------------------------
void CLI::AddLibraryItem(string author, string title, int itemType)
{

}
