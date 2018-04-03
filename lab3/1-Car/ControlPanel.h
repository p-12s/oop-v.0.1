#pragma once
#include <boost/noncopyable.hpp>

class CCar;

// ���� ��������� ����������� � ������������ ����������� ������
class CControlPanel : boost::noncopyable
{
public:
	CControlPanel(CCar & tv, std::istream & input, std::ostream & output);
	bool HandleCommand();

	// ����������� �� �������������� ����������� � ���, ��� �� �� ������ ������������� �������� ������������
	// CControlPanel& operator=(const CControlPanel &) = delete;
private:
	/*bool TurnOn(std::istream & args);
	bool TurnOff(std::istream & args);
	bool Info(std::istream & args);*/
private:
	typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

	CCar & m_car;
	std::istream & m_input;
	std::ostream & m_output;

	const ActionMap m_actionMap;
};