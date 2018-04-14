#include "stdafx.h"
#include "Car.h"

using namespace std;

pair<int, int> GetSpeedRange(Gear gear)
{
	return speedRange[static_cast<int>(gear)];
}

bool IsSpeedAllowableForGear(Gear gear, int speed)
{
	return speed >= GetSpeedRange(gear).first && speed <= GetSpeedRange(gear).second;
}

CCar::CCar(ostream &output)
	: m_lastError(output)
{
}

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
		m_lastError << "can not change the speed when car engine is off";
		return false;
	}
	
	if (speed < 0)
	{
		m_lastError << "speed can not be negative";
		return false;
	}

	if (speed == 0)
	{
		m_speed = speed;
		m_direction = Direction::STOP;
		return true;
	}

	switch (m_gear)
	{
	case Gear::NEUTRAL:
		if (speed > m_speed)
		{
			m_lastError << "when switched neutral gear, you can change the speed only to a lower side";
			return false;
		}
		m_speed = speed;
		return true;

	case Gear::REVERSE:
		if (speed > 20)
		{
			m_lastError << "invalid speed value. on the current gear is permissible movement with a speed of 0-20";
			return false;
		}
		m_speed = speed;
		m_direction = Direction::BACK;
		return true;

	case Gear::FIRST:
	case Gear::SECOND:
	case Gear::THIRD:
	case Gear::FOURTH:
	case Gear::FIFTH:
		if (IsSpeedAllowableForGear(m_gear, speed))
		{
			m_speed = speed;
			m_direction = Direction::FORWARD;
			return true;
		}
		m_lastError << "invalid speed value. on the current gear is permissible movement with a speed of " +
			to_string(GetSpeedRange(m_gear).first) + "-" + 
			to_string(GetSpeedRange(m_gear).second);
		return false;

	default:
		return false;
	}
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SetGear(const Gear gear)
{
	if (!IsEngineOn())
	{
		if (gear == Gear::NEUTRAL)
			return true;

		m_lastError << "when the engine is off, the gear can only be switched to neutral";
		return false;
	}

	if (m_gear == gear)
		return true;

	if (gear == Gear::NEUTRAL)
	{
		m_gear = Gear::NEUTRAL;
		m_direction = m_speed == 0 ? Direction::STOP : m_direction;
		return true;
	}

	if (m_speed == 0)
	{
		m_direction = Direction::STOP;
		switch (gear)
		{
		case Gear::NEUTRAL:
			m_gear = Gear::NEUTRAL;
			return true;
		case Gear::FIRST:
			m_gear = Gear::FIRST;
			return true;
		case Gear::REVERSE:
			m_gear = Gear::REVERSE;
			return true;
		default:
			m_lastError << "when the car is stationary, you can only switch to the reverse, neutral or first gear";
			return false;
		}
	}

	if (m_direction == Direction::FORWARD)
	{
		if (gear == Gear::REVERSE)
		{
			m_lastError << "you can not turn the reverse gear when driving forward";
			return false;
		}

		if (IsSpeedAllowableForGear(gear, m_speed))
		{
			m_gear = gear;
			return true;
		}
		m_lastError << "you can not switch to this gear at the current speed";
		return false;
	}

	if (m_speed > 0 && m_direction == Direction::BACK && m_gear == Gear::NEUTRAL)
	{
		m_lastError << "you can not change the gear until the car stops completely";
	}
	else
	{
		m_lastError << "you can not turn the forward gear when driving back";
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
		return true;
	}
	m_lastError << "car engine is already on";
	return false;
}

bool CCar::TurnOffEngine()
{
	if (IsEngineOn() && m_speed == 0 && m_gear == Gear::NEUTRAL)
	{
		m_isEngineOn = false;
		return true;
	}
	if (!IsEngineOn())
	{
		m_lastError << "car engine is already off";
	}
	else
	{
		m_lastError << "car engine can be turned off only in neutral gear and at zero speed";
	}	
	return false;
}
