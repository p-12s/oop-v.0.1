#pragma once
#include "stdafx.h"

// TODO описание перенести в друой файл
struct EquationRoot4
{
	double numRoots;
	double roots[4];
};

class CSolve4
{
public:
	CSolve4(double a, double b = 0, double c = 0, double d = 0, double e = 0);
	EquationRoot4& GetRootsOfEquation() const;

private:
	double m_a, m_b, m_c, m_d, m_e;
};