#pragma once
#include "stdafx.h"

class CComplex
{
public:
	// ������������� ������������ ����� ���������� �������������� � ������ ������
	CComplex(double real = 0, double imaginary = 0);
	~CComplex() = default;
	// ���������� �������������� ����� ������������ �����
	double Re()const;
	// ���������� ������ ����� ������������ �����
	double Im()const;
	// ���������� ������ ������������ �����
	double GetMagnitude()const;
	// ���������� �������� ������������ �����
	double GetArgument()const;

private:
	double m_real;
	double m_imaginary;
};