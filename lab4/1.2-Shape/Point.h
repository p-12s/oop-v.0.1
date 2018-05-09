#pragma once

class CPoint
{
public:
	CPoint();//TODO избавиться от дефолтного конструктора
	CPoint(const double x, const double y);
	~CPoint() = default;
	std::pair<double, double> GetCoordinates() const;
	double GetDistanceTo(const CPoint point) const;
	void SetXValue(const double x);
	void SetYValue(const double y);

private:
	double m_x = 0;
	double m_y = 0;
};