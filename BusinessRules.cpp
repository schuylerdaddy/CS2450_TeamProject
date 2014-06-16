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
	int pID=stoi(patronID);
	int iID = stoi(itemID);
	Media item;
	Patron user = library.readPatron(pID);
	if (user.canBorrow()){
		 item = library.readBook(iID);
		if (item.GetCheckedInStatus()){
			user.checkoutBook(iID);
			Date date = CalculateDueDate(item, today);
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

void BusinessRules::CheckInItem(string patronID, string itemID){
	int pID = stoi(patronID);
	int iID = stoi(itemID);
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

void BusinessRules::ListAllItems(){
	vector<Media> allItems = library.readBook();
	for (int i = 0; i < allItems.size(); ++i){
		allItems[i].display();
	}
}

void BusinessRules::ListAllPatrons(){
	vector<Patron> allItems = library.readPatron();
	for (int i = 0; i < allItems.size(); ++i){
		allItems[i].displayPatronInfo();
	}
}

void BusinessRules::ListAllOverdueItems(){
	vector<Media> allItems = library.readBook();
	for (int i = 0; i < allItems.size(); ++i){
		if (allItems[i].isOverdue(today)){
			allItems[i].display();
		}
	}
}

void BusinessRules::ListBooksByPatron(string PatronID){
	int pID = stoi(PatronID);
	Patron user = library.readPatron(pID);
	user.displayPatronInfo();
	vector<int> bookList = user.GetBookList();
	cout << "Books checked out: \n";
	for (int i = 0; i < bookList.size(); ++i){
		Media item = library.readBook(bookList[i]);
		item.display();
	}
}


Date BusinessRules::CalculateDueDate(Media item, Date today){
	return today + item.getLoanTime();
}
Date BusinessRules::AdvanceDate(){
	return today += 1;
}

void BusinessRules::AddLibraryItem(	string author, string title, MediaTypes type){
	Media item(author, title, type);
	library.addBook(item);
}

void BusinessRules::AddPatron(string first, string last, bool adult){
	Patron user(first, last, adult);
	library.addPatron(user);
}
