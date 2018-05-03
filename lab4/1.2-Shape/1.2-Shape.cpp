#include "stdafx.h"
#include "Point.h"
#include "LineSegment.h"

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
	CPoint startPoint = CPoint(0.0, 0.0);
	CPoint endPoint = CPoint(-10.0, -10.0);
	string color = "ff0000";
	CLineSegment lineSegment = CLineSegment(startPoint, endPoint, color);


	cout << lineSegment.ToString() << endl;

	if (AsStringEqual(lineSegment, "Line segment", 0, lineSegment.GetPerimeter(), color))
		cout << "equal" << endl;
	else
		cout << "none" << endl;
	
    return 0;
}

