#include "SubstCipher.h"
#include "Utils.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>

static bool IsValidSubstitutionTable(const std::string& alphabet,
    const std::string& keyTable) {
    if (alphabet.length() != keyTable.length()) return false;

    std::set<char> aSet(alphabet.begin(), alphabet.end());
    std::set<char> kSet(keyTable.begin(), keyTable.end());
    return aSet == kSet;
}

static bool LoadKeyFromFile(const std::string& fileName,
    const std::string& alphabet,
    std::string& outKey) {
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile.is_open()) {
        std::cout << "[Ошибка] Не удалось открыть файл '" << fileName << "'\n";
        return false;
    }

    std::string loadedKey;
    std::getline(inFile, loadedKey);
    inFile.close();

    if (loadedKey.size() >= 3 &&
        static_cast<unsigned char>(loadedKey[0]) == 0xEF &&
        static_cast<unsigned char>(loadedKey[1]) == 0xBB &&
        static_cast<unsigned char>(loadedKey[2]) == 0xBF) {
        loadedKey.erase(0, 3);
    }

    while (!loadedKey.empty() &&
        (loadedKey.back() == '\r' ||
            loadedKey.back() == '\n' ||
            loadedKey.back() == ' ' ||
            loadedKey.back() == '\t')) {
        loadedKey.pop_back();
    }

    if (!IsValidSubstitutionTable(alphabet, loadedKey)) {
        std::cout << "[Ошибка] Содержимое файла не является перестановкой "
            "текущего алфавита.\n";
        return false;
    }

    outKey = loadedKey;
    return true;
}

static bool SaveKeyToFile(const std::string& fileName,
    const std::string& keyTable) {
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cout << "[Ошибка] Не удалось открыть '" << fileName
            << "' для записи.\n";
        return false;
    }
    outFile << keyTable;
    outFile.close();
    return true;
}

std::string GetSubstitutionTable(const std::string& alphabet,
    const std::string& keyInput) {
    const std::string defaultFileName = "keytable.txt";
    std::string key;

    // ---- ВЕТКА 1: явная генерация новой таблицы ----
    if (keyInput == "__GENERATE__") {
        key = alphabet;
        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(key.begin(), key.end(), rng);

        std::cout << "[Инфо] Сгенерирована новая случайная таблица замен.\n";

        // Принудительно удаляем старый файл, чтобы не путаться
        std::remove(defaultFileName.c_str());

        if (SaveKeyToFile(defaultFileName, key)) {
            std::cout << "[Инфо] Таблица сохранена в '" << defaultFileName << "'\n";
        }
        return key;
    }

    // ---- ВЕТКА 2: пользователь ввёл готовую строку-ключ ----
    if (!keyInput.empty() &&
        keyInput.length() == alphabet.length() &&
        IsValidSubstitutionTable(alphabet, keyInput)) {
        if (SaveKeyToFile(defaultFileName, keyInput)) {
            std::cout << "[Инфо] Введённая таблица сохранена в '"
                << defaultFileName << "'\n";
        }
        return keyInput;
    }

    // ---- ВЕТКА 3: пользователь указал имя файла ----
    if (!keyInput.empty()) {
        if (LoadKeyFromFile(keyInput, alphabet, key)) {
            std::cout << "[Инфо] Таблица замен загружена из файла '"
                << keyInput << "'\n";
            return key;
        }
        std::cout << "[Предупреждение] Не удалось загрузить из '"
            << keyInput << "'. Будет сгенерирована новая.\n";
    }

    std::cout << "[Инфо] Будет сгенерирована новая случайная таблица.\n";
    key = alphabet;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(key.begin(), key.end(), rng);

    if (SaveKeyToFile(defaultFileName, key)) {
        std::cout << "[Инфо] Таблица сохранена в '" << defaultFileName << "'\n";
    }

    return key;
}

std::string EncryptSubst(const std::string& text,
    const std::string& alphabet,
    const std::string& keyTable) {
    std::string result;
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

std::string DecryptSubst(const std::string& text,
    const std::string& alphabet,
    const std::string& keyTable) {
    std::string result;
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