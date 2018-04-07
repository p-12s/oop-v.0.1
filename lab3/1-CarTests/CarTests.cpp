#include "stdafx.h"
#include "../1-Car/Car.h"

using namespace std;

struct CarDependencies
{
	stringstream output;
};

struct CarFixture : CarDependencies
{
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
		// Direction is depeanding on Gear
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
		{// to inform the reason of impossibility
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
			BOOST_AUTO_TEST_CASE(but_can_to_switch_gear_after_that_only_complete_stop)
			{
				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				BOOST_CHECK(!car.SetSpeed(10));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 5);

				BOOST_CHECK(car.SetSpeed(3));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(!car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::NEUTRAL, Direction::BACK, 3);

				BOOST_CHECK(car.SetSpeed(0));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);

				BOOST_CHECK(car.SetGear(Gear::REVERSE));
				BOOST_CHECK(car.SetSpeed(20));
				CheckCarState(Gear::REVERSE, Direction::BACK, 20);
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct when_car_starts_moving_forward_ : when_engine_is_on_
		{
			when_car_starts_moving_forward_()
			{
				car.SetGear(Gear::FIRST);
				car.SetSpeed(5);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_car_starts_moving_forward, when_car_starts_moving_forward_)
			BOOST_AUTO_TEST_SUITE(in_1th_gear)
				BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
				{
					BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
					CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 5);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(in_2th_gear)
				BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
				{
					BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
					CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 5);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(in_3th_gear)
				BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
				{
					BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
					CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 5);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(in_4th_gear)
				BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
				{
					BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
					CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 5);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(in_5th_gear)
				BOOST_AUTO_TEST_CASE(can_switch_neutral_gear)
				{
					BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
					CheckCarState(Gear::NEUTRAL, Direction::FORWARD, 5);
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()
		// when_car_starts_moving_forward
			// and is in 1th gear	
			// can increase speed up to 30
			// 

			// 2 gear
			// 3 gear
			// 4 gear
			// 5 gear


	BOOST_AUTO_TEST_SUITE_END()	


BOOST_AUTO_TEST_SUITE_END()