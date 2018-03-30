#include "stdafx.h"
#include "CryptProcessing.h"

using namespace std;

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

	try
	{
		CopyFileWithEncryption(argv);
	}
	catch (const exception& error)
	{
		cout << error.what();
		return 1;
	}

    return 0;
}