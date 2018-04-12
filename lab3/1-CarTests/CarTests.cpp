#include "stdafx.h"
#include "../1-Car/Car.h"

using namespace std;

struct CarFixture
{
	stringstream output;
	CCar car;

	CarFixture()
		: car(output)
	{
	}

	void CheckCarImmobility() const
	{
		BOOST_CHECK(car.GetDirection() == Direction::STOP);
		BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
		BOOST_CHECK(car.GetSpeed() == 0);
	}

	void CheckCarState(const Gear expectedGear, const Direction expectedDirection) const
	{
		BOOST_CHECK(car.GetGear() == expectedGear);
		BOOST_CHECK(car.GetDirection() == expectedDirection);
	}

	void CheckCarState(const Gear expectedGear, const Direction expectedDirection, const int expectedSpeed) const
	{
		BOOST_CHECK(car.GetGear() == expectedGear);
		BOOST_CHECK(car.GetDirection() == expectedDirection);
		BOOST_CHECK(car.GetSpeed() == expectedSpeed);
	}

	void CanNotTurnOffEngine()
	{
		BOOST_CHECK(!car.TurnOffEngine());
		BOOST_CHECK(car.IsEngineOn());
	}

	void CanTurnOffEngine()
	{
		BOOST_CHECK(car.TurnOffEngine());
		BOOST_CHECK(!car.IsEngineOn());
	}
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_SUITE(general_behavior)
		BOOST_AUTO_TEST_CASE(engine_is_off_by_default)
		{
			BOOST_CHECK(!car.IsEngineOn());
		}
		BOOST_AUTO_TEST_CASE(default_direction_is_stop)
		{
			BOOST_CHECK(car.GetDirection() == Direction::STOP);
		}		
		BOOST_AUTO_TEST_CASE(default_gear_is_neutral)
		{
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
		}
		BOOST_AUTO_TEST_CASE(default_speed_is_0)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_the_engine_is_off)
		BOOST_AUTO_TEST_CASE(engine_can_not_be_turned_off_again)
		{
			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(!car.IsEngineOn());
		}
		BOOST_AUTO_TEST_CASE(gear_can_be_switched_only_to_neutral)
		{
			BOOST_CHECK(!car.SetGear(Gear::REVERSE));
			CheckCarImmobility();
			BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			CheckCarImmobility();
			BOOST_CHECK(!car.SetGear(Gear::FIRST));
			CheckCarImmobility();
			BOOST_CHECK(!car.SetGear(Gear::SECOND));
			CheckCarImmobility();
			BOOST_CHECK(!car.SetGear(Gear::THIRD));
			CheckCarImmobility();
			BOOST_CHECK(!car.SetGear(Gear::FOURTH));
			CheckCarImmobility();
			BOOST_CHECK(!car.SetGear(Gear::FIFTH));
			CheckCarImmobility();
		}
		BOOST_AUTO_TEST_CASE(can_not_increase_the_speed)
		{
			BOOST_CHECK(!car.SetSpeed(10));
		}
		BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
		{
			BOOST_CHECK(!car.TurnOffEngine());
			BOOST_CHECK(car.TurnOnEngine());
			BOOST_CHECK(car.IsEngineOn());
		}		
	BOOST_AUTO_TEST_SUITE_END()

	struct when_engine_is_on_ : CarFixture
	{
		when_engine_is_on_()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_engine_is_first_turned_on, when_engine_is_on_)
		BOOST_AUTO_TEST_CASE(engine_can_not_be_turned_on_again)
		{
			BOOST_CHECK(!car.TurnOnEngine());
			BOOST_CHECK(car.IsEngineOn());
		}
		BOOST_AUTO_TEST_CASE(direction_is_stop)
		{
			BOOST_CHECK(car.GetDirection() == Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(gear_is_neutral)
		{
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
		}
		BOOST_AUTO_TEST_CASE(speed_is_0)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}

		BOOST_AUTO_TEST_SUITE(if_the_car_is_standing)
			BOOST_AUTO_TEST_CASE(engine_can_be_turned_off_if_only_gear_is_neutral)
			{
				BOOST_CHECK(car.SetGear(Gear::FIRST));
				CheckCarState(Gear::FIRST, Direction::STOP, 0);
				CanNotTurnOffEngine();

				BOOST_CHECK(car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::REVERSE, Direction::STOP, 0);
				CanNotTurnOffEngine();

				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
				CanTurnOffEngine();
			}
			BOOST_AUTO_TEST_CASE(can_be_turned_first_gear)
			{
				BOOST_CHECK(car.SetGear(Gear::FIRST));
				CheckCarState(Gear::FIRST, Direction::STOP, 0);
			}			
			BOOST_AUTO_TEST_CASE(can_be_turned_reverse_gear_only_if_first_or_neutral_gear_is_on)
			{
				BOOST_CHECK(car.SetGear(Gear::FIRST));
				CheckCarState(Gear::FIRST, Direction::STOP, 0);
				BOOST_CHECK(car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::REVERSE, Direction::STOP, 0);

				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
				BOOST_CHECK(car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::REVERSE, Direction::STOP, 0);

				BOOST_CHECK(car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::REVERSE, Direction::STOP, 0);
			}
			BOOST_AUTO_TEST_CASE(can_not_be_turned_from_2th_to_5th_gear)
			{
				BOOST_CHECK(!car.SetGear(Gear::SECOND));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);

				BOOST_CHECK(!car.SetGear(Gear::THIRD));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);

				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);

				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
			}
		BOOST_AUTO_TEST_SUITE_END()		

		struct when_car_starts_moving_backward_ : when_engine_is_on_
		{
			when_car_starts_moving_backward_()
			{
				car.SetGear(Gear::REVERSE);
				car.SetSpeed(5);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_car_starts_moving_backward, when_car_starts_moving_backward_)
			BOOST_AUTO_TEST_CASE(can_increase_speed_up_only_to_20)
			{
				BOOST_CHECK(car.SetSpeed(20));
				CheckCarState(Gear::REVERSE, Direction::BACK, 20);

				BOOST_CHECK(car.SetSpeed(15));
				CheckCarState(Gear::REVERSE, Direction::BACK, 15);

				BOOST_CHECK(!car.SetSpeed(21));
				CheckCarState(Gear::REVERSE, Direction::BACK, 15);

				BOOST_CHECK(car.SetSpeed(0));
				CheckCarState(Gear::REVERSE, Direction::STOP, 0);
			}
			BOOST_AUTO_TEST_CASE(can_not_switch_to_gear_from_1th_to_5th)
			{
				BOOST_CHECK(!car.SetGear(Gear::FIRST));
				CheckCarState(Gear::REVERSE, Direction::BACK, 5);

				BOOST_CHECK(!car.SetGear(Gear::SECOND));
				CheckCarState(Gear::REVERSE, Direction::BACK, 5);

				BOOST_CHECK(!car.SetGear(Gear::THIRD));
				CheckCarState(Gear::REVERSE, Direction::BACK, 5);

				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::REVERSE, Direction::BACK, 5);

				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::REVERSE, Direction::BACK, 5);
			}
			BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 5);
			}
			BOOST_AUTO_TEST_CASE(but_after_that_to_switch_from_neutral_gear_it_is_necessary_to_completely_stop)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(!car.SetSpeed(10));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 5);

				BOOST_CHECK(car.SetSpeed(3));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(!car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(!car.SetGear(Gear::FIRST));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(!car.SetGear(Gear::SECOND));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(!car.SetGear(Gear::THIRD));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(car.SetSpeed(0));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);

				BOOST_CHECK(car.SetGear(Gear::REVERSE));
				BOOST_CHECK(car.SetSpeed(20));
				CheckCarState(Gear::REVERSE, Direction::BACK, 20);
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct when_car_starts_moving_forward_in_1th_gear_ : when_engine_is_on_
		{
			when_car_starts_moving_forward_in_1th_gear_()
			{
				car.SetGear(Gear::FIRST);
				car.SetSpeed(5);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_car_starts_moving_forward_in_1th_gear, when_car_starts_moving_forward_in_1th_gear_)
			BOOST_AUTO_TEST_CASE(can_not_turn_off_engine)
			{
				BOOST_CHECK(!car.TurnOffEngine());
				BOOST_CHECK(car.IsEngineOn());
				CheckCarState(Gear::FIRST, Direction::FORWARD, 5);
			}
			BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 5);
			}
			BOOST_AUTO_TEST_CASE(can_not_increase_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(!car.SetSpeed(6));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 5);
			}
			BOOST_AUTO_TEST_CASE(can_reduce_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(car.SetSpeed(4));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 4);
			}
			BOOST_AUTO_TEST_CASE(can_dial_speed_from_0_to_30)
			{
				BOOST_CHECK(car.SetSpeed(0));
				CheckCarState(Gear::FIRST, Direction::STOP, 0);

				BOOST_CHECK(car.SetSpeed(30));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 30);

				BOOST_CHECK(!car.SetSpeed(31));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 30);
			}
			BOOST_AUTO_TEST_CASE(can_switch_2th_gear_if_speed_more_than_20)
			{
				BOOST_CHECK(!car.SetGear(Gear::SECOND));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 5);

				BOOST_CHECK(car.SetSpeed(19));
				BOOST_CHECK(!car.SetGear(Gear::SECOND));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 19);

				BOOST_CHECK(car.SetSpeed(20));
				BOOST_CHECK(car.SetGear(Gear::SECOND));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_switch_3th_gear_if_speed_is_30)
			{
				BOOST_CHECK(car.SetSpeed(29));
				BOOST_CHECK(!car.SetGear(Gear::THIRD));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 29);

				BOOST_CHECK(car.SetSpeed(30));
				BOOST_CHECK(car.SetGear(Gear::THIRD));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 30);
			}
			BOOST_AUTO_TEST_CASE(can_not_switch_gear_more_than_3th)
			{
				BOOST_CHECK(car.SetSpeed(30));
				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 30);

				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 30);
			}
			BOOST_AUTO_TEST_CASE(can_not_switch_reverse_gear)
			{
				BOOST_CHECK(!car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 5);
			}
		BOOST_AUTO_TEST_SUITE_END()

			
		struct when_car_moving_forward_in_2th_gear_ : when_engine_is_on_
		{
			when_car_moving_forward_in_2th_gear_()
			{
				car.SetGear(Gear::FIRST);
				car.SetSpeed(20);
				car.SetGear(Gear::SECOND);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_car_moving_forward_in_2th_gear, when_car_moving_forward_in_2th_gear_)
			BOOST_AUTO_TEST_CASE(can_not_turn_off_engine)
			{
				BOOST_CHECK(!car.TurnOffEngine());
				BOOST_CHECK(car.IsEngineOn());
				CheckCarState(Gear::SECOND, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_not_increase_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(!car.SetSpeed(21));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_reduce_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(car.SetSpeed(20));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_dial_speed_from_20_to_50)
			{
				BOOST_CHECK(!car.SetSpeed(19));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 20);

				BOOST_CHECK(car.SetSpeed(50));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 50);

				BOOST_CHECK(!car.SetSpeed(51));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 50);
			}
			BOOST_AUTO_TEST_CASE(can_switch_3th_gear_if_speed_more_than_30)
			{
				BOOST_CHECK(!car.SetGear(Gear::THIRD));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 20);

				BOOST_CHECK(car.SetSpeed(29));
				BOOST_CHECK(!car.SetGear(Gear::THIRD));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 29);

				BOOST_CHECK(car.SetSpeed(30));
				BOOST_CHECK(car.SetGear(Gear::THIRD));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 30);
			}
			BOOST_AUTO_TEST_CASE(can_switch_4th_gear_if_speed_more_than_40)
			{
				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 20);

				BOOST_CHECK(car.SetSpeed(39));
				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 39);

				BOOST_CHECK(car.SetSpeed(40));
				BOOST_CHECK(car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 40);
			}
			BOOST_AUTO_TEST_CASE(can_switch_5th_gear_if_speed_is_50)
			{
				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 20);

				BOOST_CHECK(car.SetSpeed(49));
				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 49);

				BOOST_CHECK(car.SetSpeed(50));
				BOOST_CHECK(car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 50);
			}
			BOOST_AUTO_TEST_CASE(can_not_switch_reverse_gear)
			{
				BOOST_CHECK(!car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_switch_to_1th_gear_if_speed_of_less_than_30)
			{
				BOOST_CHECK(car.SetSpeed(31));
				BOOST_CHECK(!car.SetGear(Gear::FIRST));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 31);

				BOOST_CHECK(car.SetSpeed(30));
				BOOST_CHECK(car.SetGear(Gear::FIRST));
				CheckCarState(Gear::FIRST, Direction::FORWARD, 30);
			}			
		BOOST_AUTO_TEST_SUITE_END()

		struct when_car_moving_forward_in_3th_gear_ : when_engine_is_on_
		{
			when_car_moving_forward_in_3th_gear_()
			{
				car.SetGear(Gear::FIRST);
				car.SetSpeed(30);
				car.SetGear(Gear::THIRD);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_car_moving_forward_in_3th_gear, when_car_moving_forward_in_3th_gear_)
			BOOST_AUTO_TEST_CASE(can_not_turn_off_engine)
			{
				BOOST_CHECK(!car.TurnOffEngine());
				BOOST_CHECK(car.IsEngineOn());
				CheckCarState(Gear::THIRD, Direction::FORWARD, 30);
			}
			BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 30);
			}
			BOOST_AUTO_TEST_CASE(can_not_increase_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(!car.SetSpeed(31));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 30);
			}
			BOOST_AUTO_TEST_CASE(can_reduce_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(car.SetSpeed(20));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_dial_speed_from_30_to_60)
			{
				BOOST_CHECK(!car.SetSpeed(29));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 30);

				BOOST_CHECK(car.SetSpeed(60));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 60);

				BOOST_CHECK(!car.SetSpeed(61));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 60);
			}
			BOOST_AUTO_TEST_CASE(can_switch_4th_gear_if_speed_more_than_40)
			{
				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 30);

				BOOST_CHECK(car.SetSpeed(39));
				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 39);

				BOOST_CHECK(car.SetSpeed(40));
				BOOST_CHECK(car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 40);
			}
			BOOST_AUTO_TEST_CASE(can_switch_5th_gear_if_speed_more_than_50)
			{
				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 30);

				BOOST_CHECK(car.SetSpeed(49));
				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 49);

				BOOST_CHECK(car.SetSpeed(50));
				BOOST_CHECK(car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 50);
			}
			BOOST_AUTO_TEST_CASE(can_not_switch_reverse_gear)
			{
				BOOST_CHECK(!car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 30);
			}
			BOOST_AUTO_TEST_CASE(can_switch_to_2th_gear_if_speed_of_less_than_50)
			{
				BOOST_CHECK(car.SetSpeed(51));
				BOOST_CHECK(!car.SetGear(Gear::SECOND));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 51);

				BOOST_CHECK(car.SetSpeed(50));
				BOOST_CHECK(car.SetGear(Gear::SECOND));
				CheckCarState(Gear::SECOND, Direction::FORWARD, 50);
			}
		BOOST_AUTO_TEST_SUITE_END()


		struct when_car_moving_forward_in_4th_gear_ : when_engine_is_on_
		{
			when_car_moving_forward_in_4th_gear_()
			{
				car.SetGear(Gear::FIRST);
				car.SetSpeed(30);
				car.SetGear(Gear::THIRD);
				car.SetSpeed(40);
				car.SetGear(Gear::FOURTH);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_car_moving_forward_in_4th_gear, when_car_moving_forward_in_4th_gear_)
			BOOST_AUTO_TEST_CASE(can_not_turn_off_engine)
			{
				BOOST_CHECK(!car.TurnOffEngine());
				BOOST_CHECK(car.IsEngineOn());
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 40);
			}
			BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 40);
			}
			BOOST_AUTO_TEST_CASE(can_not_increase_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(!car.SetSpeed(41));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 40);
			}
			BOOST_AUTO_TEST_CASE(can_reduce_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(car.SetSpeed(20));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_dial_speed_from_40_to_90)
			{
				BOOST_CHECK(!car.SetSpeed(39));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 40);

				BOOST_CHECK(car.SetSpeed(90));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 90);

				BOOST_CHECK(!car.SetSpeed(91));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 90);
			}
			BOOST_AUTO_TEST_CASE(can_switch_5th_gear_if_speed_more_than_50)
			{
				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 40);

				BOOST_CHECK(car.SetSpeed(49));
				BOOST_CHECK(!car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 49);

				BOOST_CHECK(car.SetSpeed(50));
				BOOST_CHECK(car.SetGear(Gear::FIFTH));
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 50);
			}
			BOOST_AUTO_TEST_CASE(can_not_switch_reverse_gear)
			{
				BOOST_CHECK(!car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 40);
			}
			BOOST_AUTO_TEST_CASE(can_switch_to_3th_gear_if_speed_of_less_than_60)
			{
				BOOST_CHECK(car.SetSpeed(61));
				BOOST_CHECK(!car.SetGear(Gear::THIRD));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 61);

				BOOST_CHECK(car.SetSpeed(60));
				BOOST_CHECK(car.SetGear(Gear::THIRD));
				CheckCarState(Gear::THIRD, Direction::FORWARD, 60);
			}
		BOOST_AUTO_TEST_SUITE_END()


		struct when_car_moving_forward_in_5th_gear_ : when_engine_is_on_
		{
			when_car_moving_forward_in_5th_gear_()
			{
				car.SetGear(Gear::FIRST);
				car.SetSpeed(30);
				car.SetGear(Gear::THIRD);
				car.SetSpeed(50);
				car.SetGear(Gear::FIFTH);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_car_moving_forward_in_5th_gear, when_car_moving_forward_in_5th_gear_)
			BOOST_AUTO_TEST_CASE(can_not_turn_off_engine)
			{
				BOOST_CHECK(!car.TurnOffEngine());
				BOOST_CHECK(car.IsEngineOn());
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 50);
			}
			BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 50);
			}
			BOOST_AUTO_TEST_CASE(can_not_increase_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(!car.SetSpeed(51));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 50);
			}
			BOOST_AUTO_TEST_CASE(can_reduce_speed_on_neutral_transmission)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(car.SetSpeed(20));
				CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 20);
			}
			BOOST_AUTO_TEST_CASE(can_dial_speed_from_50_to_150)
			{
				BOOST_CHECK(!car.SetSpeed(49));
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 50);

				BOOST_CHECK(car.SetSpeed(150));
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 150);

				BOOST_CHECK(!car.SetSpeed(151));
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 150);
			}
			BOOST_AUTO_TEST_CASE(can_not_switch_reverse_gear)
			{
				BOOST_CHECK(!car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 50);
			}
			BOOST_AUTO_TEST_CASE(can_switch_to_4th_gear_if_speed_of_less_than_90)
			{
				BOOST_CHECK(car.SetSpeed(91));
				BOOST_CHECK(!car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::FIFTH, Direction::FORWARD, 91);

				BOOST_CHECK(car.SetSpeed(90));
				BOOST_CHECK(car.SetGear(Gear::FOURTH));
				CheckCarState(Gear::FOURTH, Direction::FORWARD, 90);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()	
BOOST_AUTO_TEST_SUITE_END()