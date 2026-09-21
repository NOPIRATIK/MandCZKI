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

    int cipher_type = 0;
    std::string alphabet;
    std::string mode;
    std::string text;
    int shift = 0;
    std::string userKeyInput = "";

    while (true) {
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

        std::cout << "\nСтандартный алфавит:\n " << default_alphabet << std::endl;
        std::cout << "1. Введите Regex диапазон (например: [а-г], [а-я0-9], [0-9], чтобы включить ё ы диапозон [а-яё])\n";
        std::cout << "   (Enter — использовать весь стандартный алфавит):\n> ";

        std::string userPattern;
        std::getline(std::cin, userPattern);

        if (userPattern.empty()) {
            alphabet = default_alphabet;
        }
        else {
            alphabet = BuildAlphabetFromRegex(default_alphabet, userPattern);
            if (alphabet.empty()) {
                alphabet = default_alphabet;
            }
        }

        std::cout << "Сформированный алфавит (" << alphabet.length() << " символов): " << alphabet << std::endl;

        std::cout << "\n2. Выберите режим (1 - Шифрование, 2 - Расшифрование): ";
        int mode_choice;
        std::cin >> mode_choice;
        mode = (mode_choice == 1) ? "enc" : "dec";

        if (cipher_type == 1) {
            std::cout << "3. Введите величину сдвига (K): ";
            std::cin >> shift;
            std::cin.ignore();
        }
        else {
            std::cin.ignore();
            std::cout << "3. Введите таблицу замен (Enter — сгенерировать случайную): ";
            std::getline(std::cin, userKeyInput);
        }

        std::cout << "4. Введите текст для обработки: ";
        std::getline(std::cin, text);

        std::cout << "\n--- РЕЗУЛЬТАТ ---" << std::endl;
        std::cout << "Мощность алфавита (N): " << alphabet.length() << std::endl;

        if (cipher_type == 1) {
            if (mode == "enc" || mode == "1") {
                std::cout << "Результат (шифрование сдвигом): " << EncryptShift(text, alphabet, shift) << std::endl;
            }
            else {
                std::cout << "Результат (расшифрование сдвигом): " << DecryptShift(text, alphabet, shift) << std::endl;
            }
        }
        else if (cipher_type == 2) {
            std::string keyTable = GetSubstitutionTable(alphabet, userKeyInput);
            std::cout << "Таблица замен: " << keyTable << std::endl;

            if (mode == "enc" || mode == "1") {
                std::cout << "Результат (шифрование заменой): " << EncryptSubst(text, alphabet, keyTable) << std::endl;
            }
            else {
                std::cout << "Результат (расшифрование заменой): " << DecryptSubst(text, alphabet, keyTable) << std::endl;
            }
        }
    }

    return 0;
}