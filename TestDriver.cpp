#include "Utility.h"
#include <stdexcept>
#include <iostream>

int main()
{
	RunUtilityTests();
	return 0;
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
