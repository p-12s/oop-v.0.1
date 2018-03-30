#pragma once
#include "stdafx.h"

enum struct ModeOfOperation
{
	Crypt, Decrypt, Unknown
};

int ReadNumberFromString(const std::string& notation);

uint8_t CryptByte(uint8_t& byte);

uint8_t DecryptByte(const uint8_t& byte);

bool IsFileProcessed(std::istream& input, std::ostream& output, int key, ModeOfOperation& mode);

ModeOfOperation GetModeParamether(const std::string& modeArgc);

int GetKeyParamether(const std::string& modeArgc);

void CopyFileWithEncryption(char* argv[]);