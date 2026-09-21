#pragma once
#include <string>

std::string EncryptShift(const std::string& text, const std::string& alphabet, int shift);
std::string DecryptShift(const std::string& text, const std::string& alphabet, int shift);