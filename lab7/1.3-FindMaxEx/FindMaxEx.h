#pragma once
#include "stdafx.h"

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
		return false;

	auto largest = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*largest, *it))
			largest = it;
	}
	maxValue = *largest;

	return true;
}