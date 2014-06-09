//all members and methods should be static
#ifndef SE_UT
#define SE_UT

#include <regex>
#include <string>

using namespace std;

class Utility
{
public:
	//functions to correlate with user in input
	static bool IsInt(string s);   //determines if string parses to an int
	static bool IsNum(string s);   //determines if string represents number
	static bool IsPosNum(string s); //determines if string is positive number
	static string Trim(string s); //returns value of string with all leading and trailing white space eliminated
};

void RunUtilityTests(void);
#endif
