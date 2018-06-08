#include "stdafx.h"
#include "../2.1-MyArray/MyArray.h"
#include <boost/range/adaptor/reversed.hpp>

using namespace std;

struct MyIteratorFixture
{
	CMyArray<float> floatArr;
	CMyIterator<float> iterator;
	CMyIterator<float> const_iterator;

	MyIteratorFixture()
		: floatArr()
		, iterator()
		, const_iterator()
	{
		for (auto i = 0; i < 6; ++i)
			floatArr.Append(static_cast<float>(i));

		iterator = floatArr.begin();
		const_iterator = floatArr.begin();
	}
};

BOOST_FIXTURE_TEST_SUITE(MyIterator, MyIteratorFixture)
	BOOST_AUTO_TEST_SUITE(common)
		BOOST_AUTO_TEST_CASE(can_refer_to_the_begin)
		{
			BOOST_CHECK(*iterator == 0);
			BOOST_CHECK(*const_iterator == 0);
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

			++const_iterator;
			BOOST_CHECK_EQUAL(*const_iterator, 1.f);

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
			for_each(floatArr.begin(), floatArr.end(), [&](auto &it) {
				stream << it << " ";
			});
			BOOST_CHECK_EQUAL(stream.str(), "0 1 2 3 4 5 ");

			stream.str("");
			for (auto const val : floatArr)
			{
				stream << val << " ";
			}
			BOOST_CHECK_EQUAL(stream.str(), "0 1 2 3 4 5 ");
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	struct reverse_ : MyIteratorFixture
	{
		reverse_iterator<CMyIterator<float>> iterator;

		CMyIterator<float> reverse_iterator;
		CMyIterator<float> reverse_const_iterator;

		reverse_()
			: iterator(floatArr.rbegin())
			, reverse_iterator(floatArr.end())
			, reverse_const_iterator(floatArr.end())
		{
		}
	};

	BOOST_FIXTURE_TEST_SUITE(reverse, reverse_)
		BOOST_AUTO_TEST_CASE(refers_to_the_end)
		{
			auto a = reverse_iterator;
			BOOST_CHECK(reverse_iterator == floatArr.end());
		}	
		BOOST_AUTO_TEST_CASE(which_can_be_incremented_with_postfix_form)
		{
			reverse_iterator--;
			BOOST_CHECK_EQUAL(*reverse_iterator--, 5);
		}		
		BOOST_AUTO_TEST_CASE(can_be_decremented_with_prefix_form)
		{
			--reverse_iterator;
			BOOST_CHECK_EQUAL(*iterator, 5);

			*reverse_iterator = 10;
			BOOST_CHECK_EQUAL(floatArr[5], 10);
		}		
		BOOST_AUTO_TEST_CASE(can_be_decremented_with_postfix_form)
		{
			reverse_iterator--;
			reverse_iterator--;
			BOOST_CHECK_EQUAL(*iterator, 5);
		}		
		BOOST_AUTO_TEST_CASE(can_be_addicted_with_number)
		{
			auto it = reverse_iterator - 2;
			BOOST_CHECK_EQUAL(*it, floatArr[4]);
		}
		BOOST_AUTO_TEST_CASE(can_be_substracted_from_another_iterator)
		{
			auto it = floatArr.begin();
			BOOST_CHECK_EQUAL(reverse_iterator - it, 6);
		}	
		BOOST_AUTO_TEST_CASE(can_be_checked_for_equality)
		{
			BOOST_CHECK(reverse_iterator == floatArr.end());
			BOOST_CHECK(reverse_iterator != floatArr.begin());
		}
		BOOST_AUTO_TEST_CASE(has_less_operator)
		{
			auto it = reverse_iterator - 2;
			BOOST_CHECK(reverse_iterator > it);
		}		
		BOOST_AUTO_TEST_CASE(has_greater_operator)
		{
			auto it = reverse_iterator - 2;
			BOOST_CHECK(it < reverse_iterator);
		}
		BOOST_AUTO_TEST_CASE(has_less_or_equal_operator)
		{
			auto it = reverse_iterator - 2;
			BOOST_CHECK(reverse_iterator >= it);
		}
		BOOST_AUTO_TEST_CASE(has_greater_or_equal_operator)
		{
			auto it = reverse_iterator - 2;
			BOOST_CHECK(it <= reverse_iterator);
		}
		BOOST_AUTO_TEST_CASE(stl_compatible)
		{
			stringstream stream;
			--reverse_iterator;
			for (reverse_iterator; reverse_iterator != floatArr.begin(); --reverse_iterator)
			{
				stream << *reverse_iterator << " ";
			}
			BOOST_CHECK_EQUAL(stream.str(), "5 4 3 2 1 ");
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
