#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "../1.2-Shape/LineSegment.h"

using namespace std;

struct LineSegmentFixture
{
	CLineSegment lineSegment;
	const CPoint startPoint = CPoint(0, 0);
	const CPoint endPoint = CPoint(-10, -10);
	const string color = "ff0000";

	LineSegmentFixture()
		: lineSegment(startPoint, endPoint, color)
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