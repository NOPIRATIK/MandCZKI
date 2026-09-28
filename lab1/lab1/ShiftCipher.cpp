#include "ShiftCipher.h"
#include "utils.h"

std::string EncryptShift(const std::string& text, const std::string& alphabet, int shift) {
    std::string result = "";
    int n = static_cast<int>(alphabet.length());
    if (n == 0) return text;

    for (char c : text) {
        int idx = findIndex(c, alphabet);
        if (idx != -1) {
            int newIdx = (idx + shift) % n;
            if (newIdx < 0) newIdx += n;
            result += alphabet[newIdx];
        }
        else {
            result += c;
        }
    }
    return result;
}

std::string DecryptShift(const std::string& text, const std::string& alphabet, int shift) {
    return EncryptShift(text, alphabet, -shift);
}