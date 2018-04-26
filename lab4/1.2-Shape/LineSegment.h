#pragma once
#include "Shape.h"
#include "Point.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(const CPoint& start, const CPoint& end, const std::string& color);
	~CLineSegment();
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const;
	std::string GetOutlineColor() const;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
	CPoint m_start;
	CPoint m_end;
};
