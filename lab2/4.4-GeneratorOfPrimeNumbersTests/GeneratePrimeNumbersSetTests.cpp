#include "stdafx.h"
#include "../4.4-GeneratorOfPrimeNumbers/GeneratePrimeNumbersSet.h"

using namespace std;

int GetNumberOfPrimesInSet(const set<int>& numbersSet)
{
	return numbersSet.size();
}

bool SetsAreEqual(set<int> const& x, set<int> const& y)
{
	return x == y;
}

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)

	BOOST_AUTO_TEST_CASE(returns_an_empty_set_if_the_entered_number_is_less_than_2)
	{
		BOOST_CHECK(SetsAreEqual(GeneratePrimeNumbersSet(1), {}));
	}

	BOOST_AUTO_TEST_CASE(returns_an_empty_set_if_the_entered_number_is_more_than_100_millions)
	{
		BOOST_CHECK(SetsAreEqual(GeneratePrimeNumbersSet(100000001), {}));
	}

	BOOST_AUTO_TEST_CASE(returns_2_if_the_entered_number_2)
	{
		BOOST_CHECK(SetsAreEqual(GeneratePrimeNumbersSet(2), {2}));
	}

	BOOST_AUTO_TEST_CASE(returns_2_3_5_if_the_entered_number_6)
	{
		BOOST_CHECK(SetsAreEqual(GeneratePrimeNumbersSet(6), { 2, 3, 5 }));
	}

	BOOST_AUTO_TEST_CASE(returns_from_2_to_37_if_the_entered_number_37)
	{
		BOOST_CHECK(SetsAreEqual(GeneratePrimeNumbersSet(37), { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }));
	}

	#ifndef _DEBUG
		BOOST_AUTO_TEST_CASE(in_the_range_of_100_million_returns_the_number_of_prime_numbers_equal_to_5761455)
		{
			const unsigned countOfPrimeNumbersIn100Millions = 5761455;
			int countOfPrimeNumbers = GetNumberOfPrimesInSet(GeneratePrimeNumbersSet(100000000));
			BOOST_CHECK(countOfPrimeNumbers == countOfPrimeNumbersIn100Millions);
		}
	#endif

BOOST_AUTO_TEST_SUITE_END()