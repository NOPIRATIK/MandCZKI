#include "ShiftCipher.h"
#include "Utils.h"

std::string EncryptShift(const std::string& text, const std::string& alphabet, int shift) {
    std::string result = "";
    int N = static_cast<int>(alphabet.length());
    if (N == 0) return text;

    shift = (shift % N + N) % N; // Normalize negative shifts

    for (char symbol : text) {
        int index = findIndex(symbol, alphabet);
        if (index != -1) {
            int new_index = (index + shift) % N;
            result += alphabet[new_index];
        }
        else {
            result += symbol; // Leave non-alphabet characters unchanged
        }
    }
    return result;
}

std::string DecryptShift(const std::string& text, const std::string& alphabet, int shift) {
    return EncryptShift(text, alphabet, -shift);
}