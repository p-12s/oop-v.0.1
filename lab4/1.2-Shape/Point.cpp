#include "stdafx.h"
#include "Point.h"

using namespace std;

CPoint::CPoint(const double x, const double y)
	: m_x(x)
	, m_y(y)
{
}

pair<double, double> CPoint::GetCoordinates() const
{
	return { m_x, m_y };
}

double CPoint::GetDistanceTo(const CPoint& point) const
{
	try
	{
		return sqrt(pow((point.m_x - m_x), 2) + pow((point.m_y - m_y), 2));
	}
	catch (exception const&)
	{
		throw overflow_error("The coordinate value is too large");
	}	
}