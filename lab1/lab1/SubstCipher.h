#ifndef SUBST_CIPHER_H
#define SUBST_CIPHER_H

#include <string>

// Handles loading, user input validation, or random generation of the substitution key table
std::string GetSubstitutionTable(const std::string& alphabet, const std::string& userKeyInput = "", const std::string& filename = "keytable.txt");

// Encrypts text using simple monoalphabetic substitution
std::string EncryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable);

// Decrypts text using simple monoalphabetic substitution
std::string DecryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable);

#endif // SUBST_CIPHER_H