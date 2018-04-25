#include "stdafx.h"
#include "../1.2-Shape/Shape.h"

using namespace std;

struct ShapeFixture
{
	stringstream output;
	const CShape shape;
	const string color = "gray";
	const string type = "circle";

	ShapeFixture()
		: shape(color, type)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Shape, ShapeFixture)
	BOOST_AUTO_TEST_SUITE(general_behavior)

		BOOST_AUTO_TEST_CASE(test_test)
		{
			BOOST_CHECK(false == true);
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
