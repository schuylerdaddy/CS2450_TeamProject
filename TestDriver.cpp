#include "Utility.h"
#include <stdexcept>
#include <iostream>

int main()
{
	RunUtilityTests();
	return 0;
}
void RunDataAccessTests(){
	//expected failure
	DataAccess data;
	try {
		data.openBookFile("book");
	}
	catch (runtime_error &e)
	{
		string temp = e.what();
		if (temp != "Book list file does not exist")
			throw runtime_error("failure: opens file that does not exist");
		else cout << "success\n";
	}

	try {
		data.openPatronFile("patron");
	}
	catch (runtime_error &e){
		string temp = e.what();
		if (temp != "Patron list file does not exist")
			throw runtime_error("failure: opens file that does not exist");
		else cout << "success\n";
	}
	try {
		data.readBook(10);
	}
	catch (runtime_error &e){
		string temp = e.what();
		if (temp != "Book does not exist" && temp != "error reading media information")
			throw runtime_error("failure: read book that does not exist");
		else cout << "success\n";
	}
	Media book("Victor Hugo", "Les Miserables", MediaTypes(0));
	try{
		data.addBook(book);
	}
	catch (runtime_error &e){
		string temp = e.what();
		if (temp != "overflow, error saving book information" && temp != "error saving book information")
			throw runtime_error("failure: saving book in non existant file");
		else
			cout << "success\n";
	}
	DataAccess library;
	//should work
	library.openBookFile("bookfile.bin");
	if (!library.mediaIsOpen())
		throw runtime_error("File not opened correctly");

	library.openPatronFile("patronfile.bin");
	if (!library.patronIsOpen())
		throw runtime_error("File not opened correctly");

	Media book1("Victor Hugo", "Les Miserables", MediaTypes(0));
	library.addBook(book1);
	int id = book1.getID();
	Media testBook = library.readBook(id);
	if (testBook.GetAuthor() != "Victor Hugo" || testBook.GetTitle() != "Les Miserables")
		throw runtime_error("error retrieving or saving record");

	Patron patron1("John", "Smith", true);
	library.addPatron(patron1);
	int pId = patron1.getID();
	Patron testPatron = library.readPatron(pId);
	string displayPatron1 = patron1.displayPatronInfo();
	string displayTestPatron = testPatron.displayPatronInfo();
	if (displayPatron1 != displayTestPatron)
		throw runtime_error("error retrieving or saving patron");
}

void RunCTOTests(){
	//invalid date
	try {
		Date testDate(0, 0, 0);
	}
	catch (runtime_error &e){
		string temp = e.what();
		if (temp != "invalid date")
			throw runtime_error("failure: invalid date accepted");
		else
			cout << "Date Success\n";
	}
	try{
		Date testDate(13, 0, 0);
	}
	catch (runtime_error &e){
		string temp = e.what();
		if (temp != "invalid date")
			throw runtime_error("failure: invalid date accepted");
		else
			cout << "Date Success\n";
	}
	try{
		Date testDate(1, 32, 1);
	}
	catch (runtime_error &e){
		string temp = e.what();
		if (temp != "invalid date")
			throw runtime_error("failure: invalid date accepted");
		else
			cout << "Date Success\n";
	}
	
	//expected success
	Date date1(1, 1, 2014);
	date1 += 1;
	if (date1.GetDay() != 2 || date1.GetMonth() != 1 || date1.GetYear() != 2014)
		throw runtime_error("Failure: incorrect addition");
	Date date2(1, 31, 2014);
	date2 += 2;
	if (date2.GetDay() != 2 || date2.GetMonth() != 2 || date2.GetYear() != 2014)
		throw runtime_error("Failure: incorrect addition");
	Date date3(12, 31, 2014);
	date3 += 1;
	if (date3.GetDay() != 1 || date3.GetMonth() != 1 || date3.GetYear() != 2015)
		throw runtime_error("Failure: incorrect addition");
	if (date2 > date3)
		throw runtime_error("failure: incorrect comparison");



}
void RunUtilityTests()
	{
		//confirm expected failures
		if (Utility::IsInt("3ad2g4"))
			throw runtime_error("Alphas accepted in IsInt");
		if (Utility::IsNum("6f134"))
			throw runtime_error("Alphas accepted in IsInt");
		if (Utility::IsInt("5.456"))
			throw runtime_error("Accepted decimal in IsInt");
		if (Utility::IsPosNum("-54"))
			throw runtime_error("Accepted Negative number in IsPosNum");
		if (Utility::IsNum(" 567.4"))
			throw runtime_error("accepted leading white space");
		if (Utility::IsNum(" 567.4 "))
			throw runtime_error("accepted trailing white space");
		if (Utility::IsInt("89!") || (Utility::IsInt("%432") || (Utility::IsInt("89$32"))))
			throw runtime_error("accepted non numeric symbols");
		if (Utility::IsNum(".4"))
			throw runtime_error("accepted decimal with no leading number(need at least 1 even if 0)");
		if (Utility::IsNum("789."))
			throw runtime_error("accepted decimal with no trailing numbers");

		//assert expected working functionality
		if (!Utility::IsInt("897"))
			throw runtime_error("897 is int");
		if (!Utility::IsInt("-897"))
			throw runtime_error("-897 is int");
		if (!Utility::IsNum("897"))
			throw runtime_error("897 is number");
		if (!Utility::IsNum("-897"))
			throw runtime_error("-897 is number");
		if (!Utility::IsPosNum("897"))
			throw runtime_error("897 is positive number");
		if (!Utility::IsNum("40.26"))
			throw runtime_error("40.26 is number");
		if (!Utility::IsNum("-40.26"))
			throw runtime_error("-40.26 is number");
		if (!Utility::IsPosNum("40.26"))
			throw runtime_error("40.26 is positive number");

		try
		{
			string s = Utility::Trim("");
		}
		catch (exception e)
		{
			throw runtime_error("should except an empty string");
		}

		if (Utility::Trim(" Bob Barker	\t") != "Bob Barker")
			throw runtime_error("didn't trim white space");
	}
