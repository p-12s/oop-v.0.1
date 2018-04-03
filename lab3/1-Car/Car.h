#pragma once

enum class Gear { REVERSE = -1, NEUTRAL = 0, FIRST, SECOND, THIRD, FOURTH, FIFTH };
enum class Direction { BACK, STOP, FORWARD };

class CCar
{
public:
	bool IsCarRunning() const;
	int GetSpeed() const;
	Gear GetGear() const;
private:
	bool m_isRunning = false;
	Gear m_gear = Gear::NEUTRAL;
	Gear previousGear;
	int m_speed = 0;
};
