#include "stdafx.h"

/*
������������ ��������� replace.exe, ����������� ������ ��������� � ��������� ����� �� ������ ������, 
� ������������ ��������� � �������� ���� (�������� �� ��������). ������ ��������� ������:
+replace.exe <input file> <output file> <search string> <replace string>

+ ��������� ������ ��������� ������������ ������, ��������� � ��������� ������� � �������� ������. 
+ ������� ������ �� ����� ���� ������.

+������� ������� � �������� ������ ������, ��� � ����������� ������ ��������� ����� �� ����������� �������. 
+��������� ������ ������������ ������� ���� ��������� � ���������� ���������� � �������� ���� ����� ���������. 

������� ������� ������ � ������-���������� �� ���������� (�� � ������� ������������ � ��� ����������).

��������, ��������� ��������� ������ ������������ ��������, ����� ����� ������� ������ ����� ����. 
� ���� ������ ������ �������� ������������� �� ������. 

����� ��������� ������ �������������� �������� 
� ������������ ���������� ������� ������ � ������-���������� (��������, ������ ������ ��� �� ����� �� ������ ��������� � ������������).

� ��������� � ���������� ������ ����������� ������������ �����, ����������� ��������� �� ������ � �������������� ������:
�	.bat ����, ����������� ������ ��������� � ���������� ��������� �����������. ���������� ��������� 
��������� ��������� ������� ���������, ������� ������������ ��������.
�	��������� ������� � �������� ����� ��� �������� ������ ��������� � ��������� �������� �������.
��������: �� ����� ������ ��������� ���������� ������ ����� ����������� ������������ �������� � ��������� ��� ��������� ������. 
��-�� ����� �� �������� ������ ��������� �1231234� ������ ������ �12312312345�. �������� ��������� ������ �������� � ����� 
������ � ��������� � ������������ ������ ���������.
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

	for (int i = 1; i < s.length(); i++) {
		int j = pi[i - 1];

		while (j > 0 && s[i] != s[j]) {
			j = pi[j - 1];
		}

		if (s[i] == s[j]) {
			pi[i] = j + 1;
		}
		else {
			pi[i] = j;
		}
	}

	return pi;
}

int main(int argc, char* argv[])
{
	string s, t;
	s = "abababc";
	t = "ba";

	vector<int> pi = prefix_function(t + '#' + s);

	int t_len = t.length();

	for (int i = 0; i < s.length(); i++) {
		if (pi[t_len + 1 + i] == t_len) {
			cout << "s[" << i - t_len + 1 << ".." << i << "] = t" << endl;
		}
	}
	/*
	abababc
	ba
	s[0..1] = t
	s[2..3] = t
	s[4..5] = t
	*/


	/*
	// �������� ��� ������� ��� ��������� ������� � ������ � ��� �������� �(<����� �������>+<����� ������>)
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
		//TODO ���������� �� �����. result
		string result = StrReplace(searchStr, replaceStr, line);
		if (!(outputFile << result << endl))
		{
			cout << "Failed to save data on disk\n";
		}
	}

	// TODO ������
	inputFile.close();
	outputFile.close();

	*/
    return 0;

}

