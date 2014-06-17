#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "Utility.h"

map<MediaTypes, int> Utility::DaysByItemType = map<MediaTypes, int>();

Utility::Utility()
{
	LoadDaysByItemType();
}

void Utility::LoadDaysByItemType()
{
	DaysByItemType[AdultBook] = 14;
	DaysByItemType[ChildBook] = 7;
	DaysByItemType[DVD] = 2;
	DaysByItemType[VideoTape] = 3;
}

bool isWhiteSpace(char c)
{
	return c == '\t' || c == '\r' || c == '\n' || c == '|' || c == ' ' || c == '\0';
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

string Utility::GetCurrentDate()
{

	time_t t = time(0);   // get time now
	struct tm *now = nullptr;
	now = localtime( &t);

	return to_string(now->tm_mon + 1) + '-' + to_string(now->tm_mday) + '-' + to_string(now->tm_year + 1900);
}

bool Utility::IsLeapYear(int year)
{
	if (year % 4 != 0) return false;
	else if (year % 100 != 0) return true;
	else if (year % 400) return false;
	else return true;
}

map<int, int> Utility::GetDayCountbyMonth()
{
	map<int, int> m;
	m[1] = 31;
	m[3] = 30;
	m[4] = 30;
	m[5] = 31;
	m[6] = 30;
	m[7] = 31;
	m[8] = 31;
	m[9] = 30;
	m[10] = 31;
	m[11] = 30;
	m[12] = 31;
	m[2] = 28;

	return m;
}

map<int, int> Utility::GetDayCountbyMonth(int year)
{
	map<int, int> m;
	m[1] = 31;
	m[3] = 30;
	m[4] = 30;
	m[5] = 31;
	m[6] = 30;
	m[7] = 31;
	m[8] = 31;
	m[9] = 30;
	m[10] = 31;
	m[11] = 30;
	m[12] = 31;
	if (IsLeapYear(year))
		m[2] = 29;
	else
		m[2] = 28;

	return m;
}
