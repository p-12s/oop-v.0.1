#pragma once
#include "stdafx.h"

struct EquationRoot4
{
	size_t numRoots = 0;
	double roots[4];
};

EquationRoot4 Solve4(double a, double b, double c, double d, double e);
double Solve3(double a, double b, double c);
std::pair<boost::optional<double>, boost::optional<double>> Solve2(double a, double b, double c);