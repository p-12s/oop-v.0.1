#include "stdafx.h"
#include "Shape.h"

using namespace std;

CShape::CShape(const string& type, const string& color)
	: m_type(type)
	, m_color(color)
{	
}

string CShape::ToString() const
{
	return "shapeName";
}

string CShape::GetOutlineColor() const
{
	return m_color;
}
