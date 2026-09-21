#pragma once
#include <string>

std::string GetSubstitutionTable(const std::string& alphabet, const std::string& keyInput);
std::string EncryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable);
std::string DecryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable);