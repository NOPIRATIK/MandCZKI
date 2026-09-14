#ifndef SHIFT_CIPHER_H
#define SHIFT_CIPHER_H

#include <string>

// Encrypts text using shift substitution: Y = (X + K) mod N
std::string EncryptShift(const std::string& text, const std::string& alphabet, int shift);

// Decrypts shift cipher text: X = (Y - K + N) mod N
std::string DecryptShift(const std::string& text, const std::string& alphabet, int shift);

#endif // SHIFT_CIPHER_H