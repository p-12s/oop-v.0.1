#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape(const std::string& type, const std::string& color);
	~CShape() = default;
	double GetArea() const override = 0;
	double GetPerimeter() const override = 0;
	std::string ToString() const override;
	std::string GetOutlineColor() const override; 

private:
	std::string m_color;
	std::string m_type;
};