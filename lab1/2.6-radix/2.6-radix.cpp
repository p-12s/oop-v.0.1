#include "stdafx.h"

using namespace std;

namespace constants
{
	const char PERMISSIBLE_CHARS_IN_SYSTEMS_OF_NUMBERS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

int StringToInt(const string& input, const int radix, bool& wasError)
{
	// отслеживать переполнение int
	int result = 0;
	
	// вектор для удобного прохождения по строке с пом. transform
	//stringstream stringToIntStream;
	//stringToIntStream.str(input);
	//vector<char> data(input.begin(), input.end());

	// create map from chars
	// проверка - возвращаемое число не дб больше итогового разряда
	map<char, int> charsMap = {
		{ 'A', 11 },
		{ 'B', 12 }
	};

	unsigned int digit = input.size() - 1;
	for (auto &ch : input)
	{
		cout << ch << "* " << digit << "  " << charsMap[ch] << "\n";
		--digit;
	}
	

	//copy(data.begin(), data.end(), ostream_iterator<char>(cout, ", "));

	

	//std::transform(myv1.begin(), myv1.end(), myv1.begin(),
	//	[](double d) -> double { return d * 3; });

	//copy(chars.begin(), chars.end(), ostream_iterator<char>(cout, ", "));

	/*string test = "AAA";
	for (string::iterator it = test.begin(); it != test.end(); ++it)
	{
		cout << *it << '\n';
	}		
	cout << '\n';*/

	// затолкнуть в вектор

	// перевод строки 1F в числов в 10-чно системе
	return result;
	/*int decimalNumber = 0;
	int strLength = str.length();
	int degree, code;
	char symbol;

	for (size_t i = 0; i < strLength; i++)
	{
		degree = strLength - 1 - i;

		cout << i << ": " << str[i] << " degree: " << degree << " ";


		symbol = static_cast<char>(str[i]);
		cout << symbol << " ";

		code = static_cast<int>(str[i]);
		cout << code << " \n";
		//cout << "source in degree: " << radix << "^" << degree << "=" << pow(radix, degree) << endl;
		//cout << "res: " << static_cast<int>(str[i]) * pow(radix, degree) << endl;


		//decimalNumber = decimalNumber + static_cast<int>(str[i]) * pow(radix, degree);
		
		
	}


	try
	{
		// 
		
		int readNumber = std::stoi(str);

		

		return readNumber;
	}
	catch (const std::exception& e)
	{
		wasError = true;
		std::cout << "an error occurred while converting the string " << str << " to a number:\n" << e.what() << "\n";
	}*/

	return 1;
}

/*ValidityOfStringInRadix(valueStr, destinationNotation)
{
	
}*/

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}	

	if (any_of(&argv[1], &argv[4], [](char* arg) {
		return strlen(arg) == 0;
	}))
	{
		cout << "Arguments <source notation> <destination notation> <value> must be non empty!\n";
		return 1;
	}

	// считать значения	

	int sourceNotation;
	int destinationNotation;
	try
	{
		sourceNotation = std::stoi(argv[1]);
		destinationNotation = std::stoi(argv[2]);
	}
	catch (const exception& e)
	{
		cout << e.what();
	}

	string valueStr = argv[3];

	// проверить на валидность
	// попробовать перевести в систему счисления

	//ValidityOfStringInRadix(valueStr, destinationNotation);
	bool wasError = false;	

	int result = StringToInt(valueStr, sourceNotation, wasError);
	if (wasError)
		return 1;

	//cout << result << endl;
    return 0;
}

