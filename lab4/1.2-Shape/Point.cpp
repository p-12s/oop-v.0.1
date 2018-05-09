#include "stdafx.h"
#include "Point.h"

using namespace std;

CPoint::CPoint()
{
}

CPoint::CPoint(const double x, const double y)
	: m_x(x)
	, m_y(y)
{
}

pair<double, double> CPoint::GetCoordinates() const
{
	return { m_x, m_y };
}

double CPoint::GetDistanceTo(const CPoint point) const
{
	try
	{
		double distance = sqrt(pow((point.m_x - m_x), 2) + pow((point.m_y - m_y), 2));
		return round(distance * 100) / 100;
	}
	catch (exception const&)
	{
		throw overflow_error("The coordinate value is too large");
	}	
}

void CPoint::SetXValue(const double x)
{
	m_x = x;
}

void CPoint::SetYValue(const double y)
{
	m_y = y;
}