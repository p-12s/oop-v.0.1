#include "stdafx.h"
#include "VectorProcessor.h"

#pragma warning (push, 3)
#pragma warning (pop)

using namespace std;
using namespace std::placeholders;

double GetVectorsMaxVal(vector<double>& numbers)
{
	return *max_element(numbers.begin(), numbers.end());
}

void SortVector(vector<double>& numbers)
{
	sort(numbers.begin(), numbers.end());
}

void ProcessVector(vector<double> & numbers)
{
	// Требуется разделить элементы массива на половину максимального элемента
	if (!numbers.empty())
	{
		double maxVal = GetVectorsMaxVal(numbers);
		if (maxVal == 0)
		{
			return;
		}

		transform(numbers.begin(), numbers.end(), numbers.begin(), [=](double value)
		{
			return value / (0.5 * maxVal);
		});
	}
}