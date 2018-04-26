#pragma once

class CPoint
{
public:
	CPoint(double m_x, double m_y);
	~CPoint() = default;
	//std::string ToString() const;

private:
	double m_x;
	double m_y;
};