#include "stdafx.h"
#include "../1-Car/Car.h"
#include "../1-Car/ControlPanel.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

struct ControlPanelDependencies
{
	stringstream output;
	stringstream input;

	CCar car;

	ControlPanelDependencies()
		: car(output)
	{
	}
};

struct ControlPanelFixture : ControlPanelDependencies
{
	CControlPanel controlPanel;

	ControlPanelFixture()
		: controlPanel(car, input, output)
	{
	}

	void CheckCommandSucceed(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();

		BOOST_CHECK(input << command);
		string commandLine = command;
		BOOST_CHECK(controlPanel.HandleCommand());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void CheckCommandFailed(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();

		BOOST_CHECK(input << command);
		string commandLine = command;
		BOOST_CHECK(!controlPanel.HandleCommand());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

};

BOOST_FIXTURE_TEST_SUITE(ControlPanel, ControlPanelFixture)

	BOOST_AUTO_TEST_SUITE(general_behavior)
		BOOST_AUTO_TEST_CASE(can_handle_an_unknown_command)
		{
			CheckCommandSucceed("chicken", "unknown command\n");
		}
// показать инфу при выключенном сост
// не может выкл движок повторно

		BOOST_AUTO_TEST_CASE(when_the_engine_is_off)
		{
			BOOST_CHECK(!car.IsEngineOn());
		}
		BOOST_AUTO_TEST_CASE(engine_can_not_be_turned_off_again)
		{
			CheckCommandFailed("EngineOff", "car engine is already off\n");
		}
		/*BOOST_AUTO_TEST_CASE(default_speed_is_0)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}*/
	BOOST_AUTO_TEST_SUITE_END()
		/*
		general_behavior
		when_the_engine_is_off
		engine_can_not_be_turned_off_again
		gear_can_be_switched_only_to_neutral
		can_not_increase_the_speed
		engine_can_be_turned_on
		when_engine_is_on
		*/
	
	/*BOOST_AUTO_TEST_CASE(can_turn_on_engine)
	{
		CheckCommandHandling("EngineOn", "car engine is turned on\n");
	}
	BOOST_AUTO_TEST_CASE(can_set_gear)
	{
		car.TurnOnEngine();
		CheckCommandHandling("SetGear 1", "first gear is switched\n");
	}*/



	/*BOOST_AUTO_TEST_CASE(can_set_speed)
	{
		CheckCommandHandling("SetSpeed 10", "speed 10 is on\n");
	}
	BOOST_AUTO_TEST_CASE(can_turn_off_engine)
	{
		CheckCommandHandling("EngineOff", "car engine is turned off\n");
	}*/


/*

can_handle_EngineOn_command
can_handle_EngineOff_comand
output_error_message_when_handling_EngineOff_command_and_engine_turned_off
can_output_automobile_info
output_success_message_when_handle_command_SetGear_with_valid_speed
output_error_message_when_handle_SetGear_with_invalid_gear
output_error_message_when_handle_SetGear_command_and_engine_is_turned_off
can_handle_command_SetSpeed_with_valid_speed

	general_behavior
		when_the_engine_is_off
		engine_can_not_be_turned_off_again
		gear_can_be_switched_only_to_neutral
		can_not_increase_the_speed
		engine_can_be_turned_on
		when_engine_is_on

		when_engine_is_first_turned_on
		engine_can_not_be_turned_on_again
		direction_is_stop
		gear_is_neutral
		speed_is_0
		if_the_car_is_standing
		engine_can_be_turned_off_if_only_gear_is_neutral
		can_be_turned_first_gear
		can_be_turned_reverse_gear_only_if_first_or_neutral_gear_is_on
		can_not_be_turned_from_2th_to_5th_gear

		when_car_starts_moving_backward
		can_increase_speed_up_only_to_20
		can_not_switch_to_gear_from_1th_to_5th
		can_switch_neutral_gear
		but_after_that_to_switch_from_neutral_gear_it_is_necessary_to_completely_stop

		when_car_starts_moving_forward_in_1th_gear
		can_not_turn_off_engine
		can_switch_neutral_gear
		can_not_increase_speed_on_neutral_transmission
		can_reduce_speed_on_neutral_transmission
		can_dial_speed_from_0_to_30
		can_switch_2th_gear_if_speed_more_than_20
		can_switch_3th_gear_if_speed_is_30
		can_not_switch_gear_more_than_3th
		can_not_switch_reverse_gear

		when_car_moving_forward_in_2th_gear
		can_not_turn_off_engine
		can_switch_neutral_gear
		can_not_increase_speed_on_neutral_transmission
		can_reduce_speed_on_neutral_transmission
		can_dial_speed_from_20_to_50
		can_switch_3th_gear_if_speed_more_than_30
		can_switch_4th_gear_if_speed_more_than_40
		can_switch_5th_gear_if_speed_is_50
		can_not_switch_reverse_gear
		can_switch_to_1th_gear_if_speed_of_less_than_30

		when_car_moving_forward_in_3th_gear
		can_not_turn_off_engine
		can_switch_neutral_gear
		can_not_increase_speed_on_neutral_transmission
		can_reduce_speed_on_neutral_transmission
		can_dial_speed_from_30_to_60
		can_switch_4th_gear_if_speed_more_than_40
		can_switch_5th_gear_if_speed_more_than_50
		can_not_switch_reverse_gear
		can_switch_to_2th_gear_if_speed_of_less_than_50

		when_car_moving_forward_in_4th_gear
		can_not_turn_off_engine
		can_not_increase_speed_on_neutral_transmission
		can_reduce_speed_on_neutral_transmission
		can_dial_speed_from_40_to_90
		can_switch_5th_gear_if_speed_more_than_50
		can_not_switch_reverse_gear
		can_switch_to_3th_gear_if_speed_of_less_than_60

		when_car_moving_forward_in_5th_gear
		can_not_turn_off_engine
		can_switch_neutral_gear
		can_not_increase_speed_on_neutral_transmission
		can_reduce_speed_on_neutral_transmission
		can_dial_speed_from_50_to_150
		can_not_switch_reverse_gear
		can_switch_to_4th_gear_if_speed_of_less_than_90
*/
/*

	/*
	BOOST_AUTO_TEST_CASE(can_turn_on_engine)
	{
		CheckCommandHandling("EngineOn", "Car engine is switched on\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_errors)
	{
		CheckCommandHandling("SetGear 1", "Gear didn't change. Only neutral gear can be set when engine is turned off\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_result_of_changing_car_status)
	{
		CheckCommandHandling("EngineOff", "The engine is already switched off\n");

		car.TurnOnEngine();
		CheckCommandHandling("EngineOn", "Car engine is already switched on\n");

		CheckCommandHandling("SetGear 1", "selected gear 1\n");
		CheckCommandHandling("SetGear 3", "Gear can't be set. Gear is out of speed range\n");

		CheckCommandHandling("SetSpeed 20", "selected speed 20\n");
		CheckCommandHandling("SetGear 2", "selected gear 2\n");
		CheckCommandHandling("SetSpeed 30", "selected speed 30\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_Info_command)
	{
		CheckCommandHandling("Info", "Engine status: switched off\nSpeed: 0\nDirection: stop\nGear: neutral\n");
	}*/

BOOST_AUTO_TEST_SUITE_END()