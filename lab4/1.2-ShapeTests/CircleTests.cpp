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
		BOOST_CHECK(ArePointCoordinatesEqual(circle.GetCenter(), 0.0, 0.0));
	}
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(circle.GetRadius(), 3));
	}
	BOOST_AUTO_TEST_CASE(has_an_area)
	{
		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(circle.GetArea(), 28.27));
	}
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(circle.GetPerimeter(), 18.85));
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
		BOOST_CHECK(IsInformationEqual(circle, "Circle", 28.27, 18.85, "000000", "ffff00"));
	}

BOOST_AUTO_TEST_SUITE_END()