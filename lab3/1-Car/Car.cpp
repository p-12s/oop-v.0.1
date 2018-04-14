#include "stdafx.h"
#include "Car.h"

using namespace std;

pair<int, int> GetSpeedRange(Gear gear)
{
	return speedRange[static_cast<int>(gear)];
}

bool IsSpeedAllowableForGear(Gear gear, int spead)
{
	return spead >= GetSpeedRange(gear).first && spead <= GetSpeedRange(gear).second;
}

CCar::CCar(std::ostream &output)
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
		return false;
	}
	
	if (speed == 0)
	{
		m_speed = speed;
		m_direction = Direction::STOP;
		return true;
	}
	else
	{
		switch (m_gear)
		{
		case Gear::NEUTRAL:
			if (speed > m_speed)
			{
				return false;
			}
			m_speed = speed;
			return true;

		case Gear::REVERSE:
			if (speed > 20)
			{
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
			return false;

		default:
			return false;
		}
	}
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SetGear(const Gear gear)
{
	if (!IsEngineOn())
		return gear == Gear::NEUTRAL;

	if (m_gear == gear)
		return true;

	if (gear == Gear::NEUTRAL)
	{
		m_previousGear = m_gear;
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
			m_previousGear = m_gear;// �.�. �������� ��� ���������� ��������?
			m_gear = Gear::NEUTRAL;
			return true;
		case Gear::FIRST:
			m_previousGear = m_gear;
			m_gear = Gear::FIRST;
			return true;
		case Gear::REVERSE:
			m_previousGear = m_gear;
			m_gear = Gear::REVERSE;
			return true;
		default:
			return false;
		}
	}

	if (m_direction == Direction::FORWARD)
	{
		if (gear == Gear::REVERSE)
		{
			m_lastError << "you can not turn the reverse gear when driving forward\n";
			return false; //����� ��� �������� ������ �������� ������
		}

		if (IsSpeedAllowableForGear(gear, m_speed))
		{
			m_previousGear = m_gear;
			m_gear = gear;
			return true;
		}
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
		//m_output << "Car engine is switched on" << endl;
		return true;
	}

	m_lastError << "car engine is already on\n";
	return false;
}

bool CCar::TurnOffEngine()
{
	if (IsEngineOn() && m_speed == 0 && m_gear == Gear::NEUTRAL)
	{
		m_isEngineOn = false;
		//m_output << "Car engine is switched off" << endl;
		return true;
	}

	m_lastError << "car engine is already off\n";
	return false;
}
