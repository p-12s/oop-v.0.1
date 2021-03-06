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
	ostringstream output;
	output << m_type << "\nArea: " << (round(GetArea() * 100) / 100) <<
		"\nPerimeter: " << (round(GetPerimeter() * 100) / 100) <<
		"\nOutline color: " << GetOutlineColor() << "\n";
	
	return output.str();
}

string CShape::GetOutlineColor() const
{
	return m_color;
}
