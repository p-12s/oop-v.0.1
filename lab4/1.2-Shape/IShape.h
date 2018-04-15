#pragma once
#include "stdafx.h"

class IShape
{
public:
	virtual ~IShape();
	virtual double GetArea() const = 0; //abstract base class
	virtual double GetPerimether() const = 0;
	virtual std::string ToString() const = 0;
	virtual std::string GetOutlineColor() const = 0;
};