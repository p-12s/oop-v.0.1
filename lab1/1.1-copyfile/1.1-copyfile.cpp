#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void CopyByChar(ifstream& input, ostream& output)
{
	char ch;
	while(input.get(ch))
	{
		if (!output.put(ch))
			throw runtime_error("Failed to save data on disk\n");
	}

	if (!output.flush())
		throw runtime_error("Failed to save data on disk\n");
}


bool IsFileCopied(const string& inputName, const string& outputName)
{
	ifstream inputFile(inputName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputName << " for reading" << endl;
		return false;
	}

	ofstream outputFile(outputName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << outputName << " for writing" << endl;
		return false;
	}

	try
	{
		CopyByChar(inputFile, outputFile);
	}
	catch (const exception& error)
	{
		cout << error.what();
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid argument counts\n"
			<< "Usage: copyfile.exe <input file> <output file>\n";
		return 1;
	}

	if (any_of(&argv[1], &argv[2], [](char* arg){
		return strlen(arg) == 0;
	}))
	{
		cout << "Arguments <input file>, <output file> must benot empty!\n";
		return 1;
	}
	
	if (!IsFileCopied(argv[1], argv[2]))
		return 1;

    return 0;
}