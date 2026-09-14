#include "Utils.h"

int findIndex(char symbol, const std::string& alphabet) {
    for (size_t i = 0; i < alphabet.length(); ++i) {
        if (alphabet[i] == symbol) {
            return static_cast<int>(i);
        }
    }
    return -1; // Return -1 if character is not in the alphabet
}