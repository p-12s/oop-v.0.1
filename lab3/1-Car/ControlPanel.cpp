#include "stdafx.h"
#include "ControlPanel.h"
#include "Car.h"  

using namespace std;
using namespace placeholders;

int ReadNumberFromString(const string& input)
{
	try
	{
		return stoi(input);
	}
	catch (exception const&)
	{
		throw invalid_argument("could not convert string to number");
	}
}

Gear GetGearByString(const string& input)
{
	int gearNumber = ReadNumberFromString(input);
	switch (gearNumber)
	{
	case -1:
		return Gear::REVERSE;
	case 0:
		return Gear::NEUTRAL;
	case 1:
		return Gear::FIRST;
	case 2:
		return Gear::SECOND;
	case 3:
		return Gear::THIRD;
	case 4:
		return Gear::FOURTH;
	case 5:
		return Gear::FIFTH;
	default:
		throw invalid_argument("invalid gear number. the gear should be in the range [-1, 5]");
	}
}

string GetGearAsString(const Gear gear)
{
	switch(gear)
	{
	case Gear::REVERSE:
		return "reverse";
	case Gear::FIRST:
		return "first";
	case Gear::SECOND:
		return "second";
	case Gear::THIRD:
		return "third";
	case Gear::FOURTH:
		return "fourth";
	case Gear::FIFTH:
		return "fifth";
	default:
		return "neutral";
	}
}

string GetDirectionAsString(const Direction direction)
{
	switch (direction)
	{
	case Direction::BACK:
		return "back";
	case Direction::FORWARD:
		return "forward";
	default:
		return "stop";
	}
}

CControlPanel::CControlPanel(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "EngineOn", bind(&CControlPanel::EngineOn, this, _1) },
		{ "EngineOff", bind(&CControlPanel::EngineOff, this, _1) },
		{ "Info", bind(&CControlPanel::Info, this, _1) },
		{ "SetGear", bind(&CControlPanel::SetGear, this, _1) },
		{ "SetSpeed", bind(&CControlPanel::SetSpeed, this, _1) }
	})
{
}

bool CControlPanel::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	m_output << "unknown command";
	return true;
}

bool CControlPanel::EngineOn(istream& /*args*/)
{
	bool IsEngineTurnOn = m_car.TurnOnEngine();
	if (IsEngineTurnOn)
		m_output << "car engine is turned on";
	return IsEngineTurnOn;
}

bool CControlPanel::EngineOff(istream& /*args*/)
{
	bool IsEngineTurnOff = m_car.TurnOffEngine();
	if (IsEngineTurnOff)
		m_output << "car engine is turned off";
	return IsEngineTurnOff;
}

bool CControlPanel::Info(istream& /*args*/) const
{
	string info = (m_car.IsEngineOn())
		? "engine status is: on\ngear is: " + GetGearAsString(m_car.GetGear()) + "\n" +
		"direction is: " + GetDirectionAsString(m_car.GetDirection()) + "\n" +
		"speed is: " + to_string(m_car.GetSpeed())
		: "engine status is: off";

	m_output << info;
	return true;
}

bool CControlPanel::SetGear(istream& args)
{
	try
	{
		string arg;
		args >> arg;

		Gear gear = GetGearByString(arg);
		bool isGearSet = m_car.SetGear(gear);

		if (isGearSet)
		{
			m_output << GetGearAsString(gear) << " gear is switched";
		}
		return isGearSet;
	}
	catch (exception const& error)
	{
		m_output << "gear change error. " << error.what();
		return false;
	}
}

bool CControlPanel::SetSpeed(istream& args)
{
	try
	{
		string arg;
		args >> arg;

		int speed = ReadNumberFromString(arg);
		bool isSpeedSet = m_car.SetSpeed(speed);

		if (isSpeedSet)
		{
			m_output << "speed " << speed << " is on";
		}
		return isSpeedSet;
	}
	catch (exception const& error)
	{
		m_output << "speed change error. " << error.what();
		return false;
	}
}