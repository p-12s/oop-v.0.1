#include "stdafx.h"
#include "../1.2-Shape/Point.h"

using namespace std;

struct PointFixture
{
	const CPoint point;
	PointFixture()
		: point(0, 0)
	{
	}

	void CheckPointCoordinates(const double expectedX, const double expectedY) const
	{
		auto coordinates = point.GetCoordinates();
		BOOST_CHECK(coordinates.first == expectedX);
		BOOST_CHECK(coordinates.second == expectedY);
	}

	bool CheckEqualOfTwoNumbers(const double a, const double b) const
	{
		return (round(a * 100) / 100) == b;
	}
};//TODO тут мб вынести проверочные функции в отдельный файл

BOOST_FIXTURE_TEST_SUITE(Point, PointFixture)
	BOOST_AUTO_TEST_CASE(has_coordinates)
	{
		CheckPointCoordinates(0, 0);
	}
	BOOST_AUTO_TEST_CASE(it_is_possible_to_get_the_distance_to_another_point)
	{
		CheckPointCoordinates(0, 0);

		auto newPoint = CPoint(10, 0);
		BOOST_CHECK(point.GetDistanceTo(newPoint) == 10);

		auto newPoint2 = CPoint(-4, -4);
		BOOST_CHECK(CheckEqualOfTwoNumbers(point.GetDistanceTo(newPoint2), 5.66));
	}
BOOST_AUTO_TEST_SUITE_END()