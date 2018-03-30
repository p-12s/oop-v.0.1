#include "stdafx.h"
#include "CryptProcessing.h"

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

uint8_t CryptByte(uint8_t& byte)
{
	uint8_t bit0 = (byte & 1) << 2;
	uint8_t bit1 = (byte & 1 << 1) << 2;
	uint8_t bit2 = (byte & 1 << 2) << 2;
	uint8_t bit3 = (byte & 1 << 3) << 3;
	uint8_t bit4 = (byte & 1 << 4) << 3;
	uint8_t bit5 = (byte & 1 << 5) >> 5;
	uint8_t bit6 = (byte & 1 << 6) >> 5;
	uint8_t bit7 = (byte & 1 << 7) >> 2;
	return (bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0);
}

uint8_t DecryptByte(const uint8_t& byte)
{
	uint8_t bit0 = (byte & 1) << 5;
	uint8_t bit1 = (byte & 1 << 1) << 5;
	uint8_t bit2 = (byte & 1 << 2) >> 2;
	uint8_t bit3 = (byte & 1 << 3) >> 2;
	uint8_t bit4 = (byte & 1 << 4) >> 2;
	uint8_t bit5 = (byte & 1 << 5) << 2;
	uint8_t bit6 = (byte & 1 << 6) >> 3;
	uint8_t bit7 = (byte & 1 << 7) >> 3;
	return (bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0);
}

bool IsFileProcessed(istream& input, ostream& output, int key, ModeOfOperation& mode)
{
	uint8_t byte;
	while (input.read(reinterpret_cast<char*>(&byte), 1))
	{
		if (mode == ModeOfOperation::Crypt)
		{
			byte = byte ^ key;
			byte = CryptByte(byte);
			if (!output.write(reinterpret_cast<char*>(&byte), 1))
				return false;
		}
		else if (mode == ModeOfOperation::Decrypt)
		{
			byte = DecryptByte(byte);
			byte = byte ^ key;
			if (!output.write(reinterpret_cast<char*>(&byte), 1))
				return false;
		}
		else
			return false;
	}
	return true;
}

ModeOfOperation GetModeParamether(const string& modeArgc)
{
	ModeOfOperation mode = (modeArgc == "crypt") ? ModeOfOperation::Crypt :
		(modeArgc == "decrypt") ? ModeOfOperation::Decrypt :
		ModeOfOperation::Unknown;
	if (mode == ModeOfOperation::Unknown)
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

void CopyFileWithEncryption(char* argv[])
{
	ModeOfOperation mode = GetModeParamether(argv[1]);
	int key = GetKeyParamether(argv[4]);

	ifstream inputFile(argv[2]);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open file for reading\n");

	ofstream outputFile(argv[3]);
	if (!outputFile.is_open())
		throw runtime_error("Failed to open file for writing\n");

	if (!IsFileProcessed(inputFile, outputFile, key, mode))
		throw runtime_error("An error occurred while processing the file\n");

	if (!outputFile.flush())
		throw runtime_error("Failed to save data on disk\n");
}