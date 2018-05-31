#include "stdafx.h"
#include "../2.1-MyArray/MyArray.h"

using namespace std;

struct EmptyArray
{
	CMyArray<string> stringArr;
	CMyArray<float> floatArr;
};

template <typename T>
bool ArraysAreEqual(CMyArray<T> const& arr1, CMyArray<T> const& arr2)
{
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (arr1[i] != arr2[i])
			return false;
	}
	return arr1.GetSize() == arr2.GetSize() && arr1.GetCapacity() == arr2.GetCapacity();
}

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
* вот это можно проделать дл€ пустого массива

* ¬озможность изменени€ длины массива при помощи метода Resize(). 
* ¬ случае, если нова€ длина массива больше прежней, вставл€емые в конец массива элементы 
* должны инициализироватьс€ значением по умолчанию дл€ типа T.

* ¬озможность опустошени€ массива (удалени€ всех его элементов) при помощи метода Clear.

*  онструктор копировани€ и оператор присваивани€

*  онструктор перемещени€ и перемещающий оператор присваивани€

* ћетоды begin() и end(), а также rbegin() и rend(), возвращающие итераторы дл€ перебора 
* элементов вектора в пр€мом и обратном пор€дке.
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
		 *в требовани€х нет такого функционала
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
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 4);
			floatArr.Resize(5);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 5);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 5);
			BOOST_CHECK_EQUAL(floatArr[0], 1.f);
			BOOST_CHECK_EQUAL(floatArr[1], 2.f);
			BOOST_CHECK_EQUAL(floatArr[2], 3.f);
			BOOST_CHECK_EQUAL(floatArr[3], 0.f);
			BOOST_CHECK_EQUAL(floatArr[4], 0.f);
			BOOST_CHECK_THROW(floatArr[5], std::out_of_range);
			floatArr.Resize(2);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 2);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 2);
			BOOST_CHECK_EQUAL(floatArr[0], 1.f);
			BOOST_CHECK_EQUAL(floatArr[1], 2.f);
			BOOST_CHECK_THROW(floatArr[2], std::out_of_range);

			stringArr.Append("a");
			stringArr.Append("b");
			stringArr.Append("c");
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 3);
			BOOST_CHECK_EQUAL(stringArr.GetCapacity(), 4);
			stringArr.Resize(5);
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 5);
			BOOST_CHECK_EQUAL(stringArr.GetCapacity(), 5);
			BOOST_CHECK_EQUAL(stringArr[0], "a");
			BOOST_CHECK_EQUAL(stringArr[1], "b");
			BOOST_CHECK_EQUAL(stringArr[2], "c");
			BOOST_CHECK_EQUAL(stringArr[3], "");
			BOOST_CHECK_EQUAL(stringArr[4], "");
			BOOST_CHECK_THROW(stringArr[5], std::out_of_range);
			stringArr.Resize(2);
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 2);
			BOOST_CHECK_EQUAL(stringArr.GetCapacity(), 2);
			BOOST_CHECK_EQUAL(stringArr[0], "a");
			BOOST_CHECK_EQUAL(stringArr[1], "b");
			BOOST_CHECK_THROW(stringArr[2], std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			for (int i = 0; i < 10; ++i)//TODO int-auto
				floatArr.Append(static_cast<float>(i));

			BOOST_CHECK_EQUAL(floatArr.GetSize(), 10);
			BOOST_CHECK_NO_THROW(floatArr.Clear());
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 0);

			for (int i = 0; i < 10; ++i)//TODO int-auto
				stringArr.Append("Hello World");

			BOOST_CHECK_EQUAL(stringArr.GetSize(), 10);
			BOOST_CHECK_NO_THROW(stringArr.Clear());
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 0);
		}
	BOOST_AUTO_TEST_SUITE_END() // TODO может еще что добавить?

	BOOST_AUTO_TEST_SUITE(copy_constructor)

		BOOST_AUTO_TEST_CASE(does_not_change_the_value_of_the_capacity_of_the_source_array)
		{
			for (auto i = 0; i < 5; ++i)
				floatArr.Append(static_cast<float>(i));				

			BOOST_CHECK_EQUAL(floatArr.GetSize(), 5);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 8);

			auto copyArr(floatArr); // конструктор копировани€
			BOOST_CHECK_EQUAL(copyArr.GetSize(), 5);
			BOOST_CHECK_EQUAL(copyArr.GetCapacity(), 8);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 5);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 8);
		}
		BOOST_AUTO_TEST_CASE(changes_in_the_original_object_are_not_reflected_on_the_copy)
		{
			for (auto i = 0; i < 6; ++i)
				floatArr.Append(static_cast<float>(i));

			auto copyArr(floatArr);
			auto anotherCopyArr(floatArr);
			floatArr[0] = 10;
			BOOST_CHECK(!ArraysAreEqual(copyArr, floatArr));
			BOOST_CHECK(ArraysAreEqual(copyArr, anotherCopyArr));
		}
		BOOST_AUTO_TEST_CASE(can_assign_an_object_to_itself)
		{
			for (auto i = 0; i < 4; ++i)
				floatArr.Append(static_cast<float>(i));

			auto copyArr(floatArr);
			floatArr = floatArr;
			BOOST_CHECK(ArraysAreEqual(copyArr, floatArr));
		}
		BOOST_AUTO_TEST_CASE(has_copy_operator)
		{
			for (auto i = 0; i < 4; ++i)
				floatArr.Append(static_cast<float>(i));

			auto copyArr = floatArr;
			BOOST_CHECK(ArraysAreEqual(copyArr, floatArr));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(move_constructor)//TODO должен уничтожать предыдущий экземпл€р класса
		BOOST_AUTO_TEST_CASE(does_not_change_the_value_of_the_capacity_of_the_source_array)
		{
			for (auto i = 0; i < 5; ++i)
				floatArr.Append(static_cast<float>(i));

			size_t size = floatArr.GetSize();
			size_t capacity = floatArr.GetCapacity();
			auto newArr(move(floatArr));
			BOOST_CHECK_EQUAL(newArr.GetSize(), size);
			BOOST_CHECK_EQUAL(newArr.GetCapacity(), capacity);
		}

		BOOST_AUTO_TEST_CASE(original_array_is_empty)//не нужно ли удалить исходный объект?
		{
			for (auto i = 0; i < 5; ++i)
				floatArr.Append(static_cast<float>(i));

			auto newArray(move(floatArr));
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 0);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
