#include "SubstCipher.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>

std::string GetSubstitutionTable(const std::string& alphabet, const std::string& userKeyInput, const std::string& filename) {
    // 1. Check if the user provided a key string or a key file path
    if (!userKeyInput.empty()) {
        std::ifstream userFile(userKeyInput);
        if (userFile.is_open()) {
            std::string fileKey;
            std::getline(userFile, fileKey);
            userFile.close();
            if (fileKey.length() == alphabet.length()) {
                std::cout << "[Инфо] Загружена таблица замен из файла: " << userKeyInput << std::endl;
                return fileKey;
            }
        }
        if (userKeyInput.length() == alphabet.length()) {
            std::cout << "[Инфо] Использована таблица замен от пользователя." << std::endl;
            return userKeyInput;
        }
    }

    // 2. Read from an existing default file
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string savedKey;
        std::getline(inFile, savedKey);
        inFile.close();
        if (savedKey.length() == alphabet.length()) {
            std::cout << "[Инфо] Загружена таблица замен из файла: " << filename << std::endl;
            return savedKey;
        }
    }

    // 3. Generate a new key table and save it to a file
    std::cout << "[Инфо] Таблица замен не найдена. Генерация новой..." << std::endl;
    std::string keyTable = alphabet;
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(keyTable.begin(), keyTable.end(), rng);

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << keyTable; // Save the shuffled alphabet string to the text file
        outFile.close();
        std::cout << "[Успех] Новая таблица замен сохранена в файл: " << filename << std::endl;
    }

    return keyTable;
}

std::string EncryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable) {
    std::string result = "";
    for (char symbol : text) {
        int pos = findIndex(symbol, alphabet);
        if (pos != -1) {
            result += keyTable[pos];
        }
        else {
            result += symbol;
        }
    }
    return result;
}

std::string DecryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable) {
    std::string result = "";
    for (char symbol : text) {
        int pos = findIndex(symbol, keyTable);
        if (pos != -1) {
            result += alphabet[pos];
        }
        else {
            result += symbol;
        }
    }
    return result;
}