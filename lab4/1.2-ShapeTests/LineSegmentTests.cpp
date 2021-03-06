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
	CLineSegment lineSegment;

	LineSegmentFixture()
		: lineSegment(startPoint, endPoint, color)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegmentFixture)

	BOOST_AUTO_TEST_CASE(has_the_start_coordinates)
	{
		CPoint currentStart = lineSegment.GetStartPoint();
		ArePointCoordinatesEqual(currentStart, 0, 0);
	}
	BOOST_AUTO_TEST_CASE(has_the_end_coordinates)
	{
		CPoint currentEnd = lineSegment.GetEndPoint();
		ArePointCoordinatesEqual(currentEnd, -10, -10);
	}
	BOOST_AUTO_TEST_CASE(has_an_area_equal_to_zero)
	{
		BOOST_CHECK_CLOSE(lineSegment.GetArea(), 0, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(can_find_its_length_which_is_equal_to_the_perimeter)
	{
		double length = lineSegment.GetStartPoint().GetDistanceTo(lineSegment.GetEndPoint());
		BOOST_CHECK_CLOSE(length, sqrt(10 * 10 + 10 * 10), DBL_EPSILON);

		double perimeter = lineSegment.GetPerimeter();		
		BOOST_CHECK_CLOSE(perimeter, sqrt(10 * 10 + 10 * 10), DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_a_method_of_obtaining_information)
	{
		BOOST_CHECK(IsInformationEqual(lineSegment, "Line segment", 0, 14.14, "ff0000", ""));
	}
	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK(lineSegment.GetOutlineColor() == "ff0000");
	}

BOOST_AUTO_TEST_SUITE_END()