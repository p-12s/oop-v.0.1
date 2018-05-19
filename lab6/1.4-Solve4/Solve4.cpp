#include "stdafx.h"
#include "Solve4.h"

using namespace std;

bool IsRootAlreadyFound(EquationRoot4& equationRoot4, const double root)
{
	double* start = equationRoot4.roots;
	double* end = start + equationRoot4.numRoots;
	return find(start, end, root) != end;
}

void AddRootsToDecision(EquationRoot4& equationRoot4,
	const pair<boost::optional<double>, boost::optional<double>>& roots)
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

pair<boost::optional<double>, boost::optional<double>> Solve2(const double a, const double b, const double c)
{
	double D = pow(b, 2) - 4 * a * c;
	if (D == 0)
	{
		return { -b / (2 * a), boost::none };
	}
	if (D > 0)
	{
		return { (-b + sqrt(D)) / (2 * a), (-b - sqrt(D)) / (2 * a) };
	}
	return { boost::none, boost::none };
}

// solution of the cubic equation by the Cardano method
double Solve3(const double a, const double b, const double c)
{
	double roots[3];

	double Q = (pow(a, 2) - 3 * b) / 9;
	double R = (2 * pow(a, 3) - 9 * a * b + 27 * c) / 54;
	double S = pow(Q, 3) - pow(R, 2);
	if (S > 0)
	{
		double phi = acos(R / sqrt(pow(Q, 3))) / 3;
		roots[0] = -2 * sqrt(Q) * cos(phi) - a / 3;
		roots[1] = -2 * sqrt(Q) * cos(phi + 2 * M_PI / 3) - a / 3;
		roots[2] = -2 * sqrt(Q) * cos(phi - 2 * M_PI / 3) - a / 3;
	}
	else
	{
		if (Q > 0)
		{
			double phi = acosh(fabs(R) / sqrt(pow(Q, 3))) / 3;
			roots[0] = -2 * (R >= 0 ? 1 : -1) * sqrt(Q) * cosh(phi) - a / 3;
		}
		else if (Q < 0)
		{
			double phi = asinh(fabs(R) / sqrt(pow(fabs(Q), 3))) / 3;
			roots[0] = -2 * (R >= 0 ? 1 : -1) * sqrt(fabs(Q)) * sinh(phi) - (a / 3);
		}
		else
		{
			roots[0] = -pow(c - pow(a, 3) / 27, 1. / 3) - a / 3;
		}
	}
	return *max_element(begin(roots), end(roots));
}

// solution of the fourth-degree equation by the method of Ferrari
EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (a == 0)
		throw invalid_argument("Argument at supmere degree must not be equal to 0");

	double inv = a;
	a = b / inv;
	b = c / inv;
	c = d / inv;
	d = e / inv;

	// we find one of the roots of the cubic resolvent
	double y = Solve3(-b, a * c - 4 * d, 4 * b * d - pow(a, 2) * d - pow(c, 2));

	double alpha = sqrt(pow(a, 2) / 4 - b + y);
	double beta = sqrt(pow(y, 2) / 4 - d);
	if ((a * y / 2 - c) < 0)
		beta *= -1;

	EquationRoot4 result;
	AddRootsToDecision(result, Solve2(1, a / 2 + alpha, y / 2 + beta));
	AddRootsToDecision(result, Solve2(1, a / 2 - alpha, y / 2 - beta));
	if (result.numRoots == 0)
		throw domain_error("Equation does not have real roots");

	sort(begin(result.roots), begin(result.roots) + result.numRoots);
	return result;
}