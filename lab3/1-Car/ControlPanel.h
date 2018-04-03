#pragma once
#include <boost/noncopyable.hpp>

class CCar;

// явно запрещаем копирование и присваивание экземпл€ров класса
class CControlPanel : boost::noncopyable
{
public:
	CControlPanel(CCar & tv, std::istream & input, std::ostream & output);
	bool HandleCommand();

	// »збавл€емс€ от предупреждени€ компил€тора о том, что он не сможет сгенерировать оператор присваивани€
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