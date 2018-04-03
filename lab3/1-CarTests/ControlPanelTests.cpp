#include "stdafx.h"
#include "../1-Car/ControlPanel.h"
#include <boost/optional/optional.hpp>

using namespace std;

/*struct ControlPanelDependencies
{
CCar car;
stringstream input;
stringstream output;
};

struct RemoteControlFixture : ControlPanelDependencies
{
CControlPanel controlPanel;

ControlPanelFixture()
: controlPanel(car, input, output)
{
}

// Вспомогательная функция для проверки работы команды command
// Она принимает ожидаемый номер канала expectedChannel и expectedOutput
void VerifyCommandHandling(const string& command, const boost::optional<int> & expectedChannel, const string& expectedOutput)
{
// Предварительно очищаем содержимое выходного потока
output = stringstream();
input = stringstream();
/*BOOST_CHECK(input << command);
BOOST_CHECK(controlPanel.HandleCommand());
BOOST_CHECK_EQUAL(car.IsTurnedOn(), expectedChannel.is_initialized());
BOOST_CHECK_EQUAL(car.GetChannel(), expectedChannel.get_value_or(0));
BOOST_CHECK(input.eof());
BOOST_CHECK_EQUAL(output.str(), expectedOutput);

// тут проще
BOOST_CHECK(input << command);
string commandLine = command;
BOOST_CHECK(car.HandleCommand(commandLine));
BOOST_CHECK_EQUAL(output.str(), expectedOutput);

}
};
*/
BOOST_AUTO_TEST_SUITE(ControlPanel_function)

// Тестовый тест
BOOST_AUTO_TEST_CASE(empty_vector_equal_himself)
{
	vector<double> emptyVector;
	BOOST_CHECK(emptyVector.empty());
}

BOOST_AUTO_TEST_SUITE_END()