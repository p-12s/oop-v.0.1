#include "stdafx.h"
#include "../1.2-Shape/CreatorOfShapes.h"
#include "../1.2-Shape/Circle.h"
#include "../1.2-Shape/Triangle.h"
#include "../1.2-Shape/Rectangle.h"
#include "../1.2-Shape/LineSegment.h"

using namespace std;

struct CreatorOfShapesFixture
{
	stringstream input;
	stringstream output;
	CCreatorOfShapes creatorOfShapes;

	CreatorOfShapesFixture()
		: creatorOfShapes()
	{
	}
};


BOOST_FIXTURE_TEST_SUITE(CreatorOfShapes, CreatorOfShapesFixture)

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

BOOST_AUTO_TEST_SUITE_END()