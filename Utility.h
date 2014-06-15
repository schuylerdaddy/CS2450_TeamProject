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
    	static void LoadDaysByItemType();
    	static string GetCurrentDate();  //returns current date as "mm-dd-yyyy"
	static bool IsLeapYear(int year);  //give a year and will return if is leap year or not
	static map<int, int> GetDayCountbyMonth();  //gives amount of days to month, asssume non leap year
	static map<int, int> GetDayCountbyMonth(int year);  //determines if year is leap year and returns a map for days by month number
};

void RunUtilityTests(void);
#endif
