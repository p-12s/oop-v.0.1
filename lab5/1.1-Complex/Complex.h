#pragma once
#include "stdafx.h"

class CComplex
{
public:
	// инициализация комплексного числа значениями действительной и мнимой частей
	CComplex(double real = 0, double imaginary = 0);
	~CComplex() = default;
	// возвращает действительную часть комплексного числа
	double Re()const;
	// возвращает мнимую часть комплексного числа
	double Im()const;
	// возвращает модуль комплексного числа
	double GetMagnitude()const;
	// возвращает аргумент комплексного числа
	double GetArgument()const;

private:
	double m_real;
	double m_imaginary;
};