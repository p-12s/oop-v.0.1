#include "stdafx.h"
#include "../1.4-Solve4/Solve4.h"

using namespace std;

void CheckRoots(const EquationRoot4& equationRoot4, const vector<double>& roots)
{
	BOOST_CHECK_EQUAL(roots.size(), equationRoot4.numRoots);
	for (size_t i = 0; i < equationRoot4.numRoots; ++i)
	{
		BOOST_CHECK_CLOSE(equationRoot4.roots[i], roots[i], DBL_EPSILON);
	}
}

BOOST_AUTO_TEST_SUITE(Function_Solve4)

	BOOST_AUTO_TEST_CASE(requires_a_coefficient_at_x_in_4_degree_not_equal_to_0)
	{
		BOOST_CHECK_THROW(Solve4(0, 0, 0, 0, 0), invalid_argument);
		BOOST_CHECK_NO_THROW(Solve4(1, 0, 0, 0, 0));
	}

	BOOST_AUTO_TEST_CASE(can_have_no_real_roots)
	{
		BOOST_CHECK_THROW(Solve4(1, 2, 3, 4, 5), domain_error);
	}

	BOOST_AUTO_TEST_CASE(can_have_1_root)
	{
		CheckRoots(Solve4(1, 0, 0, 0, 0), { 0 });
		CheckRoots(Solve4(1, 4, 6, 4, 1), { -1 });
	}

	BOOST_AUTO_TEST_CASE(can_have_2_root)
	{
		CheckRoots(Solve4(1, 0, -2, 0, 1), { -1, 1 });
		CheckRoots(Solve4(1, 3, 3, -1, -6), { -2, 1 });
		CheckRoots(Solve4(1, 1, 0, 0, 0), { -1, 0 });
	}

	BOOST_AUTO_TEST_CASE(can_have_3_root)
	{
		CheckRoots(Solve4(2, -3, 1, 0, 0), { 0, 0.5, 1 });
		CheckRoots(Solve4(2, -9, 14, -9, 2), {0.5, 1, 2 });

	}

	BOOST_AUTO_TEST_CASE(can_have_4_root)
	{
		CheckRoots(Solve4(3, 6, -123, -126, 1080), { -6, -4, 3, 5 });
	}
BOOST_AUTO_TEST_SUITE_END()