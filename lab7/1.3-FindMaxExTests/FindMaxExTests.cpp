#include "stdafx.h"
#include "../1.3-FindMaxEx/Resource.h"
#include "../1.3-FindMaxEx/FindMaxEx.h"

using namespace std;

struct ListOfAthletes
{
	vector<Athlete> athletes;
	ListOfAthletes()
		: athletes({
			{ 160, 61.5f, "Djohn" },
			{ 155, 48.2f, "Brad" },
			{ 178, 73.9f, "Sarah" },
			{ 189, 125.3f, "Ken" },
			{ 205, 105.0f, "Lusy" },
			{ 173, 68.5f, "Baddy" }
	})
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(FindMaxEx_function, ListOfAthletes)

	BOOST_AUTO_TEST_CASE(for_an_empty_vector_will_return_false)
	{
		vector<Athlete> emptyAthleteList;
		Athlete max;
		BOOST_CHECK(!FindMaxEx(emptyAthleteList, max,
			[](auto&& a, auto&& b)
		{
			return a.growthInCentimeters < b.growthInCentimeters;
		}));
		BOOST_CHECK(FindMaxEx(athletes, max,
			[](auto&& a, auto&& b)
		{
			return a.growthInCentimeters < b.growthInCentimeters;
		}));
	}

	BOOST_AUTO_TEST_CASE(can_return_the_maximum_for_type_int)
	{
		Athlete max;
		BOOST_CHECK(FindMaxEx(athletes, max,
			[](auto&& a, auto&& b)
		{
			return a.growthInCentimeters < b.growthInCentimeters;
		}));
		BOOST_CHECK(max.growthInCentimeters == 205);
	}

	BOOST_AUTO_TEST_CASE(can_return_the_maximum_for_type_float)
	{
		Athlete max;
		BOOST_CHECK(FindMaxEx(athletes, max,
			[](auto&& a, auto&& b)
		{
			return a.weightInKilograms < b.weightInKilograms;
		}));
		BOOST_CHECK(max.weightInKilograms == 125.3f);
	}

	BOOST_AUTO_TEST_CASE(can_return_the_maximum_for_type_string)
	{
		Athlete max;
		BOOST_CHECK(FindMaxEx(athletes, max,
			[](auto&& a, auto&& b)
		{
			return a.name < b.name;
		}));
		BOOST_CHECK(max.name == "Sarah");
	}

BOOST_AUTO_TEST_SUITE_END()