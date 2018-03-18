#include "stdafx.h"

using namespace std;

namespace constants
{
const string PERMISSIBLE_CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const unsigned MIN_RADIX = 2;
const unsigned MAX_RADIX = 36;
const unsigned START_NUMBER_SYSTEM_WITH_LETTERS = 11;
}
/*
string GetCharViewOfDigitByPosition(const unsigned pos)
{
	string numeral = constants::PERMISSIBLE_CHARS[pos];
}*/

int StringToInt(string input, const int radix, bool& wasError)
{
	long long result = 0;
	if (input.empty() || input == "-" || input == "+")
	{
		wasError = true;
		return static_cast<int>(result);
	}

	int signOfNumber = (input[0] == '-') ? -1 : 1;
	input = (input[0] == '-' || input[0] == '+') ? input.substr(1) : input;

	int charPos = 0;
	long long increment = 0;

	for (int i = input.length() - 1; i >= 0; i--)
	{
		int numeral = constants::PERMISSIBLE_CHARS.find(input[charPos]);

		if (numeral != std::string::npos)
		{
			increment = static_cast<long long>(signOfNumber * numeral * pow(radix, i));
			if (increment < INT_MIN || increment > INT_MAX)
			{
				wasError = true;
				break;
			}

			result += increment;
			if (result < INT_MIN || result > INT_MAX)
			{
				wasError = true;
				break;
			}
		}
		else
		{
			wasError = true;
			break;
		}
		charPos++;
	}
	return static_cast<int>(result);
}

bool IsNotationInAllowableRange(const unsigned a)
{
	return (a >= constants::MIN_RADIX && a <= constants::MAX_RADIX);
};

bool IsCharsInAllowableRange(const char ch, const unsigned radix, const char majorSymbol)
{
	if (radix < constants::START_NUMBER_SYSTEM_WITH_LETTERS)
		return (ch >= '0' && ch <= majorSymbol);
	else
		return ((ch >= '0' && ch <= '9') || (toupper(ch) >= 'A' && toupper(ch) <= toupper(majorSymbol)));
};

void CheckStringForValidateWithRadix(string valueStr, const unsigned radix)
{
	if (valueStr[0] == '-' || valueStr[0] == '+')
		valueStr = valueStr.substr(1);

	char majorValidSymbol = constants::PERMISSIBLE_CHARS[radix - 1];

	for (auto& ch : valueStr)
	{
		if (!IsCharsInAllowableRange(ch, radix, majorValidSymbol))
		{
			throw invalid_argument("Characters in the string are not allowed for this number system");
		}
	}
}

int ReadNumberFromString(const string& notation)
{
	int number = 0;
	try
	{
		number = stoi(notation);
	}
	catch (exception const&)
	{
		throw invalid_argument("Arguments <source notation> <destination notation> <value> must be a numbers!");
	}
	return number;
}

void CastCharsToUpperCase(string& valueStr)
{
	try
	{
		for (auto& ch : valueStr) ch = toupper(ch);
	}
	catch (exception const&)
	{
		throw runtime_error("Error in casting characters to uppercase");
	}
}

// подумать над названием
void Divide(long long n, int radix, string& result, bool& wasError)
{
	if (radix != 0)
	{
		if (n >= radix)
			Divide((n / radix), radix, result, wasError);
		result += constants::PERMISSIBLE_CHARS[n % radix];
	}	
}

string IntToString(long long n, int radix, bool& wasError)
{
	string result = "";

	int signOfNumber = (n < 0) ? -1 : 1;
	n *= signOfNumber;

	Divide(n, radix, result, wasError);

	return (signOfNumber < 0) ? "-" + result : result;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	if (any_of(&argv[1], &argv[4], [](char* arg) {
			return strlen(arg) == 0;
		}))
	{
		cout << "Arguments <source notation> <destination notation> <value> must be non empty!\n";
		return 1;
	}
		/*
		cout << "INT_MAX: " << INT_MAX << endl;
		cout << "LONG_MAX: " << LONG_MAX << endl;
		cout << "LLONG_MAX: " << LLONG_MAX<< endl;
		cout << "LLONG_MIN: " << LLONG_MIN<< endl;
		cout << "INT_MIN: " << INT_MIN << endl << endl;

		INT_MAX: 2147483647
		LONG_MAX: 2147483647
		LLONG_MAX: 9223372036854775807
		LLONG_MIN: -9223372036854775808
		INT_MIN: -2147483648		
		*/

	try
	{
		int sourceNotation = ReadNumberFromString(argv[1]);
		int destinationNotation = ReadNumberFromString(argv[2]);

		if (!IsNotationInAllowableRange(sourceNotation) || !IsNotationInAllowableRange(destinationNotation))
		{
			throw runtime_error("The base of the number systems should be in the range [2, 36]");
		}

		bool wasError = false;
		string valueStr = argv[3];

		CheckStringForValidateWithRadix(valueStr, sourceNotation);

		CastCharsToUpperCase(valueStr);

		long long result = StringToInt(valueStr, sourceNotation, wasError);
		if (wasError)
			throw underflow_error("There was an overflow of a number of type int");
		else
		{
			// магическое число

			string res = IntToString(result, destinationNotation, wasError);
			
			cout << res << endl;
		}
			

	}
	catch (const exception& error)
	{
		cout << error.what() << endl;
		return 1;
	}



	return 0;
}