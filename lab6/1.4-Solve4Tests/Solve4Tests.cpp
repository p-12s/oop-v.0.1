#include "stdafx.h"
#include "../1.4-Solve4/Solve4.h"

using namespace std;

struct Solve4Fixture
{
	double a = 16;
	double b = 0;
	double c = 145;
	double d = 0;
	double e = 9;
	CSolve4 solve4;

	Solve4Fixture()
		: solve4(a, b, c, d, e)
	{
	}

	void CheckSolve4Roots(const EquationRoot4& equationRoot4, const vector<double>& roots)
	{
		BOOST_CHECK_EQUAL(roots.size(), equationRoot4.numRoots);
		for (auto i = 0; i < equationRoot4.numRoots; ++i)
		{
			BOOST_CHECK_CLOSE(equationRoot4.roots[i], roots[i], DBL_EPSILON);
		}
	}

	// проверка по теореме виета - связь корней с коэффициентами/ нужна иниц. всех 4-х корней
	void VerificationRootsByTheoremOfVieta(const EquationRoot4& equationRoot4, 
		double a, double b, double c, double d, double e)
	{
		// если заполнить неиниц корни нулями - будет ок, но лучше дождусь примера с 2-мя+ корями
		double x1 = equationRoot4.roots[0];
		double x2 = equationRoot4.roots[1];
		double x3 = equationRoot4.roots[2];
		double x4 = equationRoot4.roots[3];

		BOOST_CHECK(x1 + x2 + x3 + x4 == -(b / a));
		BOOST_CHECK(x1*x2 + x1*x3 + x1*x4 + x2*x3 + x2*x4 + x3*x4 == c / a);
		BOOST_CHECK(x1*x2*x3 + x1*x2*x4 + x1*x3*x4 + x2*x3*x4 == -d / a);
		BOOST_CHECK(x1*x2*x3*x4 == e / a);
	}



};

BOOST_FIXTURE_TEST_SUITE(Solve4, Solve4Fixture)

	BOOST_AUTO_TEST_CASE(the_coefficient_of_x_in_4_degree_can_not_be_0)
	{
		BOOST_CHECK_THROW(CSolve4(0, b, c, d, e), invalid_argument);
		BOOST_CHECK_NO_THROW(CSolve4(a, b, c, d, e));
	}

// может иметь 1 корень
	BOOST_AUTO_TEST_CASE(solution_with_1_root)
	{
		CSolve4 solve4 = CSolve4(1, 0, 0, 0, 0);
		vector<double> expectedRoots = {0};
		EquationRoot4 answer = solve4.GetRootsOfEquation();
		// CheckRoots(Solve4(1, 0, 0, 0, 0), 4, expectedRoots1);
		CheckSolve4Roots(answer, expectedRoots);
		//VerificationRootsByTheoremOfVieta(answer, 1, 0, 0, 0, 0);
	}

	/*BOOST_AUTO_TEST_CASE(test_2)
	{
		CSolve4 solve4 = CSolve4(2, 5, -11, -20, 12);
		vector<double> expectedRoots = { 2, 0.5, -2, 3 };
		EquationRoot4 answer = solve4.GetRootsOfEquation();
		CheckSolve4Roots(answer, expectedRoots);
		//VerificationRootsByTheoremOfVieta(answer, 1, 0, 0, 0, 0);
	}*/
// может иметь 2 корень
// может иметь 3 корень
// может иметь 4 корень

/*
	BOOST_AUTO_TEST_CASE(solution_with_2_roots)
	{
		EquationRoot4 answer;
		std::vector<double> coef = { 1, 0, -2, 0, 1 };
		answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
		BOOST_CHECK_EQUAL(answer.numRoots, 2);
		CheckSolve4(answer, coef);

		coef = { 1, 1, 0, 0, 0 };
		answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
		BOOST_CHECK_EQUAL(answer.numRoots, 2);
		CheckSolve4(answer, coef);

		coef = { 4, -12, 13, -6, 1 };
		answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
		BOOST_CHECK_EQUAL(answer.numRoots, 2);
		CheckSolve4(answer, coef);
	}
	BOOST_AUTO_TEST_CASE(solution_with_3_roots)
	{
		EquationRoot4 answer;
		std::vector<double> coef = { 2, -3, 1, 0, 0 };
		answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
		BOOST_CHECK_EQUAL(answer.numRoots, 3);
		CheckSolve4(answer, coef);

		coef = { 2, -9, 14, -9, 2 };
		answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
		BOOST_CHECK_EQUAL(answer.numRoots, 3);
		CheckSolve4(answer, coef);

	}
	BOOST_AUTO_TEST_CASE(solution_with_4_roots)
	{
		EquationRoot4 answer;
		std::vector<double> coef = { 1, -2, -1, 2, 0 };
		answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
		BOOST_CHECK_EQUAL(answer.numRoots, 4);
		CheckSolve4(answer, coef);

		coef = { 4, -12, 7, 3, -2 };
		answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
		BOOST_CHECK_EQUAL(answer.numRoots, 4);
		CheckSolve4(answer, coef);

	}
	*/


// максимальный действительный корень уравнения третьей степени
//in_the_case_of_the_three_roots_in_the_equation
//in_the_case_of_the_same_root
//in_the_case_of_two_different_roots

// уравнение 4 степени
//not_have_highest_coefficient_of_zero
//can_have_no_roots
//has_four_equal_real_roots
//has_different_real_roots
//has_two_real_roots

BOOST_AUTO_TEST_SUITE_END()