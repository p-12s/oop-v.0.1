#pragma once

using namespace std;

enum class Gear { REVERSE = -1, NEUTRAL = 0, FIRST, SECOND, THIRD, FOURTH, FIFTH };
enum class Direction { BACK, STOP, FORWARD };

class CCar
{
public:
	ostream & m_output;

	CCar(ostream &output);
	~CCar();

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
	Gear previousGear;
	int m_speed = 0;
	Direction m_direction = Direction::STOP;
};
