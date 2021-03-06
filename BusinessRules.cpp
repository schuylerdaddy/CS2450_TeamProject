#include "BusinessRules.h"
#include <iostream>
using namespace std;

DataAccess BusinessRules::library;
Date BusinessRules::today;

BusinessRules::BusinessRules()
{
}

void BusinessRules::OpenFiles(string book, string patron){
	library.openBookFile(book);
	library.openPatronFile(patron);
}

void BusinessRules::CheckOutItem(string patronID, string itemID){
	int pID=stoi(patronID); //note invalid_argument exception needs to be caught if no conversion could be performed.
	int iID = stoi(itemID);
	Media item;
	Patron user = library.readPatron(pID);
	if (user.canBorrow()){
		item = library.readBook(iID);
		if (!user.isAdult()){
			if (!item.isChildrenBook())
				throw runtime_error("Children can only borrow children books");
		}
		
		if (item.GetCheckedInStatus()){
			user.checkoutBook(iID);
			Date date = CalculateDueDate(item);
			item.CheckOut(date);
		}
		else
			throw runtime_error("Book already checked out");
	}
	else{
		throw runtime_error("User reached borrowing limit");
	}
	library.saveBook(item);
	library.savePatron(user);
}

void BusinessRules::CheckInItem(string itemID){
	int pID;
	int iID = stoi(itemID);
		
	pID = getBorrower(iID);
	if (pID == 0) throw runtime_error("No record of borrower");
	Patron user = library.readPatron(pID);
	Media item = library.readBook(iID);

	if (item.GetCheckedInStatus())
		throw runtime_error("Book already checked in");
	else{
		user.checkinBook(iID);
		item.CheckIn();
	}
	library.saveBook(item);
	library.savePatron(user);
}

string BusinessRules::ListAllItems(){
	string display;
	vector<Media> allItems = library.readBook();
	for (int i = 0; i < allItems.size(); ++i){
		display+=allItems[i].display();
	}
	return display;
}

string BusinessRules::ListAllPatrons(){
	string display;
	vector<Patron> allItems = library.readPatron();
	for (int i = 0; i < allItems.size(); ++i){
		display+=allItems[i].displayPatronInfo();
	}
	return display;
}

string BusinessRules::ListAllOverdueItems(){
	string display;
	vector<Media> allItems = library.readBook();
	for (int i = 0; i < allItems.size(); ++i){
		if (allItems[i].isOverdue(today)){
			display+=allItems[i].display();
		}
	}
	return display;
}

string BusinessRules::ListBooksByPatron(string PatronID){
	string display;
	int pID = stoi(PatronID);
	Patron user = library.readPatron(pID);
	display+=user.displayPatronInfo();
	vector<int> bookList = user.GetBookList();
	cout << "Books checked out: \n";
	for (int i = 0; i < bookList.size(); ++i){
		Media item = library.readBook(bookList[i]);
		display+=item.display();
	}
	return display;
}


Date BusinessRules::CalculateDueDate(Media item){
	return today + item.getLoanTime();
}
void BusinessRules::AdvanceDate(){
	today += 1;
}

void BusinessRules::AddLibraryItem(	string author, string title, MediaTypes type){
	Media item(author, title, type);
	library.addBook(item);
}

void BusinessRules::AddPatron(string first, string last, bool adult){
	Patron user(first, last, adult);
	library.addPatron(user);
}

string BusinessRules::DisplayCurrentDate(){
	return today.display();
}

int BusinessRules::getBorrower(int bookID){
	int pID = 0;
	int totalPatrons = library.getTotalPatrons();
	for (int i = 1; i <= totalPatrons; ++i){
		Patron user = library.readPatron(i);
		vector<int> bookList = user.GetBookList();
		for (int j = 0; j < bookList.size(); ++j){
			if (bookID == bookList[j]){
				pID = i;
				break;
			}
		}
		if (pID != 0) break;
	}
	return pID;
}
