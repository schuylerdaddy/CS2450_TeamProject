#include "Utility.h"


bool isWhiteSpace(char c)
{
	return c == '\t' || c == '\r' || c == '\n' || c == '|' || c == ' '  || c =='\0';
}

string Trimfront(string s)
{
	int i = 0;
	for (; i < s.length() && isWhiteSpace(s[i]); ++i);
	return s.substr(i);

}

string Trimback(string s)
{
	int i = s.length();
	bool wSpaceFound = false;
	for (; i >= 0 && isWhiteSpace(s[i]); --i)
		if (isWhiteSpace(s[i]))
			wSpaceFound = true;
	return wSpaceFound ? s.substr(0, i + 1) : s.substr(0, i);
}

bool Utility::IsInt(string s)
{
	return regex_match(s, regex("^-?[0-9]+$"));
}

bool Utility::IsNum(string s)
{
	return (regex_match(s, regex("^-?[0-9]+(\\.[0-9]+){0,1}$")));
}

bool Utility::IsPosNum(string s)
{
	return regex_match(s, regex("^[0-9]+(\\.[0-9]+){0,1}$"));
}

string Utility::Trim(string s)
{
	s = Trimfront(s);
	s = Trimback(s);
	return s;
}
