#include "stdafx.h"
#include "GeneratePrimeNumbersSet.h"
#include <string>

using namespace std;

void PrintSet(const set<int>& numbers)
{
	for (auto number : numbers)
		cout << number << " ";
	cout << endl;
}

int ReadNumberFromString(const string& upperBound)
{
	int number = 0;
	try
	{
		number = stoi(upperBound);
	}
	catch (exception const&)
	{
		throw invalid_argument("Arguments <upper bound value [2, 100000000]> must be a numbers\n");
	}
	return number;
}

void CheckUpperBound(const int upperBound)
{
	if ((upperBound < 2) || (upperBound > 100000000))
		throw runtime_error("The upper bound must be in the range [2, 100000000]\n");
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: program.exe <upper bound value [2, 100000000]>\n";
		return 1;
	}

	try
	{
		int upperBound = ReadNumberFromString(argv[1]);
		CheckUpperBound(upperBound);
		
		set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);

		PrintSet(primeNumbers);
	}
	catch (const exception& error)
	{
		cout << error.what();
		return 1;
	}

    return 0;
}

