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

CComplex const operator+(const CComplex& complex1, const CComplex& complex2)
{
	return CComplex(complex1.Re() + complex2.Re(), complex1.Im() + complex2.Im());
}

CComplex const CComplex::operator-(const CComplex& complex) const
{
	return CComplex(m_real - complex.m_real, m_imaginary - complex.m_imaginary);
}

CComplex const operator-(double real, const CComplex& complex)
{
	return CComplex(real) - complex;
}

CComplex const CComplex::operator*(const CComplex& complex) const
{
	return CComplex(m_real * complex.m_real - m_imaginary * complex.m_imaginary,
		m_imaginary * complex.m_real + m_real * complex.m_imaginary);
}

CComplex const operator*(double real, const CComplex& complex)
{
	return CComplex(real) * complex;
}

CComplex const CComplex::operator/(const CComplex& complex) const
{
	double denominator = pow(complex.m_real, 2) + pow(complex.m_imaginary, 2);
	double real = (m_real * complex.m_real + m_imaginary * complex.m_imaginary) / denominator;
	double imaginary = (complex.m_real * m_imaginary - m_real * complex.m_imaginary) / denominator;

	return CComplex(real, imaginary);
}

CComplex const operator/(double real, const CComplex& complex)
{
	return CComplex(real) / complex;
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

// оставшиеся операторы
CComplex& CComplex::operator*=(const CComplex& complex)
{
	return *this = *this * complex;
}

CComplex& CComplex::operator/=(const CComplex& complex)
{
	return *this = *this / complex;
}




bool CComplex::operator==(const CComplex & complex) const
{
	return fabs(complex.m_imaginary - m_imaginary) < DBL_EPSILON &&
		fabs(complex.m_real - m_real) < DBL_EPSILON;
}

bool CComplex::operator!=(const CComplex & complex) const
{
	return !(complex == *this);
}


bool operator==(double real, const CComplex & complex)//TODO форматирование
{
	return CComplex(real) == complex;
}

bool operator!=(double real, const CComplex & complex)
{
	return !(CComplex(real) == complex);
}

istream & operator >> (istream& stream, CComplex& complex)
{
	double real = 0;
	double imaginary = 0;
	if (
		(stream >> real) &&
		(stream >> imaginary) &&
		(stream.get() == 'i')
		)
	{
		complex = CComplex(real, imaginary);
	}
	else
	{
		stream.setstate(ios_base::failbit | stream.rdstate());
	}

	return stream;

}

ostream & operator<<(ostream& stream, const CComplex& complex)
{
	stream << complex.Re();
	stream.setf(ios_base::showpos);
	stream << complex.Im() << 'i';
	stream.unsetf(ios_base::showpos);
	return stream;

}