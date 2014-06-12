//all members and methods should be static
#ifndef SE_UT
#define SE_UT

#include <regex>
#include <string>
#include <map>

using namespace std;

enum MediaTypes{AdultBook,ChildBook,DVD,VideoTape};
    

class Utility
{
private:
    Utility();
public:
	//functions to correlate with user in input
	static bool IsInt(string s);   //determines if string parses to an int
	static bool IsNum(string s);   //determines if string represents number
	static bool IsPosNum(string s); //determines if string is positive number
	static string Trim(string s); //returns value of string with all leading and trailing white space
    static map <MediaTypes,int> DaysByItemType;
    void LoadDaysByItemType();
};

void RunUtilityTests(void);
#endif
