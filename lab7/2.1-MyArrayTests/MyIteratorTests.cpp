#include "stdafx.h"
#include "../2.1-MyArray/MyArray.h"

using namespace std;

struct ArrayItem
{
	ArrayItem(int value = 0) : value(value)
	{}
	int value;
};

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};

struct has_iterators_ : EmptyStringArray //CMyArray<ArrayItem> arr;
{
	CMyIterator<ArrayItem> iterator;
	has_iterators_()
	{
		for (auto i = 0; i < 6; ++i)
			arr.Append(i);

		iterator = arr.begin();

		auto aa = *iterator;
		auto b = iterator + 1;
		++iterator;
	}
};


struct MyIteratorFixture
{
	CMyArray<float> floatArr;
	CMyIterator<float> iterator;
	
	MyIteratorFixture()
		: floatArr()
		, iterator()
	{
		for (auto i = 0; i < 6; ++i)
			floatArr.Append(static_cast<float>(i));
		iterator = floatArr.begin();
	}
};

BOOST_FIXTURE_TEST_SUITE(MyIterator, MyIteratorFixture) //, has_iterators_ MyIteratorFixture
	BOOST_AUTO_TEST_SUITE(common)
		BOOST_AUTO_TEST_CASE(can_refer_to_the_begin)
		{
			BOOST_CHECK(*iterator == 0);
		}
		BOOST_AUTO_TEST_CASE(can_refer_to_the_end)
		{
			iterator = floatArr.end();
			BOOST_CHECK(iterator == floatArr.end());
			BOOST_CHECK(iterator != floatArr.begin());
		}
		BOOST_AUTO_TEST_CASE(can_be_incremented_with_prefix_form)
		{
			++iterator;
			BOOST_CHECK_EQUAL(*iterator, 1.f);

			++iterator;
			BOOST_CHECK_EQUAL(*iterator, 2.f);
		}
		BOOST_AUTO_TEST_CASE(can_be_incremented_with_postfix_form)
		{
			BOOST_CHECK_EQUAL(*iterator++, 0);
			BOOST_CHECK_EQUAL(*iterator, 1.f);
		}
		BOOST_AUTO_TEST_CASE(can_be_decremented_with_prefix_form)
		{
			++iterator;
			BOOST_CHECK_EQUAL(*iterator, 1.f);
			--iterator;
			BOOST_CHECK_EQUAL(*iterator, 0);

			*iterator = 10.f;
			BOOST_CHECK_EQUAL(floatArr[0], 10);
		}	
		BOOST_AUTO_TEST_CASE(can_be_decremented_with_postfix_form)
		{
			iterator++;
			BOOST_CHECK_EQUAL(*iterator, 1.f);
			iterator--;
			BOOST_CHECK_EQUAL(*iterator, 0);
		}
		BOOST_AUTO_TEST_CASE(can_be_addicted_with_number)
		{
			auto it = iterator + 3;
			BOOST_CHECK_EQUAL(*it, floatArr[3]);

			it = 3 + iterator;
			BOOST_CHECK_EQUAL(*it, floatArr[3]);
		}
		BOOST_AUTO_TEST_CASE(can_be_substracted_with_number)
		{
			auto it = floatArr.end() - 3;
			BOOST_CHECK_EQUAL(*it, 3);
		}
		BOOST_AUTO_TEST_CASE(can_be_substracted_from_another_iterator)
		{
			auto it = floatArr.end();
			BOOST_CHECK_EQUAL(it - iterator, 6);
			BOOST_CHECK_EQUAL(iterator - it, -6);
		}
		BOOST_AUTO_TEST_CASE(elements_can_be_accessed_with_offset)
		{
			BOOST_CHECK_EQUAL(iterator[2], 2);
			iterator[2] = 0;
			BOOST_CHECK_EQUAL(iterator[2], 0);
		}
		BOOST_AUTO_TEST_CASE(can_be_checked_for_equality)
		{
			BOOST_CHECK(iterator == floatArr.begin());
			BOOST_CHECK(iterator != floatArr.end());
		}
		BOOST_AUTO_TEST_CASE(has_less_operator)
		{
			auto it = iterator + 2;
			BOOST_CHECK(iterator < it);
			BOOST_CHECK(!(it < iterator));
		}
		BOOST_AUTO_TEST_CASE(has_greater_operator)
		{
			auto it = iterator + 2;
			BOOST_CHECK(it > iterator);
			BOOST_CHECK(!(iterator > it));
		}		
		BOOST_AUTO_TEST_CASE(has_less_or_equal_operator)
		{
			auto it = iterator + 2;
			BOOST_CHECK(iterator <= it);
			BOOST_CHECK(!(it <= iterator));
		}
		
		BOOST_AUTO_TEST_CASE(has_greater_or_equal_operator)
		{
			auto it = iterator + 2;
			BOOST_CHECK(it >= iterator);
			BOOST_CHECK(!(iterator >= it));
		}
		BOOST_AUTO_TEST_CASE(stl_compatible)
		{
			stringstream stream;
			for (auto &el : floatArr)
			{
				stream << el << " ";
			}
			BOOST_CHECK_EQUAL(stream.str(), "0 1 2 3 4 5 ");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(reverse)
		BOOST_AUTO_TEST_CASE(test)
		{
			BOOST_CHECK(true);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
