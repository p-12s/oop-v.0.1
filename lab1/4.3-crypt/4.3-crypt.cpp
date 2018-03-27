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

	// проверка открытия входного файла
	ifstream inputFile(argv[2]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for reading" << endl;
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

	// открыть файл на чтение в двоичном режиме, в файле пусть будет 1 байт
	ifstream input = OpenFileInBinaryModeForReading(argv[2]);
	// связать с потоком ввода

	uint8_t byte;
	while (input.read(reinterpret_cast<char*>(&byte), 1))
	{
		cout << byte << endl;
		// flush ?
	}

	//  то же самое для потока вывода

	// считывать по байту (8 бит) и отправлять на выход


    return 0;
}