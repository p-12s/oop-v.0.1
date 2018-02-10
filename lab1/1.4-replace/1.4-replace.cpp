#include "stdafx.h"

/*
Разработайте программу replace.exe, выполняющую замену подстроки в текстовом файле на другую строку, 
и записывающей результат в выходной файл (отличный от входного). Формат командной строки:
+replace.exe <input file> <output file> <search string> <replace string>

+ Программа должна корректно обрабатывать ошибки, связанные с открытием входных и выходных файлов. 
+ Искомая строка не может быть пустой.

+Размеры входных и выходных файлов таковы, что в оперативную память программы могут не поместиться целиком. 
+Программа должна обрабатывать входной файл построчно и записывать результаты в выходной файл также построчно. 

Размеры искомой строки и строки-заменителя не ограничены (но с большой вероятностью в ОЗУ поместятся).

Внимание, программа корректно должна обрабатывать ситуацию, когда длина искомой строки равна нулю. 
В этом случае замены символов производиться не должно. 

Также корректно должна обрабатываться ситуация 
с многократным вхождением искомой строки в строку-заменитель (например, замена строки «ма» на «мама» не должна приводить к зацикливанию).

В комплекте с программой должны обязательно поставляться файлы, позволяющие проверить ее работу в автоматическом режиме:
•	.bat файл, выполняющий запуск программы с различными тестовыми параметрами. Необходимо проверить 
возможные граничные условия программы, включая недопустимые ситуации.
•	Эталонные входные и выходные файлы для проверки работы программы с тестовыми входными данными.
Внимание: из опыта автора сдаваемые студентами работы часто некорректно обрабатывают ситуацию с возвратом при неудачном поиске. 
Из-за этого не работает замена подстроки «1231234» внутри текста «12312312345». Добавьте обработку данной ситуации в набор 
тестов и убедитесь в корректности работы программы.
*/

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
		output << ReplaceString(line, searchString, replacementString) << "\n";
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

	ifstream inputFile(argv[1]);	
	/*if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading" << endl;
		return 1;
	}*/

	ofstream outputFile(argv[2]);
	/*if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing" << endl;
		return 1;
	}*/

	string searchStr = argv[3];
	string replaceStr = argv[4];
	CopyFileWithReplace(inputFile, outputFile, searchStr, replaceStr);



	inputFile.close();
	outputFile.flush();
	outputFile.close();
	
    return 0;
}

