#include "stdafx.h"
#include "GeneratePrimeNumbersSet.h"

#pragma warning (push, 3)
#pragma warning (pop)

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound)
{

	if ((upperBound < 2) || (upperBound > 100000000))
		return {};
	
	// можно ускорить, объ€вив изначально все места, кратные 2, false
	vector<bool> boleanBolter(upperBound, true);
	boleanBolter.at(0) = false;
	boleanBolter.at(1) = false;

	cout << "boolean vector size: " << boleanBolter.size() << '\n';

	for (size_t i = 2; i * i < upperBound; i++)
	{
		if (boleanBolter.at(i))
		{
			for (size_t j = i; j * i < upperBound; j++)
			{
				boleanBolter[j * i] = false;
			}
		}
	}

	set<int> result;
	for (size_t i = 2; i < boleanBolter.size(); i++)
	{
		if (boleanBolter.at(i))
		{
			result.insert(i);//мб. перенести в пред. цикл
			//cout << i << " ";
		}		
	}
	//cout << endl;

	cout << "number of primes in " << upperBound  << " = "<< result.size() << '\n';



	set<int>::reverse_iterator rit = result.rbegin();
	cout << *rit << endl;


	return result;
}
