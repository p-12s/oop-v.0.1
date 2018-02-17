#include "stdafx.h"

using namespace std;

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
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

void CopyFileWithReplace(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
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

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	if (any_of(&argv[1], &argv[2], [](char* arg) {
		return strlen(arg) == 0;
	}))
	{
		cout << "Arguments <input file>, <output file> must be non empty!";
		return 1;
	}

	ifstream inputFile(argv[1]);	
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading" << endl;
		return 1;
	}
	ofstream outputFile(argv[2]);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing" << endl;
		return 1;
	}

	string searchStr = argv[3];
	string replaceStr = argv[4];
	CopyFileWithReplace(inputFile, outputFile, searchStr, replaceStr);

	inputFile.close();
	outputFile.flush();
	outputFile.close();

    return 0;
}

