#pragma once
#include "ISolidShape.h"
#include "Shape.h"

class CSolidShape : public CShape, public ISolidShape // TODO как избавитьс€ от ромбовидного наследовани€?
{
public:
	CSolidShape(const std::string& type, const std::string& outlineColor, const std::string& fillColor);
	~CSolidShape() = default;
	double GetArea() const override = 0;
	double GetPerimeter() const override = 0;
	std::string GetFillColor() const override;
	std::string GetOutlineColor() const override;
	std::string ToString() const override;

private:
	std::string m_fillColor;
};