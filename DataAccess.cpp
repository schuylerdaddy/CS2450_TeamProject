#include "DataAccess.h"
#include <stdexcept>

using namespace std;


DataAccess::DataAccess(string bookFile, string patronFile)
{
	//open book file
	bookStream.open(bookFile, ios::in | ios::out | ios::binary);
	if (!bookStream) throw runtime_error("Book list file does not exist");

	bookStream.seekg(0, ios::beg);
	bookStream.read(reinterpret_cast<char*>(&maxBooks), sizeof(int));

	//open patrons file
	patronStream.open(patronFile, ios::in | ios::out | ios::binary);
	if (!patronStream) throw runtime_error("Patron list file does not exist");

	patronStream.seekg(0, ios::beg);
	patronStream.read(reinterpret_cast<char*>(&maxPatrons), sizeof(int));
}

void DataAccess::openBookFile(string bookFile){
	bookStream.open(bookFile, ios::in | ios::out | ios::binary);
	if (!bookStream) throw runtime_error("Book list file does not exist");

	bookStream.seekg(0, ios::beg);
	bookStream.read(reinterpret_cast<char*>(&maxBooks), sizeof(int));
}

void DataAccess::openPatronFile(string patronFile){
	//open patrons file
	patronStream.open(patronFile, ios::in | ios::out | ios::binary);
	if (!patronStream) throw runtime_error("Patron list file does not exist"); 

	patronStream.seekg(0, ios::beg);
	patronStream.read(reinterpret_cast<char*>(&maxPatrons), sizeof(int));
}
Media DataAccess::readBook(int id){
	//check for overflow of ID
	if (id > maxBooks) throw runtime_error("overflow");
	bookStream.seekg(id*BOOK_BLOCKSIZE, ios::beg);
	Media temp = Media::read(bookStream);
	if (!bookStream) throw runtime_error("error reading media information");
	return temp;
}

vector<Media> DataAccess::readBook(){
	vector<Media> mediaList;
	for (int i = 0; i<maxBooks; ++i){
		mediaList.push_back(readBook(i+1));
	}
	return mediaList;
}

void DataAccess::saveBook(Media bookInfo){
	int id = bookInfo.getID();
	if (id > maxBooks) throw runtime_error("overflow, error saving book information");
	bookStream.seekg(id*BOOK_BLOCKSIZE, ios::beg);
	bookInfo.Save(bookStream);
	if (!bookStream) throw runtime_error("error saving book information");
}

void DataAccess::addBook(Media bookInfo){
	maxBooks++;
	bookInfo.AssignId(maxBooks);
	bookStream.seekg(0, ios::beg);
	bookStream.write(reinterpret_cast<char*>(&maxBooks), sizeof(int));
	saveBook(bookInfo);
}

Patron DataAccess::readPatron(int id){
	//check for overflow of ID
	if (id > maxPatrons) throw runtime_error("overflow");
	patronStream.seekg(id*PATRON_BLOCKSIZE, ios::beg);
	Patron temp = Patron::ReadPatron(patronStream);
	if (!patronStream) throw runtime_error("error saving book information");
	return temp;
}

vector<Patron> DataAccess::readPatron(){
	vector<Patron> patronList;
	for (int i = 0; i<maxPatrons; ++i){
		patronList.push_back(readPatron(i+1));
	}
	return patronList;
}
void DataAccess::savePatron(Patron patronInfo){
	
	int id = patronInfo.getID();
//	if (id > maxPatrons) throw runtime_error("overflow, error saving patron information");
	patronStream.seekg(id*PATRON_BLOCKSIZE, ios::beg);
	patronInfo.SavePatron(patronStream);
	if (!patronStream) 
		throw runtime_error("error saving patron information");
}

void DataAccess::addPatron(Patron patronInfo){
	maxPatrons++;
	patronInfo.AssignPatronId(maxPatrons);
	patronStream.seekg(0, ios::beg);
	patronStream.write(reinterpret_cast<char*>(&maxPatrons), sizeof(int));
	savePatron(patronInfo);
}

int DataAccess::getBorrower(int bookID){
	int pID = 0;
	for (int i = 1; i <= maxPatrons; ++i){
		Patron user = readPatron(i);
		vector<int> bookList = user.GetBookList();
		for (int i = 0; i < bookList.size(); ++i){
			if (bookID == bookList[i]){
				pID = i;
				break;
			}
		}
		if (pID != 0) break;
	}
	return pID;
}
