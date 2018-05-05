#pragma once
#include "IShape.h"

class ISolidShape : public virtual IShape
{
public:
	virtual std::string GetFillColor() const = 0;//TODO нужно ли тут приравнивать к нулю? это же стока, а не инт
};
