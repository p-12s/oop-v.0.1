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

	struct when_the_engine_is_on_ : CarFixture
	{
		when_the_engine_is_on_()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_the_engine_is_first_turned_on, when_the_engine_is_on_)
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
			BOOST_AUTO_TEST_CASE(can_be_turned_first_gear)
			{
				BOOST_CHECK(car.SetGear(Gear::FIRST));
				BOOST_CHECK(car.GetGear() == Gear::FIRST);
			}
			BOOST_AUTO_TEST_CASE(engine_can_be_turned_off_if_only_gear_is_neutral)
			{
				BOOST_CHECK(car.SetGear(Gear::FIRST));
				BOOST_CHECK(car.SetSpeed(10));
				BOOST_CHECK(car.GetGear() == Gear::FIRST);
				BOOST_CHECK(car.GetDirection() == Direction::STOP);
				BOOST_CHECK(car.GetSpeed() == 0);
				//CheckCarState(Gear::FIRST, Direction::FORWARD, 10);
				BOOST_CHECK(!car.TurnOffEngine());
				BOOST_CHECK(car.IsEngineOn());

				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
				//BOOST_CHECK(!car.TurnOffEngine());
				//BOOST_CHECK(car.IsEngineOn());

				car.SetSpeed(0);
				//BOOST_CHECK(car.TurnOffEngine());
				//BOOST_CHECK(!car.IsEngineOn());				
			}
			BOOST_AUTO_TEST_CASE(can_be_turned_reverse_gear_only_if_first_or_neutral_gear_is_on)
			{
				BOOST_CHECK(car.SetGear(Gear::FIRST));
				car.SetSpeed(10);
				//BOOST_CHECK(!car.SetGear(Gear::REVERSE));
				//CheckCarState(Gear::FIRST, Direction::FORWARD, 10);

				car.SetSpeed(0);
				BOOST_CHECK(car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::REVERSE, Direction::BACK, 0);

				BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
				CheckCarState(Gear::NEUTRAL, Direction::STOP, 0);
				BOOST_CHECK(car.SetGear(Gear::REVERSE));
				CheckCarState(Gear::REVERSE, Direction::BACK, 0);
			}
		BOOST_AUTO_TEST_SUITE_END()		

		struct when_the_car_starts_moving_backwards_ : when_the_engine_is_on_
		{
			when_the_car_starts_moving_backwards_()
			{
				car.SetGear(Gear::REVERSE);
				car.SetSpeed(5);
			}
		};
		// when_car_starts_moving_backwards
			// can increase speed up to 20
			// Can not switch to gear from 1th to 5th	
			// can switch neutral gear
			// can switch 1th gear if speed is reset to 0

		BOOST_FIXTURE_TEST_SUITE(when_car_starts_moving_backwards, when_the_car_starts_moving_backwards_)

			BOOST_AUTO_TEST_CASE(test_test)
			{
				car.SetSpeed(0);
				//CheckCarState(Gear::REVERSE, Direction::BACK, 5);
			}

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