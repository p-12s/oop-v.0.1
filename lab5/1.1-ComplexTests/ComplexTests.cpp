#include "stdafx.h"
#include "../1.1-Complex/Complex.h"

using namespace std;

struct ComplexFixture
{
	double expectedRe = 1.0;
	double expectedIm = -2.0;
	CComplex complex1;

	ComplexFixture()
		: complex1(expectedRe, expectedIm)
	{
	}

	void AreComplexNumbersEqual(const CComplex& arg1, const CComplex& arg2) const
	{
		BOOST_CHECK_CLOSE(arg1.Re(), arg2.Re(), DBL_EPSILON);
		BOOST_CHECK_CLOSE(arg1.Im(), arg2.Im(), DBL_EPSILON);
	}

	void CheckArgumentsOfComplexNumber(const CComplex& arg1, const double re, const double im) const
	{
		BOOST_CHECK_CLOSE(arg1.Re(), re, DBL_EPSILON);
		BOOST_CHECK_CLOSE(arg1.Im(), im, DBL_EPSILON);
	}
};

BOOST_FIXTURE_TEST_SUITE(Complex, ComplexFixture)

	BOOST_AUTO_TEST_CASE(has_real_part)
	{
		BOOST_CHECK_CLOSE(complex1.Re(), expectedRe, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(has_imaginary_part)
	{
		BOOST_CHECK_CLOSE(complex1.Im(), expectedIm, DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(can_get_its_module)
	{
		CComplex coordinateCenter = CComplex(0, 0);
		BOOST_CHECK_CLOSE(coordinateCenter.GetMagnitude(), 0, DBL_EPSILON);

		BOOST_CHECK_CLOSE(complex1.GetMagnitude(), sqrt(pow(expectedRe, 2) + pow(expectedIm, 2)), DBL_EPSILON);
	}
	BOOST_AUTO_TEST_CASE(can_get_its_argument)
	{
		CComplex coordinateCenter = CComplex(0, 0);
		BOOST_CHECK_CLOSE(coordinateCenter.GetArgument(), 0, DBL_EPSILON);

		CComplex centerBottom = CComplex(0, -2);
		BOOST_CHECK_CLOSE(centerBottom.GetArgument(), DBL_MAX, DBL_EPSILON);

		CComplex rightTopQuarter = CComplex(1, 2);
		BOOST_CHECK_CLOSE(rightTopQuarter.GetArgument(), 1.1071487177940904, DBL_EPSILON);
		
		CComplex rightBottomQuarter = CComplex(1, -2);
		BOOST_CHECK_CLOSE(rightBottomQuarter.GetArgument(), -1.1071487177940904, DBL_EPSILON);

		CComplex leftTopQuarter = CComplex(-1, 2);
		BOOST_CHECK_CLOSE(leftTopQuarter.GetArgument(), 2.0344439357957027, DBL_EPSILON);

		CComplex leftBottomQuarter = CComplex(-1, -2);
		BOOST_CHECK_CLOSE(leftBottomQuarter.GetArgument(), -2.0344439357957027, DBL_EPSILON);
	}

	struct Complex2Fixture : ComplexFixture
	{
		double real = -10;
		double expectedRe = 5.0; // 1
		double expectedIm = -9.0; // -2
		CComplex complex2;

		Complex2Fixture()
			: complex2(expectedRe, expectedIm)
		{
		}
	};
	BOOST_FIXTURE_TEST_SUITE(for_the_object_are_defined_operations, Complex2Fixture)
		BOOST_AUTO_TEST_CASE(binary_plus_for_two_complex_numbers)
		{
			CComplex result = complex1 + complex2;
			CheckArgumentsOfComplexNumber(result, 6, -11);
		}
		BOOST_AUTO_TEST_CASE(binary_plus_for_complex_and_real_number)
		{			
			CComplex result = real + complex2;
			CheckArgumentsOfComplexNumber(result, -5, -9);

			CComplex result2 = complex2 + real;
			CheckArgumentsOfComplexNumber(result, -5, -9);
		}

		BOOST_AUTO_TEST_CASE(binary_minus_for_two_complex_numbers)
		{
			CComplex result = complex1 - complex2;
			CheckArgumentsOfComplexNumber(result, -4, 7);

			CComplex result2 = complex2 - complex1;
			CheckArgumentsOfComplexNumber(result2, 4, -7);
		}
		BOOST_AUTO_TEST_CASE(binary_minus_for_complex_and_real_number)
		{
			CComplex result = real - complex2;
			CheckArgumentsOfComplexNumber(result, -15, 9);

			CComplex result2 = complex2 - real;
			CheckArgumentsOfComplexNumber(result2, 15, -9);
		}

		BOOST_AUTO_TEST_CASE(multiplication_for_two_complex_numbers)
		{
			CComplex result = complex1 * complex2;
			CheckArgumentsOfComplexNumber(result, -13, -19);

			CComplex result2 = complex2 * complex1;
			CheckArgumentsOfComplexNumber(result2, -13, -19);
		}
		BOOST_AUTO_TEST_CASE(multiplication_for_complex_and_real_number)
		{
			CComplex result = real * complex2;
			CheckArgumentsOfComplexNumber(result, -50, 90);

			CComplex result2 = complex2 * real;
			CheckArgumentsOfComplexNumber(result2, -50, 90);
		}

		BOOST_AUTO_TEST_CASE(division_for_two_complex_numbers)
		{
			CComplex result = complex2 / complex1;
			CheckArgumentsOfComplexNumber(result, 4.6, 0.2);

			CComplex result2 = complex1 / complex1;
			CheckArgumentsOfComplexNumber(result2, 1, 0);
		}
		BOOST_AUTO_TEST_CASE(division_for_complex_and_real_number)
		{
			CComplex result = complex2 / real;
			CheckArgumentsOfComplexNumber(result, -0.5, 0.9);

			double real2 = 2;
			CComplex result2 = real2 / complex1;
			CheckArgumentsOfComplexNumber(result2, 0.4, 0.8);
		}

		BOOST_AUTO_TEST_CASE(unary_operator_plus)
		{
			CComplex result = +complex1;
			CheckArgumentsOfComplexNumber(result, 1, -2);

			CComplex result2 = +complex2;
			CheckArgumentsOfComplexNumber(result2, 5, -9);
		}

		BOOST_AUTO_TEST_CASE(unary_operator_minus)
		{
			CComplex result = -complex1;
			CheckArgumentsOfComplexNumber(result, -1, 2);

			CComplex result2 = -complex2;
			CheckArgumentsOfComplexNumber(result2, -5, 9);
		}

		BOOST_AUTO_TEST_CASE(addition_assignment_operator)
		{
			CComplex result = complex1;
			result += complex2;
			CheckArgumentsOfComplexNumber(result, 6, -11);
		}

		BOOST_AUTO_TEST_CASE(subtraction_assignment_operator)
		{
			CComplex result = complex1;
			result -= complex2;
			CheckArgumentsOfComplexNumber(result, -4, 7);
		}
		// оставшиеся операторы
		BOOST_AUTO_TEST_CASE(multiply_assignment_operator)
		{
			CComplex result = complex1;
			result *= complex2;
			CheckArgumentsOfComplexNumber(result, -13, -19);
		}

		BOOST_AUTO_TEST_CASE(division_assignment_operator)
		{
			CComplex result = complex2;
			result /= complex1;
			CheckArgumentsOfComplexNumber(result, 4.6, 0.2);
		}

		BOOST_AUTO_TEST_CASE(comparison_operators_operator)
		{
			CComplex copyComplex1 = complex1;
			AreComplexNumbersEqual(copyComplex1, complex1);
			BOOST_CHECK(copyComplex1 == complex1);
			BOOST_CHECK(complex2 != complex1);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()