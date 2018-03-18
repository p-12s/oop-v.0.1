#include "stdafx.h"
#include "RadixProcessing.h"

using namespace std;

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
		int sourceNotation;
		int destinationNotation;
		string valueStr;
		CheckValidityOfParameters(argv, sourceNotation, destinationNotation, valueStr);

		string result = TryChangingRadix(sourceNotation, destinationNotation, valueStr);
		cout << result << endl;
	}
	catch (const exception& error)
	{
		cout << error.what();
		return 1;
	}

	return 0;
}