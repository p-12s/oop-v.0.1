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

	return atan2(m_imaginary, m_real);
}

CComplex const operator+(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() + complex2.Re(), complex1.Im() + complex2.Im());
}

CComplex const operator-(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() - complex2.Re(), complex1.Im() - complex2.Im());
}

CComplex const operator*(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() * complex2.Re() - complex1.Im() * complex2.Im(),
		complex1.Im() * complex2.Re() + complex1.Re() * complex2.Im());
}

CComplex const operator/(const CComplex& complex1, const CComplex& complex2)
{
	double denominator = pow(complex2.Re(), 2) + pow(complex2.Im(), 2);
	double real = (complex1.Re() * complex2.Re() + complex1.Im() * complex2.Im()) / denominator;
	double imaginary = (complex2.Re() * complex1.Im() - complex1.Re() * complex2.Im()) / denominator;

	return CComplex(real, imaginary);
}

CComplex const CComplex::operator+() const
{
	return CComplex(m_real, m_imaginary);
}

CComplex const CComplex::operator-() const
{
	return CComplex(-m_real, -m_imaginary);
}

CComplex& CComplex::operator+=(const CComplex& complex)
{
	m_imaginary += complex.m_imaginary;
	m_real += complex.m_real;
	return *this;
}

CComplex& CComplex::operator-=(const CComplex& complex)
{
	m_imaginary -= complex.m_imaginary;
	m_real -= complex.m_real;
	return *this;
}

CComplex& CComplex::operator*=(const CComplex& complex)
{
	return *this = *this * complex;
}

CComplex& CComplex::operator/=(const CComplex& complex)
{
	return *this = *this / complex;
}

bool CComplex::operator==(const CComplex& complex) const
{
	 return fabs(complex.m_imaginary - m_imaginary) < DBL_EPSILON &&
		fabs(complex.m_real - m_real) < DBL_EPSILON;
}

bool CComplex::operator!=(const CComplex& complex) const
{
	return !(complex == *this);
}

istream& operator>>(istream& stream, CComplex& complex)
{
	double real = 0;
	double imaginary = 0;
	if ((stream >> real) &&	(stream >> imaginary) && (stream.get() == 'i'))
	{
		complex = CComplex(real, imaginary);
	}
	else
	{
		stream.setstate(ios_base::failbit);
	}
	return stream;
}

ostream& operator<<(ostream& stream, const CComplex& complex)
{
	stream << complex.Re();
	stream.setf(ios_base::showpos);
	stream << complex.Im() << 'i';
	stream.unsetf(ios_base::showpos);
	return stream;
}