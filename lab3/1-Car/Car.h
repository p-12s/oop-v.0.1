#pragma once
#include "stdafx.h"

enum class Gear { REVERSE = -1, NEUTRAL = 0, FIRST, SECOND, THIRD, FOURTH, FIFTH };
enum class Direction { BACK, STOP, FORWARD };

static const std::vector<std::pair<int, int>> speedRange = {
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
	std::ostream& m_lastError;
	CCar(std::ostream& output = std::cout);
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
	int m_speed = 0;
	Direction m_direction = Direction::STOP;
};