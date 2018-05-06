#include "stdafx.h"
#include "Point.h"
#include "LineSegment.h"
#include "Rectangle.h"

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
	CPoint leftTop = CPoint(0.0, 2.0);
	CPoint rightBottom = CPoint(3.0, 0.0);
	string outlineColor = "ff0011";
	string fillColor = "ffffff";
	CRectangle rectangle = CRectangle(leftTop, rightBottom, outlineColor, fillColor);


	cout << rectangle.ToString() << endl;

	double area = rectangle.GetArea();
	double per = rectangle.GetPerimeter();
	
    return 0;
}

