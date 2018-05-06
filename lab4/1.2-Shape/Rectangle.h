#pragma once
#include "SolidShape.h"
#include "Point.h"

class CRectangle : public CSolidShape
{
public:
	CRectangle(const CPoint& leftTop, const CPoint& rightBottom,
		const std::string& outlineColor, const std::string& fillColor);
	~CRectangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};