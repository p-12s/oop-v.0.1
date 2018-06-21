#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "../1.2-Shape/Circle.h"
#include "TestingUtilities.h"

using namespace std;

struct CircleFixture
{
	CPoint center = CPoint(0.0, 0.0);
	double radius = 3;
	string outlineColor = "000000";
	string fillColor = "ffff00";
	CCircle circle;

	CircleFixture()
		: circle(center, radius, outlineColor, fillColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Circle, CircleFixture)

	BOOST_AUTO_TEST_CASE(has_the_coordinate_of_center)
	{
		ArePointCoordinatesEqual(circle.GetCenter(), 0, 0);
	}
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_CLOSE(circle.GetRadius(), radius, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_an_area)
	{
		BOOST_CHECK_CLOSE(circle.GetArea(), (M_PI * radius * radius), DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK_CLOSE(circle.GetPerimeter(), (2 * M_PI * 3), DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK(circle.GetOutlineColor() == "000000");
	}
	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK(circle.GetFillColor() == "ffff00");
	}
	BOOST_AUTO_TEST_CASE(has_a_method_of_obtaining_information)
	{
		auto area = M_PI * radius * radius;
		area = round(area * 100) / 100;
		auto perimeter = 2 * M_PI * 3;
		perimeter = round(perimeter * 100) / 100;

		BOOST_CHECK(IsInformationEqual(circle, "Circle", area, perimeter, "000000", "ffff00"));
	}

BOOST_AUTO_TEST_SUITE_END()