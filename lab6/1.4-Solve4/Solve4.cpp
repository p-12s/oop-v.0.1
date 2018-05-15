#include "stdafx.h"
#include "Solve4.h"

using namespace std;

bool IsRootAlreadyFound(EquationRoot4& equationRoot4, const double root) // почему тут не работает const EquationRoot4& equationRoot4
{
	double* start = equationRoot4.roots;
	double* end = start + equationRoot4.numRoots;
	return find(start, end, root) != end;
}

// решение кубического уравнени€ методом  ардано
double Solve3(double a, double b, double c) // сложно
{
	double roots[3];

	double q = (a * a - 3.0 * b) / 9.0;
	double r = (2.0 * a * a * a - 9.0 * a * b + 27.0 * c) / 54.0;
	double s = pow(q, 3) - pow(r, 2);

	if (s > 0)
	{
		double t = acos(r / sqrt(pow(q, 3))) / 3.0;
		roots[0] = -2 * sqrt(q) * cos(t) - a / 3.0; // а если тут q отрицательное?
		roots[1] = -2 * sqrt(q) * cos(t + 2 * M_PI / 3.0) - a / 3.0;
		roots[2] = -2 * sqrt(q) * cos(t - 2 * M_PI / 3.0) - a / 3.0;
	}
	else if (s < 0)
	{
		if (q > 0)
		{
			double t = acosh(abs(r) / sqrt(pow(q, 3))) / 3.0;
			roots[0] = -2 * ((r > 0) ? 1 : ((r < 0) ? -1 : 0)) * sqrt(q) * cosh(t) - a / 3.0;
		}
		if (q < 0)
		{
			double t = acosh(abs(r) / sqrt(pow(abs(q), 3))) / 3.0;
			roots[0] = -2 * ((r > 0) ? 1 : ((r < 0) ? -1 : 0)) * sqrt(q) * sinh(t) - a / 3.0;
		}
		if (q = 0)
		{
			roots[0] = -pow((c - pow(a, 3) / 27), 1 / 3.0) - a / 3.0;
		}
	}
	else
	{
		roots[0] = -2 * pow(r, 1 / 3.0) - a / 3.0;
		roots[1] = pow(r, 1 / 3.0) - a / 3.0;
	}
	sort(rbegin(roots), rend(roots));
	return roots[0];
}

pair<boost::optional<double>, boost::optional<double>> Solve2(double a, double b, double c)
{
	double D = b * b - 4 * a * c;
	if (D == 0)
	{
		return {-b / (2 * a), boost::none};
	}
	if (D > 0)
	{
		return {(-b + sqrt(D)) / (2 * a), (-b - sqrt(D)) / (2 * a)};
	}
	return {boost::none, boost::none};
}


void AddRootsToEquation(EquationRoot4& equationRoot4, 
	pair<boost::optional<double>, boost::optional<double>> const& roots)// почему тут константна€ ссылка, сделать парамтер константным, а ссылку - нет
{
	if (roots.first)
	{
		if (!IsRootAlreadyFound(equationRoot4, static_cast<double>(*roots.first)))
		{
			equationRoot4.roots[equationRoot4.numRoots] = roots.first.get();
			equationRoot4.numRoots++;
		}		
	}
	if (roots.second)
	{
		if (!IsRootAlreadyFound(equationRoot4, static_cast<double>(*roots.second)))
		{
			equationRoot4.roots[equationRoot4.numRoots] = roots.second.get();
			equationRoot4.numRoots++;
		}		
	}
}

CSolve4::CSolve4(double a, double b, double c, double d, double e)
	: m_a(a)
	, m_b(b)
	, m_c(c)
	, m_d(d)
	, m_e(e)
{
	if (a == 0) throw invalid_argument("The coefficient of x^4 can not be 0");
}

EquationRoot4 CSolve4::GetRootsOfEquation() const
{
	EquationRoot4 answer;
	answer.numRoots = 0;

	// приведем к виду, пригодному дл€ решени€ методом ‘еррари
	double A = m_b / m_a;
	double B = m_c / m_a;
	double C = m_d / m_a;
	double D = m_e / m_a;

	// коэф. кубической резольвенты, начина€ с y^2 (y^3 без коэф.)
	double y0 = Solve3(-B, (A * C - 4 * D), (A * A * D + 4 * B * D - C * C));
	/*
	Ёто уравнение, имеет три корн€, но дл€ метода ‘еррари 
	требуетс€ найти только один вещественный корень этого уравнени€. 
	ќн всегда существует, поскольку кубическа€ парабола как минимум один раз пересекаетс€ с осью абсцисс. 
	ѕока будем считать, что этот корень найден и равен y0
	 */
	
	double alpha = sqrt(A * A / 4 - B + y0); // переименовать на y
	double beta = sqrt(y0 * y0 / 4 - D);
	if ((A * y0 / 2 - C) < 0)
	{
		beta *= -1;
	}
	AddRootsToEquation(answer, Solve2(1, A / 2 + alpha, y0 / 2 + beta));
	AddRootsToEquation(answer, Solve2(1, A / 2 - alpha, y0 / 2 - beta));
	
	sort(begin(answer.roots), begin(answer.roots) + answer.numRoots);
	try
	{
		if (answer.numRoots == 0)
		{
			throw domain_error("Equation does not have of real roots");
		}
	}
	catch (domain_error)
	{
		cout << "Equation does not have of real roots" << endl;
	}
	return answer;
}



