#include "stdafx.h"
#include <iomanip>

using namespace std;

namespace constants
{
	const unsigned MATRIX_SIZE = 3;
	const unsigned FLOAT_PRECISION = 3;
	const unsigned FIELD_DISPLAY_WIDTH = 8;
}

typedef double(matrix)[constants::MATRIX_SIZE][constants::MATRIX_SIZE];

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

void ReadMatrix3x3(istream& input, matrix& sourceMatrix)
{
	string matrixRowString, numberString;
	stringstream matrixRowStream;
	int rowIndex = 0;

	while (getline(input, matrixRowString))
	{
		if (rowIndex >= constants::MATRIX_SIZE)
		{
			throw runtime_error("Matrix must have 3 rows");
		}
		matrixRowStream.clear();
		matrixRowStream.str(matrixRowString);
		
		int colIndex = 0;
		while(matrixRowStream >> numberString)
		{
			if (colIndex >= constants::MATRIX_SIZE)
			{
				throw runtime_error("Matrix must have 3 columns!");
			}
			
			sourceMatrix[rowIndex][colIndex] = ReadFloatNumberFromString(numberString);
			++colIndex;			
		}
		if (colIndex < constants::MATRIX_SIZE)
		{
			throw runtime_error("Matrix must have 3 columns!");
		}
		++rowIndex;
	}	

	if (rowIndex != constants::MATRIX_SIZE)
	{
		throw runtime_error("Matrix must have 3 rows!");
	}
}

void TryReadMatrix(const string& inputName, matrix& matrix)
{
	ifstream inputFile(inputName);
	if (!inputFile.is_open())
		throw runtime_error("Failed to open file for reading");
	
	ReadMatrix3x3(inputFile, matrix);
}

void PrintMatrix3x3(const matrix& sourceMatrix)
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

double Get3x3MatrixDetermanant(const matrix& mx)
{
	return (mx[0][0] * mx[1][1] * mx[2][2]) + 
		(mx[0][1] * mx[1][2] * mx[2][0]) + 
		(mx[0][2] * mx[1][0] * mx[2][1]) -
		(mx[0][0] * mx[1][2] * mx[2][1]) - 
		(mx[0][1] * mx[1][0] * mx[2][2]) - 
		(mx[0][2] * mx[1][1] * mx[2][0]);
}

void SetOppositeIndicesForMatrix3x3(const int index, int& oppositeIndex1, int& oppositeIndex2)
{
	switch (index)
	{
	case 0:
		oppositeIndex1 = 1;
		oppositeIndex2 = 2;
		break;
	case 1:
		oppositeIndex1 = 0;
		oppositeIndex2 = 2;
		break;
	case 2:
		oppositeIndex1 = 0;
		oppositeIndex2 = 1;
		break;
	default:
		throw runtime_error("The cells of the matrix must have indices from 0 to 2");
	}
}

void TransposeMatrix3x3(const matrix& mx, matrix& transposeMx)
{
	for (int i = 0; i < constants::MATRIX_SIZE; i++)
	{
		for (int j = i; j < constants::MATRIX_SIZE; j++)
		{
			transposeMx[i][j] = mx[j][i];
			transposeMx[j][i] = mx[i][j];
		}
	}
}

void GetAdjointMatrix3x3(const matrix& mx, matrix& algebraicComplementsOfMatrix)
{
	int oppRow1, oppRow2, oppCol1, oppCol2;
	for (int i = 0; i < constants::MATRIX_SIZE; i++)
	{
		for (int j = 0; j < constants::MATRIX_SIZE; j++)
		{
			SetOppositeIndicesForMatrix3x3(i, oppRow1, oppRow2);
			SetOppositeIndicesForMatrix3x3(j, oppCol1, oppCol2);
                        algebraicComplementsOfMatrix[i][j] =
                            pow((-1), (i + j)) *
                            ((mx[oppRow1][oppCol1] * mx[oppRow2][oppCol2]) -
                             (mx[oppRow2][oppCol1] * mx[oppRow1][oppCol2]));
                }
        }
}

void DivideMatrix3x3ByDeterminant(matrix& invertedMatrix, const double& determinant)
{
	for (int i = 0; i < constants::MATRIX_SIZE; i++)
	{
		for (int j = 0; j < constants::MATRIX_SIZE; j++)
		{
			invertedMatrix[i][j] /= determinant;
		}
	}
}

void TryInvertMatrix(const matrix& sourceMatrix, matrix& invertedMatrix)
{
	double determinant = Get3x3MatrixDetermanant(sourceMatrix);
	if (determinant == 0)
		throw runtime_error("The inverse matrix does not exist, because the determinant = 0");

	matrix transposeMatrix;
	TransposeMatrix3x3(sourceMatrix, transposeMatrix);

	GetAdjointMatrix3x3(transposeMatrix, invertedMatrix); // matrix of algebraic complements (adjoint matrix)

	DivideMatrix3x3ByDeterminant(invertedMatrix, determinant);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: invert.exe <matrix file>\n";
		return 1;
	}

	try
	{
		matrix sourceMatrix;
		TryReadMatrix(argv[1], sourceMatrix);

		matrix invertedMatrix;
		TryInvertMatrix(sourceMatrix, invertedMatrix);

		PrintMatrix3x3(invertedMatrix);
	}
	catch (exception const& error)
	{
		cout << error.what() << endl;
		return 1;
	}

    return 0;
}