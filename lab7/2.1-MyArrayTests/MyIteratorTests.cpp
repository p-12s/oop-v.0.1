#include "stdafx.h"

using namespace std;

struct Test
{
	
};

/*
����������� ���������� �������� � ����� �������
� ����������� ��������� ���������� ���������, ������������ � �������
� ����������� ������������� ���������������� ������� � ��������� ������� 
��� ������ ��������� �[]�. � ������, ���� ������ �������� ������� �� ������� �������, 
������ ������������� ���������� std::out_of_range
� ����������� ��������� ����� ������� ��� ������ ������ Resize(). 
� ������, ���� ����� ����� ������� ������ �������, ����������� � ����� ������� 
�������� ������ ������������������ ��������� �� ��������� ��� ���� T.
� ����������� ����������� ������� (�������� ���� ��� ���������) ��� ������ ������ Clear.
� ����������� ����������� � �������� ������������
� ����������� ����������� � ������������ �������� ������������
� ������ begin() � end(), � ����� rbegin() � rend(), ������������ ��������� ��� �������� 
��������� ������� � ������ � �������� �������.
 */

BOOST_FIXTURE_TEST_SUITE(MyIterator, Test)
// ����� ���� ������
// 
// 
// 
// 
// 
// 
// 
// 
	BOOST_AUTO_TEST_CASE(test_test)
	{
		BOOST_CHECK(true);
	}

BOOST_AUTO_TEST_SUITE_END()