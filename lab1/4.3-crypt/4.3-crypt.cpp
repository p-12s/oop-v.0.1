#include "stdafx.h"

using namespace std;

enum struct ModeOfOperation
{
	Crypt, Decrypt, Unknown
};

int ReadNumberFromString(const string& notation)
{
	int number = 0;
	try
	{
		number = stoi(notation);
	}
	catch (exception const&)
	{
		throw invalid_argument("Argument must be a number!\n");
	}
	return number;
}
/*
ifstream OpenFileInBinaryModeForReading(const string& fileName)
{
	ifstream strm(fileName, ios_base::binary);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

ofstream OpenFileInBinaryModeForWriting(const string& fileName)
{
	ofstream strm(fileName, ios_base::binary);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}*/

void CopyFileWithBytePermutation(istream& input, ostream& output)
{
	// TODO почему тут так, и можно ли по-другому
	uint8_t byte;
	
	while (input.read(reinterpret_cast<char*>(&byte), 1))
	{
		output << byte;
	}
}

uint8_t EncodeByte(const uint8_t& byte)
{
	uint8_t bit0 = (byte & 1) << 2;
	uint8_t bit1 = (byte & 1 << 1) << 2;
	uint8_t bit2 = (byte & 1 << 2) << 2;
	uint8_t bit3 = (byte & 1 << 3) << 3;
	uint8_t bit4 = (byte & 1 << 4) << 3;
	uint8_t bit5 = (byte & 1 << 5) >> 5;
	uint8_t bit6 = (byte & 1 << 6) >> 5;
	uint8_t bit7 = (byte & 1 << 7) >> 2;
	return bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0;
}

uint8_t DecodeByte(const uint8_t& byte)
{
	uint8_t bit0 = (byte & 1) << 5;
	uint8_t bit1 = (byte & 1 << 1) << 5;
	uint8_t bit2 = (byte & 1 << 2) >> 2;
	uint8_t bit3 = (byte & 1 << 3) >> 2;
	uint8_t bit4 = (byte & 1 << 4) >> 2;
	uint8_t bit5 = (byte & 1 << 5) << 2;
	uint8_t bit6 = (byte & 1 << 6) >> 3;
	uint8_t bit7 = (byte & 1 << 7) >> 3;
	return bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0;
}

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

	// проверка режима
	// возможно она излишня

	string modeParamether = argv[1];
	ModeOfOperation mode = (modeParamether == "crypt") ? ModeOfOperation::Crypt :
							(modeParamether == "decrypt") ? ModeOfOperation::Decrypt :
							ModeOfOperation::Unknown;
	
	if (mode == ModeOfOperation::Unknown)
	{
		cout << "Invalid encryption mode!";
		return 1;
	}

	// проверка параметра шифрования key	
	try
	{
		int key = ReadNumberFromString(argv[4]);

		if (key < 0 || key > 255)
			throw invalid_argument("Paramether key must be in interval [0, 255]\n");

		cout << key << endl;
	}
	catch (const exception& error)
	{
		cout << error.what();
		return 1;
	}

	ifstream inputFile(argv[2]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for reading" << endl;
		return 1;
	}
	ofstream outputFile(argv[3]);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[3] << " for writing" << endl;
		return 1;
	}

	CopyFileWithBytePermutation(inputFile, outputFile);

	if (!outputFile.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}


    return 0;
}