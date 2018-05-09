#include "stdafx.h"
#include "CreatorOfShapes.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "LineSegment.h"

using namespace std;
using namespace placeholders;

bool IsHexColor(const string& color)
{
	if (color.length() != 6)
		return false;

	auto isHexChar = [](char x) {
		return x >= '0' && x <= '9' || x >= 'a' && x <= 'f';
	};
	return all_of(color.begin(), color.end(), isHexChar);
}

CPoint CreatePoint(istringstream& strm)
{
	double x, y;
	if (strm >> x >> y)
	{
		return CPoint(x, y);
	}
	throw exception("Input error when creating a point");
}

string ReadColor(istringstream& strm)
{
	string color;
	if (strm >> color)
	{
		if (IsHexColor(color)) return color;
	}
	throw exception("Input error when reading a color");
}

double ReadLength(istringstream& strm)
{
	double length;
	if (strm >> length)
	{
		if (length > 0) return length;
	}
	throw exception("Input error when reading a length");
}

CCreatorOfShapes::CCreatorOfShapes()
	: m_actionMap({
		{ "LineSegment", bind(&CCreatorOfShapes::CreateLineSegment, this, _1) },
		{ "Rectangle", bind(&CCreatorOfShapes::CreateRectangle, this, _1) },
		{ "Circle", bind(&CCreatorOfShapes::CreateCircle, this, _1) },
		{ "Triangle", bind(&CCreatorOfShapes::CreateTriangle, this, _1) }
})
{	
}

shared_ptr<IShape> CCreatorOfShapes::CreateShapesFromString(const string& commandLine) const
{
	string command = commandLine;// TODO избавиться от избыточного преобразования
	istringstream strm(command);
	string shapeType;
	strm >> shapeType;
	auto it = m_actionMap.find(shapeType);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	throw exception("Unknown command");
}


shared_ptr<IShape> CCreatorOfShapes::CreateLineSegment(istringstream& strm) const
{
	CPoint start = CreatePoint(strm);
	CPoint end = CreatePoint(strm);
	string color = ReadColor(strm);

	return make_shared<CLineSegment>(start, end, color);
}

shared_ptr<IShape> CCreatorOfShapes::CreateRectangle(istringstream& strm) const
{
	CPoint leftTop = CreatePoint(strm);
	CPoint rightBottom = CreatePoint(strm);
	string outlineColor = ReadColor(strm);
	string fillColor = ReadColor(strm);
	return make_shared<CRectangle>(leftTop, rightBottom, outlineColor, fillColor);
}

shared_ptr<IShape> CCreatorOfShapes::CreateCircle(istringstream& strm) const
{
	CPoint center = CreatePoint(strm);
	double radius = ReadLength(strm);
	string outlineColor = ReadColor(strm);
	string fillColor = ReadColor(strm);
	return make_shared<CCircle>(center, radius, outlineColor, fillColor);
}

shared_ptr<IShape> CCreatorOfShapes::CreateTriangle(istringstream& strm) const
{
	CPoint vertex1 = CreatePoint(strm);
	CPoint vertex2 = CreatePoint(strm);
	CPoint vertex3 = CreatePoint(strm);
	string outlineColor = ReadColor(strm);
	string fillColor = ReadColor(strm);
	return make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}