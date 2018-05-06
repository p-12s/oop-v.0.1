#include "stdafx.h"
#include "Circle.h"

using namespace std;

CCircle::CCircle(const CPoint& center, const double radius,
	const string& outlineColor, const string& fillColor)
	: m_center(center)
	, m_radius(radius)
	, CSolidShape("Circle", outlineColor, fillColor)
{
	if (radius < 0.f) throw exception("Radius can not be negative");
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetArea() const
{
	return round(M_PI * pow(m_radius, 2) * 100) / 100;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}