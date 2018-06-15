#pragma once
#include "stdafx.h"

class CComplex
{
public:
	CComplex(double real = 0, double imaginary = 0);
	double Re() const;
	double Im() const;	
	double GetMagnitude() const; // модуль	
	double GetArgument() const;

	CComplex const operator-(const CComplex& complex) const;
	CComplex const operator*(const CComplex& complex) const;
	CComplex const operator/(const CComplex& complex) const;
	CComplex const operator+() const;
	CComplex const operator-() const;
	CComplex& operator+=(const CComplex& complex);
	CComplex& operator-=(const CComplex& complex);
	
	CComplex& operator*=(const CComplex& complex);
	CComplex& operator/=(const CComplex& complex);
	bool operator==(const CComplex& complex) const;
	bool operator!=(const CComplex& complex) const;

private:
	double m_real;
	double m_imaginary;
};

CComplex const operator+(const CComplex& complex1, const CComplex& complex2);
CComplex const operator-(double real, const CComplex& complex);
CComplex const operator*(double real, const CComplex& complex);
CComplex const operator/(double real, const CComplex& complex);
bool operator==(double real, const CComplex& complex);
bool operator!=(double real, const CComplex& complex2);
std::istream& operator>>(std::istream& stream, CComplex& complex);
std::ostream& operator<<(std::ostream& stream, const CComplex& complex);