#include "stdafx.h"
#include "Triangle.h"

using namespace std;

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, 
	const string& outlineColor, const string& fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CSolidShape("Triangle", outlineColor, fillColor)
{	
}

double CTriangle::GetArea() const
{
	pair<double, double> vertex1 = m_vertex1.GetCoordinates();
	pair<double, double> vertex2 = m_vertex2.GetCoordinates();
	pair<double, double> vertex3 = m_vertex3.GetCoordinates();

	double area = ((vertex1.first - vertex3.first) * (vertex2.second - vertex3.second) -
		(vertex2.first - vertex3.first) * (vertex1.second - vertex3.second)) * 0.5;
	return (area > 0) ? area : (area * -1);
}

double CTriangle::GetPerimeter() const
{
	return m_vertex1.GetDistanceTo(m_vertex2) + 
		m_vertex2.GetDistanceTo(m_vertex3) + 
		m_vertex3.GetDistanceTo(m_vertex1);
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}