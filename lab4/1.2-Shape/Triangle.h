#pragma once
#include "SolidShape.h"
#include "Point.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3, const std::string& outlineColor, const std::string& fillColor);
	~CTriangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3; // TODO мб вектор использовать, лучше что-то другое
};