#pragma once
#include "DataAccess.h"
#include "Utility.h"
#include<string>
using std::string;

class BusinessRules
{
private:
	static DataAccess library;
	static Date today;
	//calculate due date for item being checked out
	//parameter: Media object to be checked out
	//returns: due date
	Date CalculateDueDate(Media); 
	
	int getBorrower(int);

public:
	BusinessRules();
	//Checks out an item
	//parameters: patronID and itemId as strings
	//returns: nothing
	//post-conditions: item and patron have been updated in the files
	void CheckOutItem(string patronId, string itemId);
	
	//Checks in an item
	//parameters: patronID and itemId as strings
	//returns: nothing
	//post-conditions: item and patron have been updated in the files
	void CheckInItem(string itemId);
	
	//List all items/books
	//parameters: none
	//returns: string containing all the info to be displayed
	string ListAllItems();
	
	//List all items/books that are overdue as of today's date
	//parameters: none
	//returns: string containing all the info to be displayed
	string ListAllOverdueItems();
	
	//List all items/books borrowed by a patron
	//parameters: patron id as a string
	//returns: string containing all the info to be displayed
	string ListBooksByPatron(string patronId);
	
	//list all patrons (for debugging, not needed in the final product)
	//parameters: none
	//returns: string containing all the info to be displayed
	string ListAllPatrons();
	
	//not sure what this is for???
	void AdvanceItemDate(string itemId);//????
	
	//add items to library
	//parameters: author and title as string, mediaTypes to specify type of the item (children, adult, dvd, tape)
	//return: nothing
	//post-condition: item saves to file
	void AddLibraryItem(string author, string title, MediaTypes itemType);
	
	//advances today's date
	//parameter: none
	//return: none
	void AdvanceDate();
	
	//open the files, need to be used right at the start of the program
	//parameters: book file name and patron file name
	//returns: nothing
	void OpenFiles(string, string);
	
	//add new patron
	//parmeter: first name, last name, bool: true for adult, false for children
	void AddPatron(string, string, bool);
	
	//display the current date
	string DisplayCurrentDate();
	

	
};




