#include "SubstCipher.h"
#include "Utils.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <iostream>

std::string GetSubstitutionTable(const std::string& alphabet, const std::string& keyInput) {
    // 1. Если пользователь сам ввёл строку-ключ нужной длины
    if (!keyInput.empty() && keyInput.length() == alphabet.length()) {
        std::ofstream outFile("keytable.txt");
        if (outFile.is_open()) {
            outFile << keyInput;
            outFile.close();
        }
        return keyInput;
    }

    // 2. Если пользователь ввёл имя файла (например, keytable.txt) — пробуем прочитать из него
    std::ifstream inFile(keyInput.empty() ? "keytable.txt" : keyInput);
    if (inFile.is_open()) {
        std::string loadedKey;
        std::getline(inFile, loadedKey);
        inFile.close();
        if (loadedKey.length() == alphabet.length()) {
            std::cout << "[Инфо] Ключ успешно загружен из файла!\n";
            return loadedKey;
        }
    }

    // 3. Если файла нет или ключ не подошёл — генерируем новый случайный ключ
    std::string keyTable = alphabet;
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(keyTable.begin(), keyTable.end(), rng);

    // Сохраняем сгенерированный ключ в файл keytable.txt
    std::ofstream outFile("keytable.txt");
    if (outFile.is_open()) {
        outFile << keyTable;
        outFile.close();
        std::cout << "[Инфо] Новый ключ сгенерирован и сохранён в файл 'keytable.txt'\n";
    }

    return keyTable;
}

std::string EncryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable) {
    std::string result = "";
    for (char c : text) {
        int idx = findIndex(c, alphabet);
        if (idx != -1 && idx < static_cast<int>(keyTable.length())) {
            result += keyTable[idx];
        }
        else {
            result += c;
        }
    }
    return result;
}

std::string DecryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable) {
    std::string result = "";
    for (char c : text) {
        int idx = findIndex(c, keyTable);
        if (idx != -1 && idx < static_cast<int>(alphabet.length())) {
            result += alphabet[idx];
        }
        else {
            result += c;
        }
    }
    return result;
}