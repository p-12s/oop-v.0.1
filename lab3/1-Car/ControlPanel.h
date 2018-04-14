#pragma once
#include <boost/noncopyable.hpp>

class CCar;

// ������������ �� boost::noncopyable - ����� ������ ��������� ����������� � ������������ ����������� ������
class CControlPanel : boost::noncopyable
{
public:
	CControlPanel(CCar& car, std::istream& input, std::ostream& output);
	~CControlPanel();

	bool HandleCommand();

	// ����������� �� �������������� ����������� � ���, ��� �� �� ������ ������������� �������� ������������
	CControlPanel& operator=(const CControlPanel&) = delete;
private:
	bool Info(std::istream& args);
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

private:	
	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;
	const ActionMap m_actionMap;
};