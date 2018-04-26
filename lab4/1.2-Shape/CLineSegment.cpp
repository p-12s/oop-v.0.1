#include "stdafx.h"
#include "LineSegment.h"

using namespace std;

CLineSegment::CLineSegment(const CPoint& start, const CPoint& end, const std::string& color)
	: CShape("Line segment", color)
	, m_start(start)
	, m_end(end)
{
}

CLineSegment::~CLineSegment()
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return 0;//add 
}
