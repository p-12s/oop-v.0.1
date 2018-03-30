#include "stdafx.h"
#include "URLProcessor.h"

#pragma warning (push, 3)
#pragma warning (pop)

using namespace std;

bool ParseURL(string const& url, Protocol&  protocol, int& port, string& host, string& document)
{
	return true;
}

bool IsUrlValid(string url)
{
	if (url.empty())
		return false;

	return true;
}