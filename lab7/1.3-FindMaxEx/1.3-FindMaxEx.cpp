#include "stdafx.h"
#include "../1.3-FindMaxEx/Resource.h"
#include "../1.3-FindMaxEx/FindMaxEx.h"

using namespace std;

void PrintAthleteInfo(const Athlete& athlete)
{
	ostringstream output;
	output << athlete.name << "\ngrowth in centimeters: "
		<< athlete.growthInCentimeters << "\nweight in kilograms: "
		<< athlete.weightInKilograms << "\n";
	cout << output.str();
}

int main()
{
	vector<Athlete> athletes;
	athletes.push_back({ 160, 61.5f, "Djohn" });
	athletes.push_back({ 155, 48.2f, "Brad" });
	athletes.push_back({ 178, 73.9f, "Sarah" });
	athletes.push_back({ 189, 125.3f, "Ken" });
	athletes.push_back({ 205, 105.0f, "Lusy" });
	athletes.push_back({ 173, 68.5f, "Baddy" });

	cout << "\nSportsman with max growth: \n";
	Athlete max;
	FindMaxEx(athletes, max, [](auto&& a, auto&& b) {
		return a.growthInCentimeters < b.growthInCentimeters;
	});
	PrintAthleteInfo(max);

	cout << "\nSportsman with max weight: \n";
	FindMaxEx(athletes, max, [](auto&& a, auto&& b) {
		return a.weightInKilograms < b.weightInKilograms;
	});
	PrintAthleteInfo(max);

	cout << "\nSportsman with max name (in alphabet order): \n";
	FindMaxEx(athletes, max, [](auto&& a, auto&& b) {
		return a.name < b.name;
	});
	PrintAthleteInfo(max);
	cout << "\n";

    return 0;
}