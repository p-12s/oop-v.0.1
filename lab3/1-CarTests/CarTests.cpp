#include "stdafx.h"
#include "../1-Car/Car.h"

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_SUITE(general_behavior)
		BOOST_AUTO_TEST_CASE(engine_is_not_start_by_default)
		{
			BOOST_CHECK(!car.IsCarRunning());
		}
		BOOST_AUTO_TEST_CASE(none)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		BOOST_AUTO_TEST_CASE(none2)
		{
			BOOST_CHECK(car.GetGear() == Gear::NEUTRAL);
		}		
	BOOST_AUTO_TEST_SUITE_END()

		/*BOOST_AUTO_TEST_CASE(engine_can_be_switched_on_by_default)
		{
		BOOST_CHECK(car.TurnOnEngine());
		CheckCarState(Gear::NEUTRAL, 0, Direction::STOP);
		}
		BOOST_AUTO_TEST_CASE(engine_can_be_switched_on_and_then_can_be_switched_off_by_default)
		{
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.TurnOffEngine());
		CheckCarState(Gear::NEUTRAL, 0, Direction::STOP);
		}*/
BOOST_AUTO_TEST_SUITE_END()

/*
// ������ 
BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)
	// ���������� ��������
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
	}
	// �� ����� ����������� ����� � ����������� ���������
	BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
	{
		BOOST_CHECK(!tv.SelectChannel(87));
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	// ����� ���� �������
	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		tv.TurnOn();
		BOOST_CHECK(tv.IsTurnedOn());
	}
	// ���������� ���������� 0 �����
	BOOST_AUTO_TEST_CASE(displays_channel_0_by_default)
	{
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	struct when_turned_on_ : TVSetFixture
	{
		when_turned_on_()
		{
			tv.TurnOn();
		}
	};

	// ����� ���������
	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
		// ���������� ����� 1
		BOOST_AUTO_TEST_CASE(displays_channel_one)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}
		// ����� ���������
		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			tv.TurnOff();
			BOOST_CHECK(!tv.IsTurnedOn());
		}
		// ��������� ������� ����� �� 1 �� 99
		BOOST_AUTO_TEST_CASE(can_select_channel_from_1_to_99)
		{
			BOOST_CHECK(tv.SelectChannel(1));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

			BOOST_CHECK(tv.SelectChannel(99));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

			// �������� ����� ����� 1 � 99
			BOOST_CHECK(tv.SelectChannel(42));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

			// ��� ������� ������� ����� �� ��������� [1; 99] 
			// ��������� �� ������ ������ ���� �����
			BOOST_CHECK(!tv.SelectChannel(0));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

			BOOST_CHECK(!tv.SelectChannel(100));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);
		}
		BOOST_AUTO_TEST_SUITE_END()

		struct after_subsequent_turning_on_ : when_turned_on_
		{
			after_subsequent_turning_on_()
			{
				tv.SelectChannel(33);
				tv.TurnOff();
				tv.TurnOn();
			}
		};

		// ����� ���������� ���������
		BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
			// ��������������� ��������� ��������� �����
			BOOST_AUTO_TEST_CASE(restores_last_selected_channel)
			{
				BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
			}
			BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
*/