#pragma once
#include "stdafx.h"

class CComplex
{
public:
	CComplex(double real = 0, double imaginary = 0);
	~CComplex() = default;
	double Re() const;
	double Im() const;	
	double GetMagnitude() const; // возвращает модуль комплексного числа	
	double GetArgument() const; // возвращает аргумент комплексного числа

private:
	double m_real;
	double m_imaginary;
};