#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "../1.2-Shape/LineSegment.h"
#include "TestingUtilities.h"

using namespace std;

struct LineSegmentFixture
{
	CPoint startPoint = CPoint(0.0, 0.0);
	CPoint endPoint = CPoint(-10.0, -10.0);
	string color = "ff0000";
	CLineSegment lineSegment = CLineSegment(startPoint, endPoint, color);

	LineSegmentFixture()
	: lineSegment()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegmentFixture)
	// имеет начало и конец
	BOOST_AUTO_TEST_CASE(has_a_method_of_obtaining_information)
	{
		BOOST_CHECK(lineSegment.ToString() == "Line segment");
	}

	BOOST_AUTO_TEST_CASE(has_the_start_coordinates)
	{
		CPoint currentStart = lineSegment.GetStartPoint();
		BOOST_CHECK(ArePointCoordinatesEqual(currentStart, startPoint.GetCoordinates().first, startPoint.GetCoordinates().second));
	}
	/*BOOST_AUTO_TEST_CASE(has_end_coordinates)
	{
		CPoint currentEnd = lineSegment.GetEndPoint();
		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(currentEnd.GetCoordinates().first, 0.0));
		BOOST_CHECK(ArePointCoordinatesEqual(currentEnd, endPoint.GetCoordinates().first, endPoint.GetCoordinates().second));
	}*/
	// имеет площадь, которая равна периметру, которая равна длине
	BOOST_AUTO_TEST_CASE(can_find_its_length_which_is_equal_to_the_perimeter)
	{
		double length = lineSegment.GetStartPoint().GetDistanceTo(lineSegment.GetEndPoint());
		double area = lineSegment.GetArea();
		double perimeter = lineSegment.GetPerimeter();

		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(length, area));
		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(length, perimeter));
	}	
	BOOST_AUTO_TEST_CASE(has_an_area_equal_to_zero)
	{
		BOOST_CHECK(CheckEqualOfTwoDoubleNumbers(lineSegment.GetArea(), 0.0));
	}
// имеет цвет обводки
	/*BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK(lineSegment.GetOutlineColor() == color);
	}*/

BOOST_AUTO_TEST_SUITE_END()