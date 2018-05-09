#pragma once
#include "stdafx.h"
#include "../1.2-Shape/Point.h"
#include "../1.2-Shape/Shape.h"

void ArePointCoordinatesEqual(const CPoint& point, const double expectedX, const double expectedY);

bool IsInformationEqual(const CShape& chape, const std::string& existedType,
	const double expectedArea, const double existedPerimether,
	const std::string& outlineColor, const std::string& fillColor);