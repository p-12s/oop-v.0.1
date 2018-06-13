#pragma once
#include "stdafx.h"

namespace constants
{
	const std::string PERMISSIBLE_CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const unsigned MIN_RADIX = 2;
	const unsigned MAX_RADIX = 36;
	const unsigned START_NUMBER_SYSTEM_WITH_LETTERS = 11;
}

int MultiplyWithOverflowCheck(unsigned const int mult1, unsigned const int mult2);

int AddWithOverflowCheck(unsigned const int add1, unsigned const int add2);

int StringToInt(std::string& input, const int radix, bool& wasError);

bool IsNotationInAllowableRange(const unsigned notation);

bool IsCharsInAllowableRange(const char ch, const unsigned radix, const char majorSymbol);

void CheckStringForValidateWithRadix(const std::string& valueStr, const unsigned radix);

int ReadNumberFromString(const std::string& notation);

void CastCharsToUpperCase(std::string& valueStr);

std::string IntToString(const int decimalValue, const unsigned radix);

void ParametersInitialization(char* argv[], int& sourceNotation, int& destinationNotation, std::string& valueStr);

std::string TryChangingRadix(const int sourceNotation, const int destinationNotation, std::string& valueStr);