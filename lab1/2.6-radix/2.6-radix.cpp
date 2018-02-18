#include "stdafx.h"

using namespace std;

/*
������������ ��������� radix.exe, ����������� ������� ����� �� ����� ������������ ������� ��������� 
� ������ ������������ � ������ ���������� � ����������� ����� ������. 
��� ������������ �������� ��������� ���������� ������� � ���������� �� 2 �� 36. 

������� ��������� � 11-������ �� 36-������ ������ ������������ ��������� ����� ���������� �������� �� A �� Z 
��� ������������� �������� � 1010 �� 3510. 

������ ��������� ������ ����������:
radix.exe <source notation> <destination notation> <value>
��������, ��������� �������� ��������� ������ ������������ ������� ������������������ ����� 1F 
� ��� ���������� �������������:
radix.exe 16 10 1F

� ����� ������, ��������� � ����������� ����� ������ ������ ������������� ��� \n.

��������� ������ ���� �������� ������������ ������� ��� �������������, ��� � ������������� �����, � ����� ����.
������ �������� ������� �������� ������������ � ����������� ����� ����� �� ������ ���������
(��� ������ ����������������� ���������).

��������� ������ ��������� ������������ ������

��������, ��� �������� ���������� ������������� � �������� � ��������� � ��������� � ������������
�������� ��������� ������ ���� ����������� �������:
int StringToInt(const string& str, int radix, bool & wasError);
�
std::string IntToString(int n, int radix, bool & wasError);

� ������ ������ (������������ �������� ������� ����������, ������������ ��� �������� ������ � �����) 
������ ������� ������ �������� ��������� ������� ���������� wasError.

� ������ ����������� ������ ��������� ������ ������� ��������������� ��������� � ��������� ��������� ���� ������.

� ��������� � ���������� ������ ����������� ������������ �����, ����������� ��������� �� ������ � �������������� ������.
*/

#include <typeinfo>

int StringToInt(const string& str, int radix, bool& wasError)
{
	// ����� ������

	// ��������� �� ���������� ��� ��������

	// ������� ������ � ���������� radix - � ���������� ������� ���������
	
	/*
	������� ����� a1a2a3 � ������� ��������� � ���������� b. 
	��� �������� � 10-� ������� ���������� ������ ������ ����� �������� �� bn, 
	��� n � ����� �������. ����� �������, (a1a2a3)b = (a1*b2 + a2*b1 + a3*b0)10.
	*/

	cout << "std: " << str << ", str len: " << str.length() << endl;

	int decimalNumber = 0;
	int strLength = str.length();
	int degree;
	char symbol;

	for (size_t i = 0; i < strLength; i++)
	{
		degree = strLength - 1 - i;

		//cout << i << ": " << str[i] << " source: " << radix << " degree: " << degree << endl;


		symbol = static_cast<char>(str[i]);
		cout << typeid(symbol).name() << endl;

		cout << "source in degree: " << radix << "^" << degree << "=" << pow(radix, degree) << endl;
		cout << "res: " << static_cast<int>(str[i]) * pow(radix, degree) << endl;


		decimalNumber = decimalNumber + static_cast<int>(str[i]) * pow(radix, degree);

		
	}

	cout << "number: " << decimalNumber << endl;
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

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}
	
	bool wasError = false;

	if (any_of(&argv[1], &argv[4], [](char* arg) {
		return strlen(arg) == 0;
	}))
	{
		cout << "Arguments <source notation> <destination notation> <value> must be non empty!\n";
		return 1;
	}

	int sourceNotationStr = std::stoi(argv[1]);
	int destinationNotationStr = std::stoi(argv[2]);
	// TODO 2-36


	string valueStr = argv[3];

	bool wasError = false;

	StringToInt(valueStr, sourceNotationStr, wasError);



	// 1F �� 16-�� ������� � ����������

	// �� 10-������� � ������������




	// ������ �������� - ���������, �� ����� ����� ����������
	// �� ����� ������� � ����������, � �� ���������� � �����

    return 0;
}

