#include "stdafx.h"
#include "../5.1-URLParser/URLProcessor.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(URLProcessor_function)

// ��� ������ ������� ������ ���������� false
BOOST_AUTO_TEST_CASE(with_an_empty_string_returns_false)
{
	BOOST_CHECK(IsUrlValid("") == false);
}

// ��� �� ������ ������� ������ ���������� true 
BOOST_AUTO_TEST_CASE(with_an_not_empty_string_returns_true)
{
	BOOST_CHECK(IsUrlValid("http://site.ru") == true);
}

// ��������� �� ������ ���������� �� ������������ ���������
// ������ �����
// ����� �����
// � ����� ���������

// � ������ ������ ������� ���������� true
// � ������ ������ � false.

// ���� ���� �� ������, �� �� ��������� ������ ������ ����� �� ��������� ��� ������� ��������� 
// ��� HTTP � ��� 80
// ��� HTTPS � 443
// ��� FTP � 21



BOOST_AUTO_TEST_SUITE_END()