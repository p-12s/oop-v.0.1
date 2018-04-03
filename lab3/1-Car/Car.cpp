#include "stdafx.h"
#include "Car.h"

using namespace std;

CCar::CCar(std::ostream &output)
	: m_output(output)
{
}

CCar::~CCar() = default;

bool CCar::IsEngineOn()const
{
	return m_isEngineOn;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::SetSpeed(const int speed)
{
	if (!IsEngineOn())
	{
		return false;
	}
	m_speed = speed;
	return true;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SetGear(const Gear gear)
{
	if (!IsEngineOn())
	{
		return gear == Gear::NEUTRAL;
	}
	/* включить заднюю можем, когда
	- включен двигатель
	- только на нулевой скорости;
	*/
	if (m_speed == 0)
	{
		m_previousGear = m_gear;// м.б. обойтись без предыдущей скорости?
		m_gear = Gear::REVERSE;
		m_direction = Direction::BACK;
		return true;
	}
	
	return false;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

bool CCar::TurnOnEngine()
{
	if (!IsEngineOn())
	{
		m_isEngineOn = true;
		m_output << "Car engine is switched on" << endl;
		return true;
	}

	m_output << "Car engine is already switched on" << endl;
	return false;
}

bool CCar::TurnOffEngine()
{
	if (IsEngineOn())
	{
		m_isEngineOn = false;
		m_output << "Car engine is switched off" << endl;
		return true;
	}

	m_output << "Car engine is already switched off" << endl;
	return false;
}
