#pragma once
#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "../1.2-Shape/Shape.h"

bool ArePointCoordinatesEqual(const CPoint& point, const double expectedX, const double expectedY);

bool CheckEqualOfTwoDoubleNumbers(const double a, const double b);

bool IsInformationEqual(const CShape& chape, const std::string& existedType,
	const double expectedArea, const double existedPerimether, const std::string& existedColor);