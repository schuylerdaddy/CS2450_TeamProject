#pragma once
#include"DTO.h"
#include <fstream>
#include <string>
#include<vector>

const int BOOK_BLOCKSIZE = 512;
const int PATRON_BLOCKSIZE = 512;
class DataAccess
{
private: 
	 std::fstream patronStream;
	 std::fstream bookStream;
	 int maxBooks;
	 int maxPatrons;

public:	
	DataAccess(){};
	DataAccess(std::string, std::string);
	void openBookFile(std::string);
	void openPatronFile(std::string);
	void closePatronFile();
	Media readBook(int);
	vector<Media> readBook();
	void saveBook(Media);
	void addBook(Media bookInfo);
	Patron readPatron(int);
	vector<Patron> readPatron();
	void savePatron(Patron);
	void addPatron(Patron);
};
