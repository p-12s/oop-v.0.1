#include "stdafx.h"

using namespace std;

struct Solve4Fixture
{
	Solve4Fixture()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Solve4, Solve4Fixture)

	BOOST_AUTO_TEST_CASE(test_test)
	{
		BOOST_CHECK(true);
	}

BOOST_AUTO_TEST_SUITE_END()