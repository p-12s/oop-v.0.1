#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape(const std::string& type, const std::string& color);
	double GetArea() const override = 0;
	double GetPerimeter() const override = 0;
	std::string ToString() const override;
	std::string GetOutlineColor() const override; 

private:
	std::string m_type;
	std::string m_color;
};