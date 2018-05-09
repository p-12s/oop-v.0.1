#include "stdafx.h"
#include "../1.2-Shape/CreatorOfShapes.h"

using namespace std;

struct CreatorOfShapesFixture
{
	CCreatorOfShapes creatorOfShapes;

	CreatorOfShapesFixture()
		: creatorOfShapes()
	{
	}
};


BOOST_FIXTURE_TEST_SUITE(CreatorOfShapes, CreatorOfShapesFixture)

	BOOST_AUTO_TEST_CASE(can_handle_an_unknown_command)
	{
		string input = "LineSegmentSuper 12.5 12.5 -12.5 -12.5 ff0000";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input), exception);
	}
	BOOST_AUTO_TEST_CASE(can_create_line_segment)
	{
		string input = "LineSegment 12.5 12.5 -12.5 -12.5 ff0000";
		BOOST_CHECK_NO_THROW(creatorOfShapes.CreateShapesFromString(input));
	}
	BOOST_AUTO_TEST_CASE(can_recognize_invalid_string_when_creating_line_segment)
	{
		string input = "LineSegment ff0000 12.5 12.5 -12.5 -12.5";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input), exception);

		string input2 = "LineSegment 12.5 12.5 -12.5 -12.5";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input2), exception);

		string input3 = "LineSegment 12.5 12.5 -12.5 -12.5 -ff0000";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input3), exception);

		string input4 = "LineSegment 12.5 12.5 -12.5 -12.5 ff000m";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input4), exception);

		string input5 = "LineSegment 12.5 12.5 -12.5 -12.5 ff00000";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input5), exception);

		string input6 = "LineSegment 12.5 12.5 -12.5 ff0000";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input6), exception);
	}

	BOOST_AUTO_TEST_CASE(can_create_rectangle)
	{
		string input = "Rectangle 1.0 -1.0 12.5 36.5 000000 ffffff";
		BOOST_CHECK_NO_THROW(creatorOfShapes.CreateShapesFromString(input));
	}
	BOOST_AUTO_TEST_CASE(can_recognize_invalid_string_when_creating_rectangle)
	{
		string input = "Rectangle 1.0 -1.0 12.5 36.5 3600.0 000000 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input), exception);

		string input2 = "Rectangle 1.0 -1.0 12.5 000000 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input2), exception);

		string input3 = "Rectangle 1.0 -1.0 12.5 36.5 0000m0 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input3), exception);

		string input4 = "Rectangle 1.0 -1.0 12.5 36.5 000000 ffnfff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input4), exception);

		string input5 = "Rectangle 1.0 12.5 36.5 000000 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input5), exception);
	}

	BOOST_AUTO_TEST_CASE(can_create_circle)
	{
		string input = "Circle 1.0 -1.0 12.4 000000 ffffff";
		BOOST_CHECK_NO_THROW(creatorOfShapes.CreateShapesFromString(input));
	}
	BOOST_AUTO_TEST_CASE(can_recognize_invalid_string_when_creating_circle)
	{
		string input = "Circle 1.0 -1.0 000000 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input), exception);

		string input2 = "Circle 1.0 -1.0 12.4 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input2), exception);

		string input3 = "Circle 1.0 000000 -1.0 12.4 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input3), exception);
	}

	BOOST_AUTO_TEST_CASE(can_create_triangle)
	{
		string input = "Triangle 1.0 -1.0 12.4 8.5 16.8 32.2 000000 ffffff";
		BOOST_CHECK_NO_THROW(creatorOfShapes.CreateShapesFromString(input));
	}
	BOOST_AUTO_TEST_CASE(can_recognize_invalid_string_when_creating_triangle)
	{
		string input = "Triangle 1.0 -1.0 12.4 8.5 16.8 32.2 12.2 000000 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input), exception);

		string input2 = "Triangle 1.0 -1.0 12.4 8.5 16.8 000000 ffffff";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input2), exception);

		string input3 = "Triangle 1.0 -1.0 12.4 8.5 16.8 32.2 000000";
		BOOST_CHECK_THROW(creatorOfShapes.CreateShapesFromString(input3), exception);
	}

BOOST_AUTO_TEST_SUITE_END()