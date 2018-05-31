#include "stdafx.h"
#include "../2.1-MyArray/MyArray.h"

using namespace std;

struct EmptyArray
{
	CMyArray<string> stringArr;
	CMyArray<float> floatArr;
};


BOOST_FIXTURE_TEST_SUITE(MyArray, EmptyArray)

	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 0);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 0);
		}
		BOOST_AUTO_TEST_CASE(has_zero_capacity)
		{
			BOOST_CHECK_EQUAL(stringArr.GetCapacity(), 0);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 0);
		}
		BOOST_AUTO_TEST_CASE(has_access_by_index)
		{			
			BOOST_CHECK_THROW(floatArr[-1], out_of_range);
			BOOST_CHECK_THROW(stringArr[0], out_of_range);
			BOOST_CHECK_THROW(stringArr[1], out_of_range);
		}
/*
* вот это можно проделать для пустого массива

* Возможность изменения длины массива при помощи метода Resize(). 
* В случае, если новая длина массива больше прежней, вставляемые в конец массива элементы 
* должны инициализироваться значением по умолчанию для типа T.

* Возможность опустошения массива (удаления всех его элементов) при помощи метода Clear.

* Конструктор копирования и оператор присваивания

* Конструктор перемещения и перемещающий оператор присваивания

* Методы begin() и end(), а также rbegin() и rend(), возвращающие итераторы для перебора 
* элементов вектора в прямом и обратном порядке.
*/
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appending_an_item)
		BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
		{
			stringArr.Append("first");
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 1);
			BOOST_CHECK_EQUAL(stringArr.GetCapacity(), 1);
			stringArr.Append("second");
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 2);
			BOOST_CHECK_EQUAL(stringArr.GetCapacity(), 2);
			stringArr.Append("third");
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 3);
			BOOST_CHECK_EQUAL(stringArr.GetCapacity(), 4);

			floatArr.Append(1.f);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 1);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 1);
			floatArr.Append(2.f);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 2);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 2);
			floatArr.Append(3.f);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 3);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 4);
		}
		/*
		 *в требованиях нет такого функционала
		 *BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
		{
			arr.Append(1);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 1);
			arr.Append(2);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 2);
			arr.Append(3);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 3);
			arr.Append(4);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 4);
		}*/
		BOOST_AUTO_TEST_CASE(can_accessible_by_index)
		{
			stringArr.Append("first");
			BOOST_CHECK_EQUAL(stringArr[0], "first");//в примере arr[1].value, т.к. value - поле тестового массива
			stringArr.Append("second");
			BOOST_CHECK_EQUAL(stringArr[1], "second");

			BOOST_CHECK_THROW(stringArr[2], std::out_of_range);
			BOOST_CHECK_THROW(stringArr[-1], std::out_of_range);

			floatArr.Append(123.f);
			BOOST_CHECK_EQUAL(floatArr[0], 123.f);
			floatArr.Append(456.f);
			BOOST_CHECK_EQUAL(floatArr[1], 456.f);			

			BOOST_CHECK_THROW(floatArr[2], std::out_of_range);
			BOOST_CHECK_THROW(floatArr[-1], std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_be_resized)
		{
			floatArr.Append(1.f);
			floatArr.Append(2.f);
			floatArr.Append(3.f);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 3);
			floatArr.Resize(5);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 5);
			BOOST_CHECK_EQUAL(floatArr[0], 1.f);
			BOOST_CHECK_EQUAL(floatArr[1], 2.f);
			BOOST_CHECK_EQUAL(floatArr[2], 3.f);
			BOOST_CHECK_EQUAL(floatArr[3], 0.f);
			BOOST_CHECK_EQUAL(floatArr[4], 0.f);
			BOOST_CHECK_THROW(floatArr[5], std::out_of_range);

			floatArr.Resize(2);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 2);
			BOOST_CHECK_EQUAL(floatArr[0], 1.f);
			BOOST_CHECK_EQUAL(floatArr[1], 2.f);
			BOOST_CHECK_THROW(floatArr[2], std::out_of_range);
		}
		/*BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			for (auto i = 0; i < 6; ++i)
			{
				arr.Append(i);
			}
			BOOST_CHECK_EQUAL(arr.GetSize(), 6u);
			BOOST_CHECK_NO_THROW(arr.Clear());
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
		}*/
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
