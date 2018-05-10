#include "stdafx.h"
#include "Complex.h"

using namespace std;

CComplex::CComplex(double real, double imaginary)
	: m_real(real)
	, m_imaginary(imaginary)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_imaginary;
}

double CComplex::GetMagnitude() const // модуль
{
	return sqrt(pow(m_real, 2) + pow(m_imaginary, 2));
}

double CComplex::GetArgument() const
{
	if (m_real == 0 && m_imaginary == 0)
		return 0;

	if (m_real == 0 && m_imaginary != 0)
		return DBL_MAX;

	double argument;
	if (m_real > 0)
	{
		argument = atan(m_imaginary / m_real);
	} 
	else if(m_real < 0 && m_imaginary >= 0)
	{
		argument = atan(m_imaginary / m_real) + M_PI;
	} 
	else
	{
		argument = atan(m_imaginary / m_real) - M_PI;
	}

	return argument;
}

CComplex const CComplex::operator+(const CComplex& complex) const
{
	return CComplex(m_real + complex.m_real, m_imaginary + complex.m_imaginary);
}

CComplex const operator+(const double real, const CComplex& complex)
{
	return CComplex(real) + complex;
}

CComplex const CComplex::operator-(const CComplex& complex) const
{
	return CComplex(m_real - complex.m_real, m_imaginary - complex.m_imaginary);
}

CComplex const operator-(double real, const CComplex& complex)
{
	return CComplex(real) - complex;
}
