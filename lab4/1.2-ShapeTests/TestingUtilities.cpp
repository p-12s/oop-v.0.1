#include "stdafx.h"
#include "TestingUtilities.h"

using namespace std;

bool CheckEqualOfTwoDoubleNumbers(const double a, const double b)
{
	try
	{
		return (round(a * 100) / 100) == (round(b * 100) / 100);
	}
	catch (exception const&)
	{
		throw overflow_error("The checked numbers is too large");
	}	
}

bool ArePointCoordinatesEqual(const CPoint& point, const double expectedX, const double expectedY)
{
	pair<double, double> pointCoordinates = point.GetCoordinates();
	return CheckEqualOfTwoDoubleNumbers(pointCoordinates.first, expectedX) && 
			CheckEqualOfTwoDoubleNumbers(pointCoordinates.second, expectedY);
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