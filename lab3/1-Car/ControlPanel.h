#pragma once
#include <boost/noncopyable.hpp>

class CCar;

class CControlPanel : boost::noncopyable
{
public:
	CControlPanel(CCar& car, std::istream& input, std::ostream& output);
	~CControlPanel() = default;
	bool HandleCommand();
	// Избавляемся от предупреждения компилятора о том, что он не сможет сгенерировать оператор присваивания
	CControlPanel& operator=(const CControlPanel&) = delete;

private:
	bool Info(std::istream& args) const;
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;
	const ActionMap m_actionMap;
};