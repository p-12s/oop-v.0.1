#include "stdafx.h"
#include "..\1-Vector\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

bool VerifyProcessVectory(vector<double> originalVector, vector<double> expectedResult)
{
	ProcessVector(originalVector);
	return VectorsAreEqual(originalVector, expectedResult);
}

// 4. ��������� ��������� �������� ������� �� �������� ������������� ��������

// ������� ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// ������� ������ ������ �� ������� �������
	BOOST_AUTO_TEST_CASE(dont_change_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	// �� ������ ������ ������������ �������� max=0
	BOOST_AUTO_TEST_CASE(does_not_divide_vector_in_which_maximum_element_this_zero)
	{
		BOOST_CHECK(VerifyProcessVectory({ -11.0, -2.0, 0.0 }, { -11.0, -2.0, 0.0 }));
	}

	// ����� ������� ������� �� �������� ������������� ��������
	BOOST_AUTO_TEST_CASE(dividing_every_vectors_element_by_half_max_element)
	{
		BOOST_CHECK(VerifyProcessVectory({ -7.0, 4.0, 2.0 }, { -3.5, 2.0, 1.0 }));
	}

BOOST_AUTO_TEST_SUITE_END()