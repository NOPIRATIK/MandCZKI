#include <iostream>
#include <string>
#include "ShiftCipher.h"
#include "SubstCipher.h"

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

        std::cout << " 1. Шифр подстановки (сдвиг)" << std::endl;
        std::cout << " 2. Шифр замены (таблица)" << std::endl;
        std::cout << " 0. Выход из программы" << std::endl;

        // Input validation for numerical options
        if (!(std::cin >> cipher_type)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        // Exit application if user inputs '0'
        if (cipher_type == 0) {
            std::cout << "\nЗавершение работы программы..." << std::endl;
            break;
        }

        // Validate menu choices
        if (cipher_type != 1 && cipher_type != 2) {
            std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
            continue;
        }

        std::cin.ignore(); // Flush newline buffer after reading option number

        // 1. Get alphabet from user
        std::cout << "\n1. Введите алфавит (Enter для использования стандартного):\n";
        std::getline(std::cin, alphabet);
        if (alphabet.empty()) alphabet = default_alphabet;

        // 2. Choose operation mode (Encrypt/Decrypt)
        std::cout << "2. Выберите режим (1 - Шифрование, 2 - Расшифрование): ";
        int mode_choice;
        std::cin >> mode_choice;
        mode = (mode_choice == 1) ? "enc" : "dec";

        // 3. Get cipher-specific parameter (Shift value or Substitution key)
        if (cipher_type == 1) {
            std::cout << "3. Введите величину сдвига (K): ";
            std::cin >> shift;
            std::cin.ignore();
        }
        else {
            std::cin.ignore();
            std::cout << "3. Введите таблицу замен / путь к файлу (Enter — сгенерировать/загрузить из keytable.txt): ";
            std::getline(std::cin, userKeyInput);
        }

        // 4. Input target text
        std::cout << "4. Введите текст для обработки: ";
        std::getline(std::cin, text);

        // Print processing output
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