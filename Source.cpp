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
	try{
		Library.OpenFile(bookFile, patronFile);
	}
	catch (runtime_error &e){
		cout << e.what() << endl;
		cout << "Closing program";
		cin.get();
		exit(1);
	}
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
	
