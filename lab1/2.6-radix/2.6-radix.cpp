#include "stdafx.h"

using namespace std;

namespace constants
{
	const char PERMISSIBLE_CHARS_IN_SYSTEMS_OF_NUMBERS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

/*
Разработайте программу radix.exe, выполняющую перевод чисел из одной произвольной системы счисления 
в другую произвольную и запись результата в стандартный поток вывода. 

Под произвольной системой счисления понимается система с основанием от 2 до 36. 

Системы счисления с 11-ричной до 36-ричной должны использовать заглавные буквы латинского алфавита 
от A до Z для представления разрядов с 1010 до 3510. 

Формат командной строки приложения:
radix.exe <source notation> <destination notation> <value>

Например, следующим способом программа должна осуществлять перевод шестнадцатеричного числа 1F в его десятичное представление:
radix.exe 16 10 1F

В конце строки, выводимой в стандартный поток вывода должен располагаться код \n.

Программа должна быть способна осуществлять перевод как положительных, так и отрицательных чисел, а также нуля.

Особое внимание уделите переводу максимальных и минимальных целых чисел на данной платформе (они должны преобразовываться корректно).

Программа должна корректно обрабатывать ошибки

Внимание, для перевода строкового представления в числовое и числового в строковое
в произвольных системах счисления должны быть разработаны функции:
int StringToInt(const string& str, int radix, bool & wasError);
и
std::string IntToString(int n, int radix, bool & wasError);

В случае ошибок (некорректные значения входных параметров, переполнение при переводе строки в число) 
данные функции должны изменять состояние булевой переменной wasError.

В случае обнаружения ошибки программа должна вывести соответствующее сообщение и корректно завершить свою работу.

В комплекте с программой должны обязательно поставляться файлы, позволяющие проверить ее работу в автоматическом режиме.
*/

#include <typeinfo>

int StringToInt(const string& str, int radix, bool& wasError)
{
	// перевод строки 1F в числов в 10-чно системе

	// ��������� �� ���������� ��� ��������

	// ������� ������ � ���������� radix - � ���������� ������� ���������


	cout << "std: " << str << ", str len: " << str.length() << endl;

	int decimalNumber = 0;
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
		/*cout << "res: " << static_cast<int>(str[i]) * pow(radix, degree) << endl;


		decimalNumber = decimalNumber + static_cast<int>(str[i]) * pow(radix, degree);
		*/
		
	}

	//cout << "number: " << decimalNumber << endl;
	// �������� �� ������������ int

	// �������

	/*try
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

	int sourceNotation;
	int destinationNotation;
	// валидные значения 2-36
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

	//ValidityOfStringInRadix(valueStr, destinationNotation);
	bool wasError = false;
	
	StringToInt(valueStr, sourceNotation, wasError);



	// 1F из 16-тиричной в 10-тичную




    return 0;
}

