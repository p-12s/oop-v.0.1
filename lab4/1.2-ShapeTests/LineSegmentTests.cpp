#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "../1.2-Shape/LineSegment.h"

using namespace std;

struct LineSegmentFixture
{
	CLineSegment lineSegment = CLineSegment(CPoint(0, 0), CPoint(-10, -10), "ff0000");

	LineSegmentFixture()
	: lineSegment()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegmentFixture)
	BOOST_AUTO_TEST_CASE(has_start_coordinates)
	{
		BOOST_CHECK(true);
	}
// ����� ������ � �����
// ����� �������, ������� ����� ���������, ������� ����� �����
// ����� ���� �������
// ����� ���������� ������
// ����� �������� �����


BOOST_AUTO_TEST_SUITE_END()