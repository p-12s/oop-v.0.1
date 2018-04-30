#include "stdafx.h"
#include "TestingUtilities.h"

using namespace std;

bool CheckEqualOfTwoDoubleNumbers(const double a, const double b)
{
	return (round(a * 100) / 100) == (round(b * 100) / 100);
}
//TODO по ссылке
bool ArePointCoordinatesEqual(const CPoint point, const double expectedX, const double expectedY)
{
	pair<double, double> pointCoordinates = point.GetCoordinates();
	return CheckEqualOfTwoDoubleNumbers(pointCoordinates.first, expectedX) && 
			CheckEqualOfTwoDoubleNumbers(pointCoordinates.second, expectedY);
}

bool IsInformationAsStringEqual(CShape chape)
{
	
}

