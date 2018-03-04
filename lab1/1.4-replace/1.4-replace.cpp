#include "stdafx.h"

using namespace std;

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (subject.empty() || searchString.empty())
		return subject;

	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(istream& input, ostream& output,
	const string& searchString, const string& replacementString)
{
	string line;

	while (getline(input, line))
	{
		if (!searchString.empty())
		{
			output << ReplaceString(line, searchString, replacementString) << "\n";
		}	
		else
		{
			output << line;
		}
	}
}

bool IsStringInFileReplaced(const string& inputName, const string& outputName,
	const string& searchStr, const string& replacementStr)
{
	ifstream inputFile(inputName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputName << " for reading" << endl;
		return false;
	}
	ofstream outputFile(outputName);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputName << " for writing" << endl;
		return false;
	}

	CopyFileWithReplace(inputFile, outputFile, searchStr, replacementStr);

	if (!outputFile.flush())
	{
		cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	if (any_of(&argv[1], &argv[3], [](char* arg) {
		return strlen(arg) == 0;
	}))
	{
		cout << "Arguments <input file>, <output file> must be non empty!";
		return 1;
	}

	if (!IsStringInFileReplaced(argv[1], argv[2], argv[3], argv[4]))
	{
		return 1;
	}

    return 0;
}

