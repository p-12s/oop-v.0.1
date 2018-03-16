#include "stdafx.h"

using namespace std;

namespace constants
{
	const string PERMISSIBLE_CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const unsigned MIN_RADIX = 2;
	const unsigned MAX_RADIX = 36;
	const unsigned START_NUMBER_SYSTEM_WITH_LETTERS = 11;
}

int StringToInt(const string& input, const int radix, bool& wasError)
{
	int result = 0;


	cout << input.length() << endl;

	// а если пустая строка?
	int charPos = 0;
	size_t inputLen = input.length();

	for (int i = 10; i >= 0; i--)
	{
		cout << i << endl;
	}

	
	return result;
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

	for (auto &ch : valueStr)
		if (!IsCharsInAllowableRange(ch, radix, majorValidSymbol))
			throw invalid_argument("Characters in the string are not allowed for this number system");
}

int ReadNumberFromString(const string& notation)
{
	int  number = 0;
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

	try
	{
		int sourceNotation = ReadNumberFromString(argv[1]);
		int destinationNotation = ReadNumberFromString(argv[2]);

		if (!IsNotationInAllowableRange(sourceNotation) || 
			!IsNotationInAllowableRange(destinationNotation))
		{
			throw runtime_error("The base of the number systems should be in the range [2, 36]");
		}

		bool wasError = false;
		string valueStr = argv[3];		

		CheckStringForValidateWithRadix(valueStr, sourceNotation);

		// попробовать перевести в систему счисления		
		if (destinationNotation == sourceNotation)
		{
			cout << valueStr << endl;
		}
		else
		{
			cout << valueStr << " in " << sourceNotation << " to 10th";
			
			int result = StringToInt(valueStr, sourceNotation, wasError);
			if (wasError)
				return 1;
			else
				cout << result << endl;
			
		}		
	}
	catch (const exception& error)
	{
		cout << error.what() << endl;
		return 1;
	}

    return 0;
}

