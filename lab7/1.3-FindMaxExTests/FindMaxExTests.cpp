#include "stdafx.h"
#include "../1.3-FindMaxEx/FindMaxEx.h"

using namespace std;

/*BOOST_FIXTURE_TEST_SUITE(FindMaxExFunction)

	BOOST_AUTO_TEST_CASE(give_me_max)
	{
		BOOST_CHECK(true);
	}
// вернуть ложь
// если пусто - вернуть ложь
// просто вернуть первый
// 

BOOST_AUTO_TEST_SUITE_END()*/

BOOST_AUTO_TEST_SUITE(FindMaxExFunction)
	BOOST_AUTO_TEST_CASE(for_an_empty_vector_will_return_false)
	{
		// TODO закинуть в обин объект инт, флоат, строку
	// TODO [](auto& x1, auto& x2) есть у меня в 5 лабе
		vector<int> emptyIntVector;
		vector<int> notEmptyIntVector = { 1, 3, 4, 2, -7, 8 };
		int intElement;
		BOOST_CHECK(!FindMaxEx(emptyIntVector, intElement));
		BOOST_CHECK(FindMaxEx(notEmptyIntVector, intElement));
		/*BOOST_CHECK(!FindMax(emptyVector, element, [](auto& x1, auto& x2) {
			return x1.intValue < x2.intValue;
		}));*/
		
		vector<float> emptyFloatVector;
		vector<float> notEmptyFloatVector = { 1., 3., 4., 2., -7., 8. };
		float floatElement;
		BOOST_CHECK(!FindMaxEx(emptyFloatVector, floatElement));
		BOOST_CHECK(FindMaxEx(notEmptyFloatVector, floatElement));
		

	}
BOOST_AUTO_TEST_SUITE_END()
