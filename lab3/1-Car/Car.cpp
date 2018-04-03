#include "stdafx.h"
#include "Car.h"

bool CCar::IsCarRunning()const
{
	return m_isRunning;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

Gear CCar::GetGear() const
{
	return m_gear;
}