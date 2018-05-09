#include "stdafx.h"
#include "../1.1-Complex/Complex.h"

using namespace std;

struct ComplexFixture
{
	double expectedRe = 1.0;
	double expectedIm = -2.0;
	CComplex complex;

	ComplexFixture()
		: complex(expectedRe, expectedIm)
	{
	}

	/*void CheckValueOfComplexNumber(const CComplex& complex, const double expectedRe, const double expectedIm) const
	{
		BOOST_CHECK(complex.Re() == expectedRe);
		BOOST_CHECK(complex.Im() == expectedIm);
	}*/
};

BOOST_FIXTURE_TEST_SUITE(Complex, ComplexFixture)

	BOOST_AUTO_TEST_CASE(has_real_part)
	{
		BOOST_CHECK_CLOSE(complex.Re(), expectedRe, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_imaginary_part)
	{
		BOOST_CHECK_CLOSE(complex.Im(), expectedIm, DBL_EPSILON);
	}
// добавить проверки на неизменение 
	BOOST_AUTO_TEST_CASE(can_get_its_module)
	{
		BOOST_CHECK_CLOSE(complex.GetMagnitude(), sqrt(5), DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(can_get_its_argument)
	{
		BOOST_CHECK_CLOSE(complex.GetArgument(), 0, DBL_EPSILON);
	}
// для 0 не определен

BOOST_AUTO_TEST_SUITE_END()