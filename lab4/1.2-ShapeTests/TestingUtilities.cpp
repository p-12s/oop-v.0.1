#include "stdafx.h"
#include "TestingUtilities.h"

using namespace std;

void ArePointCoordinatesEqual(const CPoint& point, const double expectedX, const double expectedY)
{
	pair<double, double> coordinates = point.GetCoordinates();
	BOOST_CHECK_CLOSE(coordinates.first, expectedX, DBL_EPSILON);
	BOOST_CHECK_CLOSE(coordinates.second, expectedY, DBL_EPSILON);
}

bool IsInformationEqual(const CShape& chape, const string& existedType,
	const double expectedArea, const double existedPerimether, 
	const string& outlineColor, const string& fillColor)
{
	ostringstream compoundString;
	compoundString << existedType << "\nArea: " << expectedArea <<
		"\nPerimeter: " << existedPerimether <<
		"\nOutline color: " << outlineColor << "\n";
	if (!fillColor.empty())
		compoundString << "Fill color: " << fillColor << "\n";

	return compoundString.str() == chape.ToString();
}