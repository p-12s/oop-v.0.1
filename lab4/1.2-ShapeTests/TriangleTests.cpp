#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "../1.2-Shape/Triangle.h"
#include "TestingUtilities.h"

using namespace std;

struct TriangleFixture
{
	CPoint vertex1 = CPoint(0.0, 0.0);
	CPoint vertex2 = CPoint(0.0, 2.0);
	CPoint vertex3 = CPoint(2.0, 0.0);
	string outlineColor = "ff0011";
	string fillColor = "ffffff";
	CTriangle triangle;

	TriangleFixture()
		: triangle(vertex1, vertex2, vertex3, outlineColor, fillColor)
	{		
	}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, TriangleFixture)

	BOOST_AUTO_TEST_CASE(has_the_coordinates_of_3_vertexes)
	{
		BOOST_CHECK(ArePointCoordinatesEqual(triangle.GetVertex1(), 0.0, 0.0));
		BOOST_CHECK(ArePointCoordinatesEqual(triangle.GetVertex2(), 0.0, 2.0));
		BOOST_CHECK(ArePointCoordinatesEqual(triangle.GetVertex3(), 2.0, 0.0));
	}
	BOOST_AUTO_TEST_CASE(has_an_area)
	{
		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(triangle.GetArea(), 2));
	}
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(triangle.GetPerimeter(), 6.83));
	}
	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK(triangle.GetOutlineColor() == "ff0011");
	}
	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK(triangle.GetFillColor() == "ffffff");
	}
	BOOST_AUTO_TEST_CASE(has_a_method_of_obtaining_information)
	{
		BOOST_CHECK(IsInformationEqual(triangle, "Triangle", 2, 6.83, "ff0011", "ffffff"));
	}

BOOST_AUTO_TEST_SUITE_END()