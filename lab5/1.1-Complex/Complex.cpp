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

double CComplex::GetMagnitude() const // возвращает модуль комплексного числа
{
	return sqrt(pow(m_real, 2) + pow(m_imaginary, 2));
}

double CComplex::GetArgument() const // возвращает аргумент комплексного числа
{
	/*double argument = 1.0 / atan(m_imaginary / m_real);
	if (m_real < 0.0 && m_imaginary > 0.0)
	{
		return M_PI + argument;
	}
	if (m_real < 0.0 && m_imaginary < 0.0)
	{
		return -M_PI + argument;
	}
	return argument;*/
	return 0;
}