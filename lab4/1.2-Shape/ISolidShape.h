#pragma once
#include "IShape.h"

class ISolidShape : public virtual IShape
{
public:
	virtual std::string GetFillColor() const = 0;
};
