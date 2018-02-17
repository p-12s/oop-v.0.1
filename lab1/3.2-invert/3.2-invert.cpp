#include "stdafx.h"
#include <iomanip>

using namespace std;

namespace constants
{
	const unsigned MATRIX_SIZE = 3;
	const unsigned FLOAT_PRECISION = 3;
	const unsigned FIELD_DISPLAY_WIDTH = 8;
}

/*
Разработайте приложение invert.exe, выполняющее инвертирование матрицы 3*3, 
т.е. нахождение обратной матрицы 
и выводящее коэффициенты результирующей матрицы в стандартный поток вывода. 

+ Формат командной строки приложения:
+ invert.exe <matrix file1>

+ Коэффициенты входной матрицы заданы во входном текстовом файле
+ (смотрите файл matrix.txt в качестве иллюстрации)  в трех строках по 3 элемента.

+ Коэффициенты результирующей матрицы выводятся с точностью до 3 знаков после запятой.

+ Используйте двухмерные массивы для хранения коэффициентов матриц.

В комплекте с программой должны обязательно поставляться файлы, 
позволяющие проверить ее работу в автоматическом режиме.
 */

typedef float(matrix)[constants::MATRIX_SIZE][constants::MATRIX_SIZE];

float ReadFloatNumberFromString(const string& str)
{
	float number = 0.0;
	try
	{
		number = stof(str);
	}
	catch (exception const&)
	{
		throw exception("Matrix value must be float number");
	}
	return number;
}

void ReadMatrix(istream& input, matrix& sourceMatrix)
{
	
	string matrixRowString, numberString;
	stringstream matrixRowStream;
	int rowIndex = 0;

	while (getline(input, matrixRowString))
	{
		if (rowIndex >= constants::MATRIX_SIZE)
		{
			throw exception("Matrix must have 3 rows");
		}
		matrixRowStream.clear();
		matrixRowStream.str(matrixRowString);
		
		int colIndex = 0;
		while(matrixRowStream >> numberString)
		{
			if (colIndex >= constants::MATRIX_SIZE)
			{
				throw exception("Matrix must have 3 columns!");
			}
			
			sourceMatrix[rowIndex][colIndex] = ReadFloatNumberFromString(numberString);
			++colIndex;
		}
		++rowIndex;
	}	

	if (rowIndex != 3)
	{
		throw exception("Matrix must have 3 rows!");
	}
}

void PrintMatrix(const matrix& sourceMatrix)
{
	cout << fixed << setprecision(constants::FLOAT_PRECISION);
	for (int i = 0; i < constants::MATRIX_SIZE; i++)
	{
		for (int j = 0; j < constants::MATRIX_SIZE; j++)
		{
			cout << setw(constants::FIELD_DISPLAY_WIDTH) << sourceMatrix[i][j];
		}
		cout << endl;
	}
}

float Get3x3MatrixDetermanant(const matrix& mx)
{
	return (mx[0][0] * mx[1][1] * mx[2][2]) + 
		(mx[0][1] * mx[1][2] * mx[2][0]) + 
		(mx[0][2] * mx[1][0] * mx[2][1]) -
		(mx[0][0] * mx[1][2] * mx[2][1]) - 
		(mx[0][1] * mx[1][0] * mx[2][2]) - 
		(mx[0][2] * mx[1][1] * mx[2][0]);
}

float GetAlgebraicComplementFor3x3Matrix(const matrix& mx, const int rowIndex, const int colIndex)
{
	float a, b, c, d;
	for (int i = 0; i < constants::MATRIX_SIZE; i++)
	{
		if (i != rowIndex)
		{
			for (int j = 0; j < constants::MATRIX_SIZE; j++)
			{
				if (j != colIndex)
				{
					// не понимаю следующие шаги по решению. как будет короче?
				}
			}
		}		
	}
}

void InvertMatrix(const matrix& sourceMatrix, matrix& invertedMatrix)
{
	// определитель
	float determinant = Get3x3MatrixDetermanant(sourceMatrix);
	cout << determinant << endl;
	if (determinant == 0)
	{
		throw exception("The inverse matrix does not exist, because the determinant = 0");
	}
	// алгебраические дополнения для союзной матрицы
	// союзная матрица
	// транспонированная союзная матрица
	// делим транспонированную на определитель
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: invert.exe <matrix file1>\n";
		return 1;
	}
	
	if (any_of(&argv[1], &argv[2], [](char* arg) {
		return strlen(arg) == 0;
	}))
	{
		cout << "Arguments <input file> must be non empty!";
		return 1;
	}

	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading" << endl;
		return 1;
	}
	
	try
	{
		matrix sourceMatrix;
		ReadMatrix(inputFile, sourceMatrix);

		matrix invertedMatrix;
		InvertMatrix(sourceMatrix, invertedMatrix);

		//PrintMatrix(sourceMatrix);
	}
	catch (exception const& error)
	{
		cout << error.what() << endl;
		return 1;
	}




    return 0;
}

