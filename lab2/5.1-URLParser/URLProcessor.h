#pragma once
#include "stdafx.h"

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(std::string const& url, Protocol&  protocol, int& port, std::string& host, std::string& document);

bool IsUrlValid(std::string url);