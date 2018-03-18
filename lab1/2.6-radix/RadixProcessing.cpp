#include "stdafx.h"
#include "RadixProcessing.h"

using namespace std;

int StringToInt(string input, const int radix, bool& wasError)
{
	long long result = 0;	// long long для того, чтобы сравнивать с INT_MIN, INT_MAX
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

void DivisionOfNumberWithRemainder(const long long n, const int radix, string& result, bool& wasError)
{
	try
	{
		if (n >= radix)
			DivisionOfNumberWithRemainder((n / radix), radix, result, wasError);
		result += constants::PERMISSIBLE_CHARS[n % radix];
	}
	catch (exception const&)
	{
		wasError = true;
	}
}

string IntToString(long long n, int radix, bool& wasError)
{
	string result = "";

	int signOfNumber = (n < 0) ? -1 : 1;
	n *= signOfNumber;

	DivisionOfNumberWithRemainder(n, radix, result, wasError);

	return (signOfNumber < 0) ? "-" + result : result;
}

void CheckValidityOfParameters(char* argv[], int& sourceNotation, int& destinationNotation, string& valueStr)
{
	sourceNotation = ReadNumberFromString(argv[1]);
	destinationNotation = ReadNumberFromString(argv[2]);

	if (!IsNotationInAllowableRange(sourceNotation) ||
		!IsNotationInAllowableRange(destinationNotation))
	{
		throw runtime_error("The base of the number systems should be in the range [2, 36]\n");
	}

	valueStr = argv[3];
	CheckStringForValidateWithRadix(valueStr, sourceNotation);
	CastCharsToUpperCase(valueStr);
}

string TryChangingRadix(const int sourceNotation, const int destinationNotation, string& valueStr, bool& wasError)
{
	long long decimalNumber = StringToInt(valueStr, sourceNotation, wasError);
	if (wasError)
		throw underflow_error("There was an overflow of a number of type int\n");

	string result = IntToString(decimalNumber, destinationNotation, wasError);
	if (wasError)
		throw underflow_error("Error when translating from the intermediate (10) system to the final number system\n");

	return result;
}