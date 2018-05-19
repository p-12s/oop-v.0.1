#include "stdafx.h"
#include "../1.3-FindMaxEx/FindMaxEx.h"

using namespace std;

struct Athlete
{
	int growthInCentimeters;
	float weightInKilograms;
	string name;
};

struct ListOfAthletes
{
	Athlete requiredAthlete;
	vector<Athlete> emptyList;
	vector<Athlete> athletes;
	ListOfAthletes()
		: athletes({
			{ 160, 61.5f, "Djohn" },
			{ 155, 48.2f, "Brad" },
			{ 178, 73.9f, "Sarah" },
			{ 189, 125.3f, "Ken" },
			{ 205, 105.0f, "Lusy" },
			{ 173, 68.5f, "Bill" }
	})
	{
	}
};


BOOST_FIXTURE_TEST_SUITE(FindMaxExFunction, ListOfAthletes)

	BOOST_AUTO_TEST_CASE(for_an_empty_vector_will_return_false)
	{
		// TODO [](auto& x1, auto& x2) есть у меня в 5 лабе		
		BOOST_CHECK(!FindMaxEx(emptyList, requiredAthlete));
		BOOST_CHECK(FindMaxEx(athletes, requiredAthlete));

		/*BOOST_CHECK(!FindMax(emptyVector, element, [](auto& x1, auto& x2) {
			return x1.intValue < x2.intValue;
		}));*/

		/*auto shape = max_element(shapes.begin(), shapes.end(),
			[](auto&& a, auto&& b)
		{
			return a->GetArea() < b->GetArea();
		});*/
	}

BOOST_AUTO_TEST_SUITE_END()