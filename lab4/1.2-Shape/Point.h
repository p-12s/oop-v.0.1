#pragma once

class CPoint
{
public:
	CPoint(const double x, const double y);
	std::pair<double, double> GetCoordinates() const;
	double GetDistanceTo(const CPoint& point) const;

private:
	double m_x = 0;
	double m_y = 0;
};