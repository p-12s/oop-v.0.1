#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "../1.2-Shape/Rectangle.h"
#include "TestingUtilities.h"

using namespace std;

struct RectangleFixture
{
	CPoint leftTop = CPoint(0.0, 2.0);
	CPoint rightBottom = CPoint(3.0, 0.0);
	string outlineColor = "ff0012";
	string fillColor = "ffff00";
	CRectangle rectangle;

	RectangleFixture()
		: rectangle(leftTop, rightBottom, outlineColor, fillColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture)

	BOOST_AUTO_TEST_CASE(has_the_coordinates_of_two_opposite_angles)
	{
		ArePointCoordinatesEqual(rectangle.GetLeftTop(), 0, 2);
		ArePointCoordinatesEqual(rectangle.GetRightBottom(), 3, 0);
	}
	BOOST_AUTO_TEST_CASE(has_a_width)
	{
		BOOST_CHECK_CLOSE(rectangle.GetWidth(), 3, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_CLOSE(rectangle.GetHeight(), 2, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_an_area)
	{
		BOOST_CHECK_CLOSE(rectangle.GetArea(), 6, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK_CLOSE(rectangle.GetPerimeter(), 10, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK(rectangle.GetOutlineColor() == "ff0012");
	}
	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK(rectangle.GetFillColor() == "ffff00");
	}
	BOOST_AUTO_TEST_CASE(has_a_method_of_obtaining_information)
	{
		BOOST_CHECK(IsInformationEqual(rectangle, "Rectangle", 6, 10, "ff0012", "ffff00"));
	}

BOOST_AUTO_TEST_SUITE_END()