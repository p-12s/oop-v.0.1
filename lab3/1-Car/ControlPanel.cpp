#include "stdafx.h"
#include "ControlPanel.h"
#include "Car.h"

using namespace std;
using namespace std::placeholders;

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
		{ "Info", bind(&CControlPanel::Info, this, _1) }
	})
	{
	}

CControlPanel::~CControlPanel() = default;

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
	m_output << "Unknown command" << endl;
	return true;
}

bool CControlPanel::EngineOn(istream& /*args*/)
{
	m_car.TurnOnEngine();
	m_output << "Car engine is turned on" << endl;
	return true;
}

bool CControlPanel::EngineOff(istream& /*args*/)
{
	m_car.TurnOffEngine();
	m_output << "Car engine is turned off" << endl;
	return true;
}

bool CControlPanel::Info(std::istream& /*args*/)
{
	string info = (m_car.IsEngineOn())
		? "Engine status is: on\nGear is: " + GetGearAsString(m_car.GetGear()) + "\n" +
		"Direction is: " + GetDirectionAsString(m_car.GetDirection()) + "\n" +
		"Speed is: " + to_string(m_car.GetSpeed()) + "\n"
		: "Engine status is: off\n";

	m_output << info;

	return true;
}