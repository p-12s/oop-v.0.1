#include "stdafx.h"
#include "Solve4.h"

using namespace std;

CSolve4::CSolve4(double a, double b, double c, double d, double e)
	: m_a(a)
	, m_b(b)
	, m_c(c)
	, m_d(d)
	, m_e(e)
{
	if (a == 0) throw invalid_argument("The coefficient of x^4 can not be 0");
}

EquationRoot4& CSolve4::GetRootsOfEquation() const
{
	return *new EquationRoot4;
}