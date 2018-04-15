#pragma once
#include "IShape.h"

class CShape
{
public:
	CShape(const std::string& m_type, const std::string& m_color);
	~CShape() = default;
	double GetArea() const;// override = 0
	double GetPerimether() const;// override = 0
	std::string ToString() const;// override
	std::string GetOutlineColor() const;// override

private:
	std::string m_color;
	std::string m_type;
};