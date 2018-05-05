#include "stdafx.h"
#include "SolidShape.h"

using namespace std;

CSolidShape::CSolidShape(const string& type, const string& outlineColor, const string& fillColor)
	: CShape(type, outlineColor)
	, m_fillColor(fillColor)
{
}

string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

string CSolidShape::ToString() const
{
	return CShape::ToString() + "\nFill color: " + m_fillColor + "\n";
}
