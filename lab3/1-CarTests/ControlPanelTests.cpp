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

	void VerifySuccess(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();

		BOOST_CHECK(input << command);
		BOOST_CHECK(controlPanel.HandleCommand());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void VerifyFailure(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();

		BOOST_CHECK(input << command);
		BOOST_CHECK(!controlPanel.HandleCommand());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void CheckResultOfRunningInfoCommand(const string expectedGear, const string expectedDirection, const int expectedSpeed)
	{
		string pattern = "engine status is: on\ngear is: " + expectedGear + "\n" +
			"direction is: " + expectedDirection + "\n" +
			"speed is: " + to_string(expectedSpeed);
		VerifySuccess("Info", pattern);
	}

	void CheckCarState(const Gear expectedGear, const Direction expectedDirection, const int expectedSpeed) const
	{
		BOOST_CHECK(car.GetGear() == expectedGear);
		BOOST_CHECK(car.GetDirection() == expectedDirection);
		BOOST_CHECK(car.GetSpeed() == expectedSpeed);
	}
};

BOOST_FIXTURE_TEST_SUITE(ControlPanel, ControlPanelFixture)

	BOOST_AUTO_TEST_SUITE(general_behavior)
		BOOST_AUTO_TEST_CASE(can_handle_an_unknown_command)
		{
			VerifySuccess("chicken", "unknown command");
		}
		BOOST_AUTO_TEST_CASE(can_show_default_info)
		{
			VerifySuccess("Info", "engine status is: off");
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_engine_is_off_ : ControlPanelFixture
	{
		when_engine_is_off_()
		{
			BOOST_CHECK(!car.IsEngineOn());
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_the_car_engine_is_off, when_engine_is_off_)
		BOOST_AUTO_TEST_CASE(can_not_turn_off_the_engine_again)
		{
			VerifyFailure("EngineOff", "car engine is already off");
		}
		BOOST_AUTO_TEST_CASE(gear_can_be_switched_only_to_neutral)
		{
			VerifyFailure("SetGear -1", "when the engine is off, the gear can only be switched to neutral");
			VerifyFailure("SetGear 1", "when the engine is off, the gear can only be switched to neutral");
			VerifyFailure("SetGear 2", "when the engine is off, the gear can only be switched to neutral");
			VerifyFailure("SetGear 3", "when the engine is off, the gear can only be switched to neutral");
			VerifyFailure("SetGear 4", "when the engine is off, the gear can only be switched to neutral");
			VerifyFailure("SetGear 5", "when the engine is off, the gear can only be switched to neutral");
			VerifySuccess("SetGear 0", "neutral gear is switched");
			VerifySuccess("Info", "engine status is: off");
			CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
		}
		BOOST_AUTO_TEST_CASE(can_not_increase_the_speed)
		{
			VerifyFailure("SetSpeed 0", "can not change the speed when car engine is off");
			VerifyFailure("SetSpeed 1", "can not change the speed when car engine is off");
			VerifyFailure("SetSpeed -1", "can not change the speed when car engine is off");
			VerifySuccess("Info", "engine status is: off");
			CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_engine_is_on_ : ControlPanelFixture
	{
		when_engine_is_on_()
		{
			BOOST_CHECK(!car.IsEngineOn());
			VerifySuccess("EngineOn", "car engine is turned on");
			CheckResultOfRunningInfoCommand("neutral", "stop", 0);
			BOOST_CHECK(car.IsEngineOn());
			CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_the_car_engine_is_on, when_engine_is_on_)
		BOOST_AUTO_TEST_CASE(can_not_turn_on_the_engine_again)
		{
			VerifyFailure("EngineOn", "car engine is already on");
			CheckResultOfRunningInfoCommand("neutral", "stop", 0);
		}
		BOOST_AUTO_TEST_CASE(can_turn_only_on_reverse_or_first_gear)
		{
			VerifySuccess("SetGear 1", "first gear is switched");
			CheckResultOfRunningInfoCommand("first", "stop", 0);
			CheckCarState(Gear::FIRST, Direction::STOP, 0);

			VerifySuccess("SetGear -1", "reverse gear is switched");
			CheckResultOfRunningInfoCommand("reverse", "stop", 0);
			CheckCarState(Gear::REVERSE, Direction::STOP, 0);

			VerifySuccess("SetGear 0", "neutral gear is switched");
			CheckResultOfRunningInfoCommand("neutral", "stop", 0);
			CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);

			VerifyFailure("SetGear 2", "when the car is stationary, you can only switch to the reverse, neutral or first gear");
			CheckResultOfRunningInfoCommand("neutral", "stop", 0);
			CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
		}
		BOOST_AUTO_TEST_CASE(can_output_an_error_if_an_incorrect_speed_is_entered)
		{
			VerifyFailure("SetSpeed ff", "speed change error. could not convert string to number");
			CheckResultOfRunningInfoCommand("neutral", "stop", 0);
		}
		BOOST_AUTO_TEST_CASE(can_output_an_error_if_an_incorrect_gear_is_entered)
		{
			VerifyFailure("SetGear ff", "gear change error. could not convert string to number");
			CheckResultOfRunningInfoCommand("neutral", "stop", 0);
		}

		struct when_car_starts_moving_backward_ : when_engine_is_on_
		{
			when_car_starts_moving_backward_()
			{
				car.SetGear(Gear::REVERSE);
				car.SetSpeed(5);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_car_starts_moving_backward, when_car_starts_moving_backward_)
			BOOST_AUTO_TEST_CASE(can_output_an_error_if_we_want_to_switch_to_first_gear)
			{
				VerifyFailure("SetGear 1", "you can not turn the forward gear when driving back");
				CheckResultOfRunningInfoCommand("reverse", "back", 5);
			}
			BOOST_AUTO_TEST_CASE(can_output_an_error_if_we_want_to_increase_unacceptable_speed)
			{
				VerifyFailure("SetSpeed 200", "invalid speed value. on the current gear is permissible movement with a speed of 0-20");
				CheckResultOfRunningInfoCommand("reverse", "back", 5);
			}
			BOOST_AUTO_TEST_CASE(can_output_an_error_if_we_want_to_increase_the_speed_moving_on_neutral_gear)
			{
				VerifySuccess("SetSpeed 10", "speed 10 is on");
				CheckResultOfRunningInfoCommand("reverse", "back", 10);

				VerifySuccess("SetGear 0", "neutral gear is switched");
				CheckResultOfRunningInfoCommand("neutral", "back", 10);

				VerifyFailure("SetSpeed 11", "when switched neutral gear, you can change the speed only to a lower side");
				CheckResultOfRunningInfoCommand("neutral", "back", 10);
			}
			BOOST_AUTO_TEST_CASE(can_output_an_error_if_we_want_to_move_to_a_neutral_gear_switch_it_to_another)
			{
				VerifySuccess("SetGear 0", "neutral gear is switched");
				CheckResultOfRunningInfoCommand("neutral", "back", 5);

				VerifyFailure("SetGear -1", "you can not change the gear until the car stops completely");
				CheckResultOfRunningInfoCommand("neutral", "back", 5);
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct when_car_starts_moving_forward_ : when_engine_is_on_
		{
			when_car_starts_moving_forward_()
			{
				car.SetGear(Gear::FIRST);
				car.SetSpeed(15);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_car_starts_moving_forward, when_car_starts_moving_forward_)
			BOOST_AUTO_TEST_CASE(can_not_turn_off_engine)
			{
				VerifyFailure("EngineOff", "car engine can be turned off only in neutral gear and at zero speed");
				CheckResultOfRunningInfoCommand("first", "forward", 15);
			}
			BOOST_AUTO_TEST_CASE(can_output_an_error_if_we_want_to_switch_unacceptable_gear)
			{
				VerifyFailure("SetGear 2", "you can not switch to this gear at the current speed");
				CheckResultOfRunningInfoCommand("first", "forward", 15);
			}
			BOOST_AUTO_TEST_CASE(can_switch_allowable_gear)
			{
				VerifySuccess("SetSpeed 20", "speed 20 is on");
				VerifySuccess("SetGear 2", "second gear is switched");
				CheckResultOfRunningInfoCommand("second", "forward", 20);
			}
			BOOST_AUTO_TEST_CASE(can_output_an_error_if_we_want_to_increase_unacceptable_speed)
			{
				VerifyFailure("SetSpeed 31", "invalid speed value. on the current gear is permissible movement with a speed of 0-30");
				CheckResultOfRunningInfoCommand("first", "forward", 15);
			}
			BOOST_AUTO_TEST_CASE(can_turn_off_engine_if_gear_is_neutral_and_speed_is_0)
			{
				VerifySuccess("SetSpeed 0", "speed 0 is on");
				VerifySuccess("SetGear 0", "neutral gear is switched");
				VerifySuccess("EngineOff", "car engine is turned off");
				VerifySuccess("Info", "engine status is: off");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()	
BOOST_AUTO_TEST_SUITE_END()