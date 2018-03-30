#include "stdafx.h"
#include "GeneratePrimeNumbersSet.h"

#pragma warning (push, 3)
#pragma warning (pop)

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if ((upperBound < 2) || (upperBound > 100000000))
		return {};

	vector<bool> boleanBolter(upperBound + 1, true);
	boleanBolter[0] = false;
	boleanBolter[1] = false;

	for (size_t i = 2; i * i < boleanBolter.size(); i++)
	{
		if (boleanBolter.at(i))
			for (size_t j = i; j * i < boleanBolter.size(); j++)
				boleanBolter[j * i] = false;
	}

	set<int> result;
	for (size_t i = 2; i < boleanBolter.size(); i++)
	{
		if (boleanBolter[i])
			result.insert(result.end(), i);
	}

	return result;
}