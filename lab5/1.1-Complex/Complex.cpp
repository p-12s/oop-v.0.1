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

double CComplex::GetMagnitude() const
{
	return 0.0;
}

double CComplex::GetArgument() const
{
	return 0.0;
}