#include<fstream>
#include<string>
#include "CLI.h"
#include<iostream>

using namespace std;
int main(){
	string bookFile, patronFile;
	bool done = false;
	CLI Library;
	Utility::LoadDaysByItemType();
	cout << "Enter the file name containing library items: ";
	getline(cin, bookFile);
	cout << "Enter the file name containing library patrons:";
	getline(cin, patronFile);
	Library.OpenFile("bookfile.db", "patronsfile.db");
	while (!done){
		Library.MenuOptions();
		bool error;
		char input;
		do{
			error = false;
			try{
				input = Library.GetCharInput();
			}
			catch (runtime_error &e){
				error = true;
				cout << e.what() << endl;
				cout << "Enter choice: ";
			}
		} while (error);
		if (toupper(input) == 'Q')
			done = true;
		else{
			Library.RunUserCommand(input);
		}
	}
}
	
/*
	cout << "patrons\n";
	cout<<Library.ListAllPatrons();
	//Library.AddLibraryItem("J.K Rowling", "Harry Potter and the Chamber of Secrets", MediaTypes(1));
	
	
	//Library.CheckOutItem("3", "10");
	cout<<Library.ListBooksByPatron("3");
	cout << "book to return:";
	string book;
	//getline(cin, book);
	//Library.CheckInItem("3", book);
	//Library.CheckOutItem("3", "11");
	cout << "books\n";
	cout<<Library.ListAllItems();
	Library.AdvanceDate();
	cout << "overdue\n";
	cout<<Library.ListAllOverdueItems();
	cout << "patron\n";
	cout<<Library.ListBooksByPatron("3");

/*	DataAccess is;

	try{

		is.openBookFile("bookfile.db");
		is.openPatronFile("patronsfile.db");
	}
	
	catch (runtime_error &e){
		cout << e.what() << endl;
		//create files
		fstream newbookfile("bookfile.db", ios::in | ios::out | ios::binary | ios::trunc);
		fstream newpatronfile("patronsfile.db", ios::in | ios::out | ios::binary | ios::trunc);
		int max = 0;
		newbookfile.write(reinterpret_cast<char*>(&max), sizeof(int));
		newpatronfile.write(reinterpret_cast<char*>(&max), sizeof(int));
		exit(1);
	} 
	Media book1("smith", "stars", MediaTypes(1));
	//book1.AssignId(1);
	is.addBook(book1);
	Media book2 = is.readBook(1);
	Patron user1("john", "green", true);
	//user1.AssignPatronId(1);
	try{
		is.addPatron(user1);
	}
	catch (runtime_error &e){
		cout << e.what() << endl;
	}
	try{
		Patron user2 = is.readPatron(1);
	}
	catch (runtime_error &e){
		cout << e.what() << endl;
	}

	Date date1(1, 3, 2014);
	date1 += 2;
	Date date2;
	date2 = date1 + 30;

	if (date2 > date1) cout << "overdue";
	else
		cout << "error";*/


