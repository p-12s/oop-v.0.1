#include "stdafx.h"
#include "../1.1-Complex/Complex.h"

using namespace std;

struct ComplexFixture
{
	CComplex complex = CComplex();
	ComplexFixture()
		: complex()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Complex, ComplexFixture)
	BOOST_AUTO_TEST_CASE(test_test)
	{
		BOOST_CHECK(true);
	}
BOOST_AUTO_TEST_SUITE_END()