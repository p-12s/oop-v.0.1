#include "stdafx.h"
#include "ControlPanel.h"

using namespace std;
using namespace std::placeholders;

CControlPanel::CControlPanel(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ 
			"EngineOn", [this](istream& strm) 
			{
				return EngineOn(strm);
			} 
		},
		{ 
			"EngineOff", bind(&CControlPanel::EngineOff, this, _1) 
		},
		{ 
			"Info", bind(&CControlPanel::Info, this, _1) 
		}
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

	return false;
}

bool CControlPanel::TurnOnEngine(std::istream & /*args*/)
{
	m_car.TurnOnEngine();
	m_output << "Engine is turned on" << endl;
	return true;
}

bool CControlPanel::TurnOff(std::istream & /*args*/)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CControlPanel::Info(std::istream & /*args*/)
{
	string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\nChannel is: " + to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\n";

	m_output << info;

	return true;
}

