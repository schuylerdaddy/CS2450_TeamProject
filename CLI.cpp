#include <iostream>
#include "CLI.h"

using namespace std;

BusinessRules CLI::br;

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
	string input;
	getline(cin, input);
	input=Utility::Trim(input);
	if (input.length() != 1)
		throw runtime_error("Enter a single character");
	charInput = input[0];
	return charInput;
}

string CLI::GetStringInput()
{
	getline(cin,stringInput);
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
	cout << "B -> Add a new item" << endl;
	cout << "N -> Add a new patron" << endl;
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
void CLI::RunUserCommand(char choice) //How are we handeling the 'present' date?
{
	choice = toupper(choice);
	switch (choice)
	{
	case 'O':
		cout << "Enter patron ID: ";
		patronID = GetStringInput();
		cout << endl << "Enter book ID: ";
		mediaID = GetStringInput();
		//TODO: add the bookID to the correct patron with patronID (done below) ???? 
		CheckOutItem(patronID, mediaID);
		break;
	case 'I':
		//DO WE WANT TO CHECKIN BOOK WITH PATRON ID OR NOT 
		//cout << "Enter patron ID: ";
		//patronID = GetStringInput();
		cout << "Enter Book ID: " << endl; 
		mediaID = GetStringInput();
		//TODO: Check in book by ID (done below)
		CheckInItem(mediaID);
		break;
	case 'L':
		cout << "All Books: " << endl;
		ListAllItems();
		break;
	case 'D':
		cout << "Overdue Books: " << endl;
		ListAllOverdueItems();
		break;
	case 'P':
		cout << "Enter patron ID: ";
		patronID = GetStringInput();
		//TODO: Get patron by ID (done below)
		ListBooksByPatron(patronID);
		break;
	case 'F':
		cout << "Patrons: " << endl;
		ListPatrons();
		//TODO: List all patrons
		//Nathan says: Do we want this option? Do we want patrons to see who all
		//has access to the library?
		break;
	case 'A':
		AdvanceDate();
		cout << "Date is now:"<< br.DisplayCurrentDate() << endl;
		break;
	case 'B':
		AddLibraryItem();
		break;
	case 'N':
		AddPatron();
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
	try{
		br.CheckOutItem(patronID, itemId);
	}
	catch (runtime_error &e){
		cout << e.what() << endl;
	}
	catch (invalid_argument &e){
		cout << "Enter an integer for patron ID and item ID\n";
	}
}

// The CheckInItem Method
// Purpose: To check in an item
// Parameters: 1 string:  string itemId)
// Returns: None
// Pre-conditions: The item the user wants to check in is valid
// Post-conditions: Item is checked in
// -----------------------------------------------------------------
void CLI::CheckInItem(string itemId)
{
	try{ 
		br.CheckInItem(itemId);
	}
	catch (runtime_error &e){
		cout << e.what() << endl;
	}
	catch (invalid_argument &e){
		cout << "Enter an integer for patron ID and item ID\n";
	}
}

// The ListAllItems Method
// Purpose: To list all items in library
// Parameters: None
// Returns: 1 string
// Pre-conditions: There are items in the library
// Post-conditions: List of items in library are returned
// -----------------------------------------------------------------
void CLI::ListAllItems()
{
	string display = br.ListAllItems();
	cout << display;
}

// The ListAllOverdueItems Method
// Purpose: To list all the items that are overdue
// Parameters: None
// Returns: 1 string
// Pre-conditions: There are items that are overdue
// Post-conditions: List of overdue items are returned
// -----------------------------------------------------------------
void CLI::ListAllOverdueItems()
{
	string display = br.ListAllOverdueItems();
	cout << display;
}

// The ListBooksByPatron Method
// Purpose: To list all the items a patron has checked out
// Parameters: 1 strings (string patronId)
// Returns: 1 string
// Pre-conditions: The patron is valid and has something checked out
// Post-conditions: A list of items the patron has checked out is returned
// -----------------------------------------------------------------
void CLI::ListBooksByPatron(string patronId)
{
	string display;
	try{
		display = br.ListBooksByPatron(patronId);
		cout << display;
	}
	catch (invalid_argument &e){
		cout << "Enter an integer for patron ID \n";
	}
	catch (runtime_error &e){
		cout << e.what();
	}
}

// The AdvanceItemDate Method
// Purpose: To advance the due date of an item
// Parameters: 1 string (string itemId)
// Returns: None
// Pre-conditions: The item is checked out and needs to have an advanced due date
// Post-conditions: The due date of the item is advanced
// -----------------------------------------------------------------
void CLI::AdvanceDate()
{
	br.AdvanceDate();
}

// The AddLibraryItem Method
// Purpose: To check out an item
// Parameters: 2 strings (string patronId, string itemId)
// Returns: None
// Pre-conditions: There is an item that needs to be added to the library
// Post-conditions: Item is added to the library
// -----------------------------------------------------------------
void CLI::AddLibraryItem(){

	string author, title, type;
	int itemType;
	cout << "Author: ";
	getline(cin, author);
	author = Utility::Trim(author);
	cout << "\nTitle: ";
	getline(cin, title);
	title = Utility::Trim(title);
	bool error;
	do{
		error = false;
		cout << "\nItem Type (0-adult, 1-children, 2-DVD, 3-Video tape): ";
		getline(cin, type);
		try {
			itemType = stoi(type);
		}
		catch (invalid_argument &e){
			cout << "\nEnter an integer between 0 and 3";
			error = true;
		}
		if (itemType > 3 || itemType < 0){
			cout << "\nEnter an integer between 0 and 3";
			error = true;
		}
	} while (error);
	br.AddLibraryItem(author, title, MediaTypes(itemType));
}

void CLI::AddPatron(){
	string firstName, lastName, adult;
	bool isAdult;
	cout << "First Name: ";
	getline(cin, firstName);
	firstName = Utility::Trim(firstName);
	cout << "\nLast Name: ";
	getline(cin, lastName);
	lastName = Utility::Trim(lastName);
	bool error;
	do{
		error = false;
		cout << "\nIs new patron an adult (Y/N): ";
		getline(cin, adult);
		adult = Utility::Trim(adult);
		if (toupper(adult[0]) == 'Y')
			isAdult = true;
		else if (toupper(adult[0]) == 'N')
			isAdult = false;
		else{
			error = true;
			cout << "\n Enter Y or N";
		}
	} while (error);
	br.AddPatron(firstName, lastName, isAdult);
}

//open the datafiles
void CLI::OpenFile(string bookFile, string patronFile){
	br.OpenFiles(bookFile, patronFile);
}

void CLI::ListPatrons(){
	cout << br.ListAllPatrons();
} 
