#pragma once
#include "stdafx.h"

enum struct ModeOfOperation
{
	Crypt, Decrypt
};

int ReadNumberFromString(const std::string& notation);

uint8_t CryptByte(uint8_t byte, const int key);

uint8_t DecryptByte(const uint8_t byte, const int key);

bool TryCrypt(std::istream& input, std::ostream& output, const int key, const ModeOfOperation& mode);

ModeOfOperation GetMode(const std::string& modeArgc);

int GetKeyParamether(const std::string& modeArgc);

std::ifstream OpenFileForBinReading(const std::string& fileName);

std::ofstream OpenFileForBinWriting(const std::string& fileName);

void CopyFileWithEncryption(char* argv[]);