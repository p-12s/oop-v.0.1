#include "stdafx.h"
#include "../4.4-GeneratorOfPrimeNumbers/GeneratePrimeNumbersSet.h"

using namespace std;

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
//Для проверки программы используйте тот факт, что в диапазоне от 1 до 100000000 содержится 5761456 простых чисел.

BOOST_AUTO_TEST_SUITE_END()