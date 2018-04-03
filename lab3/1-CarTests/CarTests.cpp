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

	void CheckCarState(Gear expectedGear, Direction expectedDirection, int expectedSpeed) const
	{
		BOOST_CHECK(car.GetGear() == expectedGear);
		BOOST_CHECK(car.GetDirection() == expectedDirection);
		BOOST_CHECK(car.GetSpeed() == expectedSpeed);
	}
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_SUITE(general_behavior)
		BOOST_AUTO_TEST_CASE(engine_is_not_start_by_default)
		{
			BOOST_CHECK(!car.IsEngineOn());
		}
		BOOST_AUTO_TEST_CASE(default_speed_is_0)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		BOOST_AUTO_TEST_CASE(default_gear_is_neutral)
		{
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
		}
		BOOST_AUTO_TEST_CASE(default_direction_is_stands_still)
		{
			BOOST_CHECK(car.GetDirection() == Direction::STOP);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_the_engine_is_off)		
		BOOST_AUTO_TEST_CASE(gear_can_be_switched_only_to_neutral)
		{
			BOOST_CHECK(!car.SetGear(Gear::REVERSE));
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);

			BOOST_CHECK(car.SetGear(Gear::NEUTRAL));
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);

			BOOST_CHECK(!car.SetGear(Gear::FIRST));
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);

			BOOST_CHECK(!car.SetGear(Gear::SECOND));
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);

			BOOST_CHECK(!car.SetGear(Gear::THIRD));
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);

			BOOST_CHECK(!car.SetGear(Gear::FOURTH));
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);

			BOOST_CHECK(!car.SetGear(Gear::FIFTH));
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
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

BOOST_AUTO_TEST_SUITE_END()