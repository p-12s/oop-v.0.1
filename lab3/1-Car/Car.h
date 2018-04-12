#pragma once
#include <iostream>
using namespace std;

enum class Gear { REVERSE = -1, NEUTRAL = 0, FIRST, SECOND, THIRD, FOURTH, FIFTH };
enum class Direction { BACK, STOP, FORWARD };

static const vector<pair<int, int>> speedRange = {
	{ 0, 20 },
	{ 0, 30 },
	{ 20, 50 },
	{ 30, 60 },
	{ 40, 90 },
	{ 50, 150 }
};

class CCar
{
public:
	ostream& m_output;

	CCar(ostream& output = cout);
	~CCar() = default;

	bool IsEngineOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	int GetSpeed() const;
	bool SetSpeed(const int speed);
	Gear GetGear() const;
	bool SetGear(const Gear gear);
	Direction GetDirection() const;
	
private:
	bool m_isEngineOn = false;
	Gear m_gear = Gear::NEUTRAL;
	Gear m_previousGear = Gear::NEUTRAL; // избавиться
	int m_speed = 0;
	Direction m_direction = Direction::STOP;
};