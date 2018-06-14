#include "stdafx.h"
#include "Crypt.h"

using namespace std;

int ReadNumberFromString(const string& notation)
{
	int number;
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

uint8_t CryptByte(uint8_t byte, const int key)
{
	byte = byte ^ key;
	uint8_t bits210 = (byte & 7) << 2;
	uint8_t bits43 = (byte & 3 << 3) << 3;
	uint8_t bits65 = (byte & 3 << 5) >> 5;
	uint8_t bit7 = (byte & 1 << 7) >> 2;
	return (bit7 | bits65 | bits43 | bits210);
}

uint8_t DecryptByte(const uint8_t byte, const int key)
{
	uint8_t bits10 = (byte & 3) << 5;
	uint8_t bits432 = (byte & 7 << 2) >> 2;
	uint8_t bit5 = (byte & 1 << 5) << 2;
	uint8_t bits76 = (byte & 3 << 6) >> 3;
	return (bits76 | bit5 | bits432 | bits10) ^ key;
}

bool TryCrypt(istream& input, ostream& output, const int key, const ModeOfOperation& mode)
{
	uint8_t byte;
	while (input.read(reinterpret_cast<char*>(&byte), 1))
	{
		if (mode == ModeOfOperation::Crypt)
		{
			byte = CryptByte(byte, key);
			if (!output.write(reinterpret_cast<char*>(&byte), 1))
				return false;
		}
		else if (mode == ModeOfOperation::Decrypt)
		{
			byte = DecryptByte(byte, key);			
			if (!output.write(reinterpret_cast<char*>(&byte), 1))
				return false;
		}
		else
			return false;
	}
	return true;
}

ModeOfOperation GetMode(const string& modeName)
{
	ModeOfOperation mode;
	if (modeName == "crypt")
		mode = ModeOfOperation::Crypt;
	else if (modeName == "decrypt")
		mode = ModeOfOperation::Decrypt;
	else
		throw runtime_error("Invalid encryption mode. Use crypt or encrypt\n");
	return mode;
}

int GetKeyParamether(const string& modeArgc)
{
	int key = ReadNumberFromString(modeArgc);
	if (key < 0 || key > 255)
		throw invalid_argument("Paramether key must be in interval [0, 255]\n");
	return key;
}

ifstream OpenFileForBinReading(const string& fileName)
{
	ifstream strm(fileName, ios_base::binary);
	if (!strm.is_open())
		throw runtime_error("Failed to open file for reading\n");
	return move(strm);
}

ofstream OpenFileForBinWriting(const string& fileName)
{
	ofstream strm(fileName, ios_base::binary);
	if (!strm.is_open())
		throw runtime_error("Failed to open file for writing\n");
	return move(strm);
}

void CopyFileWithEncryption(char* argv[])
{
	ModeOfOperation mode = GetMode(argv[1]);
	int key = GetKeyParamether(argv[4]);

	ifstream inputFile = OpenFileForBinReading(argv[2]);
	ofstream outputFile = OpenFileForBinWriting(argv[3]);

	if (!TryCrypt(inputFile, outputFile, key, mode))
		throw runtime_error("An error occurred while processing the file\n");

	if (!outputFile.flush())
		throw runtime_error("Failed to save data on disk\n");
}