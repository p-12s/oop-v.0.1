#include "stdafx.h"
#include "IShape.h"
#include "ShapesCreator.h"
#include "CalculatingShapes.h"

using namespace std;

vector<shared_ptr<IShape>> ReadShapes(const string& inputName)
{
	ifstream inputFile(inputName);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open file for reading");

	vector<shared_ptr<IShape>> shapes;
	string shapeString;
	CShapesCreator shapesCreator;
	while (getline(inputFile, shapeString))
		shapes.push_back(shapesCreator.CreateShapesFromString(shapeString));
	
	return shapes;
}

void PrintShapes(const vector<shared_ptr<IShape>>& shapes)
{
	for_each(shapes.begin(), shapes.end(), [&](auto& shape) {
		cout << shape->ToString() << endl;
	});
}

void PrintShapeWithLargestArea(const vector<shared_ptr<IShape>>& shapes)
{
	shared_ptr<IShape> shapeWithLargestArea = CalculateLargestArea(shapes);
	if (shapeWithLargestArea)
		cout << "The figure with the largest area:\n" 
			<< shapeWithLargestArea->ToString() << endl;
}

void PrintShapeWithLeastPerimeter(const vector<shared_ptr<IShape>>& shapes)
{
	shared_ptr<IShape> shapeWithLeastPerimeter = CalculateLeastPerimeter(shapes);
	if (shapeWithLeastPerimeter)
		cout << "The figure with the least perimeter:\n"
		<< shapeWithLeastPerimeter->ToString() << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: program.exe <file with shapes>\n";
		return 1;
	}
	
	try
	{
		/*
		Пусть лучше функция возвращает массив фигур. Тогда не придётся передавать ранее созданный массив
		 */
		vector<shared_ptr<IShape>> shapes = ReadShapes(argv[1]);
		if (shapes.empty())
		{
			cout << "There is no figure\n";
			return 0;
		}			

		PrintShapes(shapes);
		PrintShapeWithLargestArea(shapes);
		PrintShapeWithLeastPerimeter(shapes);
	}
	catch (const exception& error)
	{
		cout << error.what();
		return 1;
	}
}

