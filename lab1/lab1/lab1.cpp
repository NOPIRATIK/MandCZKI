#include <iostream>
#include <string>
#include <cstdlib>
#include "ShiftCipher.h"
#include "SubstCipher.h"
#include "Utils.h"

int main() {
#ifdef _WIN32
    system("chcp 1251 > nul");
#endif

    std::string default_alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя0123456789 .,!?";

    while (true) {
        int cipher_type = 0;
        std::cout << "\n==========================================" << std::endl;
        std::cout << "=== ЛАБОРАТОРНАЯ РАБОТА: ШИФРЫ ===" << std::endl;
        std::cout << "Выберите действие:" << std::endl;
        std::cout << " 1. Шифр подстановки (сдвиг)" << std::endl;
        std::cout << " 2. Шифр замены (таблица)" << std::endl;
        std::cout << " 0. Выход из программы" << std::endl;
        std::cout << "Ваш выбор: ";

        if (!(std::cin >> cipher_type)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (cipher_type == 0) {
            std::cout << "\nЗавершение работы программы..." << std::endl;
            break;
        }

        if (cipher_type != 1 && cipher_type != 2) {
            std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
            continue;
        }

        std::cin.ignore();

        // ---------- Выбор алфавита ----------
        std::cout << "\nСтандартный алфавит:\n " << default_alphabet << std::endl;
        std::cout << "1. Введите Regex диапазон (например: [а-г], [а-я0-9], [0-9])\n";
        std::cout << "   (учтите: [а-я] не включает 'ё', для включения используйте [а-яё])\n";
        std::cout << "   (Enter — использовать весь стандартный алфавит):\n> ";

        std::string userPattern;
        std::getline(std::cin, userPattern);

        std::string alphabet;
        if (userPattern.empty()) {
            alphabet = default_alphabet;
        }
        else {
            alphabet = BuildAlphabetFromRegex(default_alphabet, userPattern);
            if (alphabet.empty()) {
                alphabet = default_alphabet;
            }
        }

        std::cout << "Сформированный алфавит (" << alphabet.length()
            << " символов): " << alphabet << std::endl;

        // ---------- Режим ----------
        std::cout << "\n2. Выберите режим (1 - Шифрование, 2 - Расшифрование): ";
        int mode_choice = 0;
        std::cin >> mode_choice;
        std::cin.ignore();

        // ---------- Параметры шифра ----------
        int shift = 0;
        std::string userKeyInput;

        if (cipher_type == 1) {
            std::cout << "3. Введите величину сдвига (K): ";
            std::cin >> shift;
            std::cin.ignore();
        }
        else {
            std::cout << "\n3. Таблица замен:\n"
                << "   1. Загрузить из указанного файла\n"
                << "   2. Сгенерировать новую случайную таблицу\n"
                << "   3. Ввести строку-ключ вручную\n"
                << "Ваш выбор: ";

            int keyChoice = 0;
            if (!(std::cin >> keyChoice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                keyChoice = 2;
            }
            std::cin.ignore();

            switch (keyChoice) {
            case 1:
                std::cout << "Введите имя файла с таблицей замен: ";
                std::getline(std::cin, userKeyInput);
                break;

            case 2:
                userKeyInput = "__GENERATE__";
                break;

            case 3:
                std::cout << "Введите строку-ключ (длиной как алфавит): ";
                std::getline(std::cin, userKeyInput);
                break;

            default:
                std::cout << "Неверный выбор. Будет сгенерирована новая таблица.\n";
                userKeyInput = "__GENERATE__";
                break;
            }
        }

        // ---------- Текст ----------
        std::cout << "4. Введите текст для обработки: ";
        std::string text;
        std::getline(std::cin, text);

        // ---------- Результат ----------
        std::cout << "\n--- РЕЗУЛЬТАТ ---" << std::endl;
        std::cout << "Мощность алфавита (N): " << alphabet.length() << std::endl;

        if (cipher_type == 1) {
            if (mode_choice == 1) {
                std::cout << "Результат (шифрование сдвигом): "
                    << EncryptShift(text, alphabet, shift) << std::endl;
            }
            else {
                std::cout << "Результат (расшифрование сдвигом): "
                    << DecryptShift(text, alphabet, shift) << std::endl;
            }
        }
        else {
            std::string keyTable = GetSubstitutionTable(alphabet, userKeyInput);
            std::cout << "Таблица замен: " << keyTable << std::endl;

            if (mode_choice == 1) {
                std::cout << "Результат (шифрование заменой): "
                    << EncryptSubst(text, alphabet, keyTable) << std::endl;
            }
            else {
                std::cout << "Результат (расшифрование заменой): "
                    << DecryptSubst(text, alphabet, keyTable) << std::endl;
            }
        }
    }

    return 0;
}