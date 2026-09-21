#pragma once
#include <string>

// Helper function to find the index of a character in the alphabet
int findIndex(char symbol, const std::string& alphabet);

// Generates an alphabet string by matching symbols from defaultAlphabet against a user regex pattern
std::string BuildAlphabetFromRegex(const std::string& defaultAlphabet, const std::string& userPattern);