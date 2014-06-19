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
	Date CalculateDueDate(Media);
	//Date CalculateToday();
public:
	BusinessRules();
	void CheckOutItem(string patronId, string itemId);
	void CheckInItem(string patronId, string itemId);
	string ListAllItems();
	string ListAllOverdueItems();
	string ListBooksByPatron(string patronId);
	string ListAllPatrons();
	void AdvanceItemDate(string itemId);//????
	void AddLibraryItem(string author, string title, MediaTypes itemType);
	void AdvanceDate();
	void OpenFiles(string, string);
	void AddPatron(string, string, bool);
	string DisplayCurrentDate();
	
};

