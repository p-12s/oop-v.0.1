#pragma once
#include "Shape.h"
#include "Point.h"

class CLineSegment : public CShape
{
public:
	CLineSegment();
	CLineSegment(const CPoint& start, const CPoint& end, const std::string& color);
	~CLineSegment() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_start;
	CPoint m_end;
};
