#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "TestingUtilities.h"

using namespace std;

struct PointFixture
{
	CPoint point;

	PointFixture()
		: point(0.0, 0.0)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Point, PointFixture)

	BOOST_AUTO_TEST_CASE(has_coordinates)
	{	
		ArePointCoordinatesEqual(point, 0, 0);
	}
	BOOST_AUTO_TEST_CASE(it_is_possible_to_get_the_distance_to_another_point)
	{
		auto newPoint = CPoint(10, 0);
		BOOST_CHECK(point.GetDistanceTo(newPoint) == 10);

		auto newPoint2 = CPoint(-4, -4);
		BOOST_CHECK_CLOSE(point.GetDistanceTo(newPoint2), 5.66, DBL_EPSILON);
	}

BOOST_AUTO_TEST_SUITE_END()