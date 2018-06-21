#pragma once
#include "SolidShape.h"
#include "Point.h"

class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint& center, const double radius,
		const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
};