#pragma once
#include "stdafx.h"

class CComplex
{
public:
	CComplex(double real = 0, double imaginary = 0);
	~CComplex() = default;
	double Re() const;
	double Im() const;	
	double GetMagnitude() const; // модуль	
	double GetArgument() const;

	CComplex const operator+(const CComplex& complex) const;
	CComplex const operator-(const CComplex& complex) const;
	CComplex const operator*(const CComplex& complex) const;
	CComplex const operator/(const CComplex& complex) const;
	CComplex const operator+() const;
	CComplex const operator-() const;
	CComplex& operator+=(const CComplex& complex);
	CComplex& operator-=(const CComplex& complex);

private:
	double m_real;
	double m_imaginary;
};

CComplex const operator+(const double real, const CComplex& complex);
CComplex const operator-(double real, const CComplex& complex);
CComplex const operator*(double real, const CComplex& complex);
CComplex const operator/(double real, const CComplex& complex);