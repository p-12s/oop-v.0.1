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
			BOOST_CHECK_EQUAL(stringArr.GetSize(), 0u);
			BOOST_CHECK_EQUAL(floatArr.GetSize(), 0u);
		}
		BOOST_AUTO_TEST_CASE(has_zero_capacity)
		{
			BOOST_CHECK_EQUAL(stringArr.GetCapacity(), 0u);
			BOOST_CHECK_EQUAL(floatArr.GetCapacity(), 0u);
		}
		BOOST_AUTO_TEST_CASE(has_access_by_index)
		{
			BOOST_CHECK_THROW(stringArr[0], std::out_of_range);
			BOOST_CHECK_THROW(floatArr[-1], std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


// has_the_ability_to_obtain_the_number_of_elements
// has_the_ability_to_access_the_item_by_index_with_[]
// throws_an_exception_if_the_index_of_an_element_is_outside_the_array
// has_the_ability_to_change_the_length_of_an_array_using_the_resize_method
// with_an_increased_length_initializes_the_element_with_the_default_value
// has_clear_for_cleaning
// has_a_copy_constructor
// has_an_assignment_operator
// has_a_move_constructor
// has_a_relocating_assignment_operator
// has_begin_and_end_methods
// has_rbegin_and_rend_methods