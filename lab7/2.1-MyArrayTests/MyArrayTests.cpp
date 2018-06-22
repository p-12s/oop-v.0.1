#include "stdafx.h"
#include "../2.1-MyArray/MyArray.h"

using namespace std;

struct MyArrayFixture
{
	CMyArray<string> stringArr;
	CMyArray<float> floatArr;

	MyArrayFixture()
		: stringArr()
		, floatArr()
	{
	}
};

template <typename T>
bool ArraysAreEqual(CMyArray<T> const& arr1, CMyArray<T> const& arr2)
{
	for (size_t i = 0; i < arr1.GetSize(); ++i)
	{
		if (arr1[i] != arr2[i])
			return false;
	}
	return arr1.GetSize() == arr2.GetSize();
}

template <typename T>
void CheckSizeAndCapacity(CMyArray<T> const& arr1, const size_t size, const size_t capacity)
{
	BOOST_CHECK(arr1.GetSize() == size && arr1.GetCapacity() == capacity);
}

template <typename T>
void CheckArrayItems(CMyArray<T> const& arr1, const vector<T>& expectedItems, const size_t capacity)
{
	for (size_t i = 0; i < arr1.GetSize(); ++i )
	{
		BOOST_CHECK(arr1[i] == expectedItems[i]);
		BOOST_CHECK_NO_THROW((arr1[i] == expectedItems[i]));
	}
	BOOST_CHECK(arr1.GetSize() == expectedItems.size());
}


BOOST_FIXTURE_TEST_SUITE(MyArray, MyArrayFixture)

	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty_and_with_zero_capacity)
		{
			CheckArrayItems(floatArr, {}, 0);
			CheckArrayItems(stringArr, {}, 0);
		}
		BOOST_AUTO_TEST_CASE(has_not_access_by_index)
		{			
			BOOST_CHECK_THROW((floatArr[-1] == -1), out_of_range);
			BOOST_CHECK_THROW(floatArr[-1], out_of_range);
			BOOST_CHECK_THROW(stringArr[0], exception);
			BOOST_CHECK_THROW(stringArr[1], out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(until_it_is_just_created_and_empty_it)
		BOOST_AUTO_TEST_CASE(can_be_increased)
		{
			floatArr.Resize(2);
			BOOST_CHECK_THROW(floatArr[-1], std::out_of_range);
			CheckArrayItems(floatArr, { 0.f, 0.f }, 2);
			BOOST_CHECK_THROW(floatArr[2], std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_be_cleaned)
		{
			BOOST_CHECK_NO_THROW(floatArr.Clear());
			CheckArrayItems(floatArr, {}, 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_appending_items_ : MyArrayFixture
	{
		after_appending_items_()
		{
			floatArr.Append(1.f);
			floatArr.Append(2.f);
			floatArr.Append(3.f);
			CheckArrayItems(floatArr, { 1.f, 2.f, 3.f }, 4);

			stringArr.Append("a");
			stringArr.Append("b");
			stringArr.Append("c");
			CheckArrayItems(stringArr, { "a", "b", "c" }, 4);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(after_appending_items, after_appending_items_)
		BOOST_AUTO_TEST_CASE(can_accessible_by_index)
		{
			BOOST_CHECK_THROW(floatArr[-1], std::out_of_range);
			CheckArrayItems(floatArr, { 1.f, 2.f, 3.f }, 4);
			BOOST_CHECK_THROW(floatArr[3], std::out_of_range);

			BOOST_CHECK_THROW(stringArr[-1], std::out_of_range);
			CheckArrayItems(stringArr, { "a", "b", "c" }, 4);
			BOOST_CHECK_THROW(stringArr[3], std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_be_resized)
		{
			floatArr.Resize(4);
			CheckArrayItems(floatArr, { 1.f, 2.f, 3.f, 0.f }, 4);
			BOOST_CHECK_THROW(floatArr[4], std::out_of_range);

			floatArr.Resize(6);
			CheckArrayItems(floatArr, { 1.f, 2.f, 3.f, 0.f, 0.f, 0.f }, 6);
			BOOST_CHECK_THROW(floatArr[6], std::out_of_range);

			floatArr.Resize(2);
			CheckArrayItems(floatArr, { 1.f, 2.f }, 6);
			BOOST_CHECK_THROW(floatArr[2], std::out_of_range);

			floatArr.Resize(1);
			CheckArrayItems(floatArr, { 1.f }, 6);
			BOOST_CHECK_THROW(floatArr[1], std::out_of_range);

			floatArr.Resize(0);
			CheckArrayItems(floatArr, {}, 6);
			BOOST_CHECK_THROW(floatArr[0], std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK_NO_THROW(floatArr.Clear());
			CheckArrayItems(floatArr, {}, 0);

			BOOST_CHECK_NO_THROW(stringArr.Clear());
			CheckArrayItems(stringArr, {}, 0);
		}
	BOOST_AUTO_TEST_SUITE_END()	

	BOOST_FIXTURE_TEST_SUITE(copy_constructor, after_appending_items_)
		BOOST_AUTO_TEST_CASE(does_not_change_the_value_of_items_of_the_source_array)
		{
			auto copyFloatArr(floatArr);
			CheckArrayItems(copyFloatArr, { 1.f, 2.f, 3.f }, 3);
			CheckArrayItems(floatArr, { 1.f, 2.f, 3.f }, 4);

			auto copyStringArr(stringArr);
			CheckArrayItems(copyStringArr, { "a", "b", "c" }, 4);
			CheckArrayItems(stringArr, { "a", "b", "c" }, 4);
		}
		BOOST_AUTO_TEST_CASE(changes_in_the_original_object_are_not_reflected_on_the_copy)
		{
			auto copyFloatArr(floatArr);
			floatArr[0] = 10;
			CheckArrayItems(copyFloatArr, { 1.f, 2.f, 3.f }, 3);
			CheckArrayItems(floatArr, { 10.f, 2.f, 3.f }, 4);

			auto copyStringArr(stringArr);
			copyStringArr[0] = "NEW";
			CheckArrayItems(copyStringArr, { "NEW", "b", "c" }, 3);
			CheckArrayItems(stringArr, { "a", "b", "c" }, 4);
		}
		BOOST_AUTO_TEST_CASE(can_assign_an_object_to_itself)
		{
			auto copyFloatArr(floatArr);
			floatArr = floatArr;
			BOOST_CHECK(ArraysAreEqual(copyFloatArr, floatArr));
			floatArr = copyFloatArr;
			BOOST_CHECK(ArraysAreEqual(copyFloatArr, floatArr));
		}
		BOOST_AUTO_TEST_CASE(has_copy_operator)
		{
			auto copyFloatArr = floatArr;
			BOOST_CHECK(ArraysAreEqual(copyFloatArr, floatArr));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(move_constructor, after_appending_items_)
		BOOST_AUTO_TEST_CASE(does_not_change_the_value_of_the_capacity_of_the_source_array)
		{
			auto movedFloatArr(move(floatArr));
			CheckArrayItems(movedFloatArr, { 1.f, 2.f, 3.f }, 4);
		}
		BOOST_AUTO_TEST_CASE(original_array_is_empty)
		{
			auto movedFloatArr(move(floatArr));
			CheckArrayItems(floatArr, {}, 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()