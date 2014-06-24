#pragma once
#include "BusinessRules.h"
#include <vector>

using namespace std;

// This class models a Command Line Interface. It contains key information
// in order to implement an interactive interface for the user
class CLI
{
public:
	CLI();
	~CLI();
	int GetIntegerInput();
	char GetCharInput();
	string GetStringInput();
	void MenuOptions();
	void RunUserCommand(char);
	void CheckOutItem(string, string);
	void CheckInItem(string);
	void ListAllItems();
	void ListAllOverdueItems();
	void ListBooksByPatron(string);
	void ListPatrons();
	void AdvanceDate();
	void AddLibraryItem(); 
	void AddPatron();
	void OpenFile(string, string); //OpenFile(bookfile, patronfile)
private:
	static BusinessRules br;
	int integerInput;
	char charInput;
	string stringInput;
	Date date;
	string patronID; 
	string mediaID; 
};

