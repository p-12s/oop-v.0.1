#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

double GetCoordinateDifference(const double a, const double b)
{
	double difference = a - b;
	return (difference > 0) ? difference : (difference * -1);
}

CRectangle::CRectangle(const CPoint& leftTop, const CPoint& rightBottom,
	const string& outlineColor, const string& fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, CSolidShape("Rectangle", outlineColor, fillColor)
{
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return GetCoordinateDifference(m_leftTop.GetCoordinates().first, m_rightBottom.GetCoordinates().first);
}

double CRectangle::GetHeight() const
{
	return GetCoordinateDifference(m_leftTop.GetCoordinates().second, m_rightBottom.GetCoordinates().second);
}

double CRectangle::GetArea() const
{
	return GetHeight() * GetWidth();
}

double CRectangle::GetPerimeter() const
{
	return (GetWidth() + GetHeight()) * 2;
}