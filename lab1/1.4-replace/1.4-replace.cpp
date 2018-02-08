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

string StrReplace(const string search, const string replace, const string subject)
{
	string result = "";
	if (!replace.empty())
	{
		result += replace;
	}
	return result;
}

#include <vector>

vector<int> prefix_function(const string& s) {
	vector<int> pi(s.length(), 0);

	for (int i = 1; i < s.length(); i++)
	{
		int j = pi[i - 1];

		while (j > 0 && s[i] != s[j])
		{
			j = pi[j - 1];
		}

		if (s[i] == s[j])
		{
			pi[i] = j + 1;
		}
		else 
		{
			pi[i] = j;
		}
	}

	return pi;
}

int main(int argc, char* argv[])
{
	// более-менее принцип понятен, нужно понять лучше
	// придумать, как заменять, а не просто выдавать индексы
	string s, t;
	//s = "abababc";
	//t = "ba";
	s = "12312312345";
	t = "1231234";

	vector<int> pi = prefix_function(t + '#' + s);

	int t_len = t.length();

	for (int i = 0; i < s.length(); i++) 
	{
		if (pi[t_len + 1 + i] == t_len) 
		{
			cout << "s[" << i - t_len + 1 << ".." << i << "] = t" << endl;
		}
	}
	/*
	abababc
	ba
	s[1..2] = t
	s[3..4] = t
	*/


	
	// Алгоритм КМП находит все вхождения образца в строку и его скорость О(<длина образца>+<длина строки>)
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>" << endl;
		return 1;
	}

	string input = argv[1];
	string output = argv[2];
	string searchStr = argv[3];
	string replaceStr = argv[4];
	if (searchStr.empty())
	{
		cout << "The search string can not be empty" << endl;
		return 1;
	}

	ifstream inputFile(input);
	ofstream outputFile(output);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading" << endl;
		return 1;
	}
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing" << endl;
		return 1;
	}

	if (argv[3] == "")
	{
		cout << "The search string can not be empty" << endl;
		return 1;
	}
	
	string line;
	while (getline(inputFile, line))
	{
		//TODO избавиться от перем. result
		string result = StrReplace(searchStr, replaceStr, line);
		if (!(outputFile << result << endl))
		{
			cout << "Failed to save data on disk\n";
		}
	}

	// TODO батник
	inputFile.close();
	outputFile.close();

	
    return 0;

}

