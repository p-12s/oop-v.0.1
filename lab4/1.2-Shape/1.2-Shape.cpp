#include "stdafx.h"
#include "Point.h"
#include "LineSegment.h"
#include "Circle.h"

using namespace std;

bool AsStringEqual(const CShape& chape, const string& existedType,
	const double expectedArea, const double existedPerimether, const string& existedColor)
{
	ostringstream compoundString;
	compoundString << existedType << "\nArea: " << expectedArea <<
		"\nPerimeter: " << existedPerimether <<
		"\nOutline color: " << existedColor << "\n";

	string info = chape.ToString();
	string my = compoundString.str();

	return my == info;
}

int main()
{
	CPoint center = CPoint(0.0, 0.0);
	double radius = 3;
	string outlineColor = "ff0011";
	string fillColor = "ffffff";
	CCircle circle = CCircle(center, radius, outlineColor, fillColor);


	cout << circle.ToString() << endl;

	double area = circle.GetArea();
	double per = circle.GetPerimeter();
	
    return 0;
}

