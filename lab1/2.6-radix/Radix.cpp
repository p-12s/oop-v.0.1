#include "stdafx.h"
#include "Radix.h"

using namespace std;

int MultiplyWithOverflowCheck(unsigned const int mult1, unsigned const int mult2)
{
	if (mult2 != 0 && mult1 > INT_MAX / mult2)
		throw overflow_error("Overflow on calculating value!");

	return mult1 * mult2;
}

int AddWithOverflowCheck(unsigned const int add1, unsigned const int add2)
{
	if (add1 > INT_MAX - add2)
		throw overflow_error("Overflow on calculating value!");

	return add1 + add2;
}

int StringToInt(string& input, const int radix, bool& wasError)
{
	const int DECIMAL_RADIX = 10;
	int result = 0;
	if (radix == DECIMAL_RADIX)
	{
		result = stoi(input);
	}
	else
	{
		const size_t valueLength = input.length();
		const bool isNegative = (input[0] == '-');

		int startPos = (isNegative) ? 1 : (input[0] == '+') ? 1 : 0;
		result = static_cast<int>(constants::PERMISSIBLE_CHARS.find(input[startPos]));

		for (size_t i = startPos + 1; i < valueLength; i++)
		{
			result = MultiplyWithOverflowCheck(result, radix);
			result = AddWithOverflowCheck(result, 
				static_cast<int>(constants::PERMISSIBLE_CHARS.find(input[i])));
		}

		if (isNegative)
			result *= -1;
	}
	return result;
}

bool IsNotationInAllowableRange(const unsigned notation)
{
	return (notation >= constants::MIN_RADIX && notation <= constants::MAX_RADIX);
};

bool IsCharsInAllowableRange(const char ch, const unsigned radix, const char majorSymbol)
{
	if (radix < constants::START_NUMBER_SYSTEM_WITH_LETTERS)
		return (ch >= '0' && ch <= majorSymbol);
	else
		return ((ch >= '0' && ch <= '9') || (toupper(ch) >= 'A' && toupper(ch) <= toupper(majorSymbol)));
};

void CheckStringForValidateWithRadix(const string& valueStr, const unsigned radix)
{
	string checkedStr = valueStr;
	if (checkedStr[0] == '-' || checkedStr[0] == '+')
		checkedStr = checkedStr.substr(1);

	char majorValidSymbol = constants::PERMISSIBLE_CHARS[radix - 1];

	for (auto& ch : checkedStr)
	{
		if (!IsCharsInAllowableRange(ch, radix, majorValidSymbol))
		{
			throw invalid_argument("Characters in the string are not allowed for this number system\n");
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
		throw invalid_argument("Arguments <source notation> <destination notation> <value> must be a numbers\n");
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
		throw runtime_error("Error in casting characters to uppercase\n");
	}
}

string IntToString(const int decimalValue, const unsigned radix)
{
	const int DECIMAL_RADIX = 10;
	if (radix == DECIMAL_RADIX)
		return to_string(decimalValue);
	
	string result;
	int balance = abs(decimalValue);
	while (balance >= radix)
	{
		result.push_back(constants::PERMISSIBLE_CHARS[balance % radix]);
		balance /= radix;
	}
	result.push_back(constants::PERMISSIBLE_CHARS[balance]);
	if (decimalValue < 0)
	{
		result.push_back('-');
	}

	return { result.rbegin(), result.rend() };
}

void ParametersInitialization(char* argv[], int& sourceNotation, int& destinationNotation, string& valueStr)
{
	sourceNotation = ReadNumberFromString(argv[1]);
	destinationNotation = ReadNumberFromString(argv[2]);

	if (!IsNotationInAllowableRange(sourceNotation) ||
		!IsNotationInAllowableRange(destinationNotation))
	{
		throw runtime_error("The base of the number systems should be in the range [2, 36]\n");
	}

	valueStr = argv[3];
	if (valueStr.length() == 0)
		throw runtime_error("Value not passed\n");

	CheckStringForValidateWithRadix(valueStr, sourceNotation);
	CastCharsToUpperCase(valueStr);
}

string TryChangingRadix(const int sourceNotation, const int destinationNotation, string& valueStr)
{
	bool wasError = false;
	int decimalNumber = StringToInt(valueStr, sourceNotation, wasError);
	if (wasError)
		throw runtime_error("There was an overflow of a number of type int\n");

	return IntToString(decimalNumber, destinationNotation);
}