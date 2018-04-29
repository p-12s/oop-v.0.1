#pragma once
#include "stdafx.h"

class IShape
{
public:
	virtual ~IShape(); // if the base class is intended for polymorphic use, then its destructor must be declared virtual
	virtual double GetArea() const = 0; // abstract base class
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual std::string GetOutlineColor() const = 0;
};

inline IShape::~IShape()
{
}
