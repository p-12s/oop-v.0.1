#include "stdafx.h"
#include "LineSegment.h"

using namespace std;

CLineSegment::CLineSegment()
{
}

CLineSegment::CLineSegment(const CPoint& start, const CPoint& end, const string& color)
	: m_start(start)
	, m_end(end)
	, CShape("Line segment", color)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return m_start.GetDistanceTo(m_end);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_end;
}
