#include "stdafx.h"

using namespace std;

enum struct ModeOfOperation
{
	Crypt, Decrypt, Unknown
};

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: crypt.exe crypt <input file> <output file> <key>\n"
			<< "from crypt, or\n"
			<< "crypt.exe decrypt <input file> <output file> <key>\n"
			<< "from decrypt";
		return 1;
	}

	if (any_of(&argv[1], &argv[4], [](char* arg) {
		return strlen(arg) == 0;
	}))
	{
		cout << "Arguments crypt <input file> <output file> <key> must be non empty!";
		return 1;
	}

	// проверить соответствие каждого парметра
	string modeParamether = argv[1];
	ModeOfOperation mode = (modeParamether == "crypt") ? ModeOfOperation::Crypt :
							(modeParamether == "decrypt") ? ModeOfOperation::Decrypt :
							ModeOfOperation::Unknown;
	
	if (mode == ModeOfOperation::Unknown)
	{
		cout << "Invalid encryption mode!";
		return 1;
	}



	/*if (mode == ModeOfOperation::Crypt)
		cout << "crypt ++" << endl;
	else if (mode == ModeOfOperation::Decrypt)
		cout << "decrypt ++" << endl;
	else
		cout << "uncnown ++" << endl;
	*/
    return 0;
}