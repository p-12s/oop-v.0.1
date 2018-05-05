#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

CRectangle::CRectangle(const CPoint& leftTop, const CPoint& rightBottom,
	const std::string& outlineColor, const std::string& fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, CSolidShape("Rectangle", outlineColor, fillColor)
{
}

double CRectangle::GetArea() const
{
	/*pair<double, double> vertex1 = m_vertex1.GetCoordinates();
	pair<double, double> vertex2 = m_vertex2.GetCoordinates();
	pair<double, double> vertex3 = m_vertex3.GetCoordinates();

	double area = ((vertex1.first - vertex3.first) * (vertex2.second - vertex3.second) -
		(vertex2.first - vertex3.first) * (vertex1.second - vertex3.second)) * 0.5;*/
	return 0;
}

double CRectangle::GetPerimeter() const
{
	/*return m_vertex1.GetDistanceTo(m_vertex2) +
		m_vertex2.GetDistanceTo(m_vertex3) +
		m_vertex3.GetDistanceTo(m_vertex1);*/
	return 0;
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
	return 0;
}

double CRectangle::GetHeight() const
{
	return 0;
}