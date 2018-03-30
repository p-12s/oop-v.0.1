#include "stdafx.h"
#include "../5.1-URLParser/URLProcessor.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(URLProcessor_function)

// При пустой входной строке возвращает false
BOOST_AUTO_TEST_CASE(with_an_empty_string_returns_false)
{
	BOOST_CHECK(IsUrlValid("") == false);
}

// При не пустой входной строке возвращает true 
BOOST_AUTO_TEST_CASE(with_an_not_empty_string_returns_true)
{
	BOOST_CHECK(IsUrlValid("http://site.ru") == true);
}

// Извлекает из строки информации об используемом протоколе
// номере порта
// имени хоста
// и имени документа

// В случае успеха функция возвращает true
// в случае ошибки – false.

// Если порт не указан, то он считается равным номеру порта по умолчанию для данного протокола 
// для HTTP – это 80
// для HTTPS – 443
// для FTP – 21



BOOST_AUTO_TEST_SUITE_END()