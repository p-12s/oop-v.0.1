#include "stdafx.h"
#include "ReadShape.h"

using namespace std;
// ���������� ����� � ������������� - � ���� ����
// ���� ����� ������� �� ��������� � �������� - � ������

void ReadShapes(const string& inputName, vector<shared_ptr<IShape>>& shapes)
{
	ifstream inputFile(inputName);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open file for reading");

	// ��������� ������ � shapeString
	string shapeString, argument;
	stringstream shapeStream;

	while (getline(inputFile, shapeString))
	{
		shapeStream.clear();
		shapeStream.str(shapeString);

		while (shapeStream >> argument)
		{
			// ��������� ������ �������� ������������ Shape
			cout << argument << endl;

			//ReadFloatNumberFromString(numberString);
		}
		cout << endl;
	}
}