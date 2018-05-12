#include "stdafx.h"
#include "../1.4-Solve4/Solve4.h"

using namespace std;

struct Solve4Fixture
{
	double a = 16;
	double b = 0;
	double c = 145;
	double d = 0;
	double e = 9;
	CSolve4 solve4;

	Solve4Fixture()
		: solve4(a, b, c, d, e)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Solve4, Solve4Fixture)

	BOOST_AUTO_TEST_CASE(the_coefficient_of_x_in_4_degree_can_not_be_0)
	{
		BOOST_CHECK_THROW(CSolve4(0, b, c, d, e), exception);
		BOOST_CHECK_NO_THROW(CSolve4(a, b, c, d, e), exception);
	}

BOOST_AUTO_TEST_SUITE_END()