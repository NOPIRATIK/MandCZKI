#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

// Функция поиска индекса буквы в очищенном алфавите
int findIndex(char symbol, const std::string& alphabet) {
    for (size_t i = 0; i < alphabet.length(); ++i) {
        if (alphabet[i] == symbol) {
            return static_cast<int>(i);
        }
    }
    return -1; // Символ не найден
}

// 1. Функция Encrypt: Y = (X + K) mod N
std::string Encrypt(const std::string& text, const std::string& alphabet, int shift) {
    std::string result = "";
    int N = static_cast<int>(alphabet.length());

    if (N == 0) return text;

    // Нормализация сдвига (защита от отрицательных значений K)
    shift = (shift % N + N) % N;

    for (char symbol : text) {
        int index = findIndex(symbol, alphabet);
        if (index != -1) {
            int new_index = (index + shift) % N;
            result += alphabet[new_index];
        }
        else {
            // Пробелы и другие символы, не входящие в алфавит, остаются без изменений
            result += symbol;
        }
    }
    return result;
}

// 2. Функция Decrypt: X = (Y - K + N) mod N
std::string Decrypt(const std::string& text, const std::string& alphabet, int shift) {
    return Encrypt(text, alphabet, -shift);
}

// Вспомогательная функция для удаления пробелов из введенного алфавита
std::string cleanAlphabet(std::string raw_alphabet) {
    std::string cleaned = "";
    for (char c : raw_alphabet) {
        if (c != ' ' && c != '\t') {
            cleaned += c;
        }
    }
    return cleaned;
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    system("chcp 1251 > nul");
#endif

    std::string alphabet;
    std::string mode;
    std::string text;
    int shift = 0;

    // --- РЕЖИМ 1: Аргументы командной строки ---
    if (argc >= 5) {
        alphabet = cleanAlphabet(argv[1]);
        mode = argv[2];
        shift = std::stoi(argv[3]);
        text = argv[4];
    }
    // --- РЕЖИМ 2: Интерактивный режим ---
    else {
        std::cout << "=== ЛАБОРАТОРНАЯ РАБОТА: ШИФР ПОДСТАНОВКИ ===" << std::endl;

        std::cout << "1. Введите алфавит (буквы через пробел): ";
        std::getline(std::cin, alphabet);
        alphabet = cleanAlphabet(alphabet); // Удаляем пробелы для расчета N

        while (alphabet.empty()) {
            std::cout << "Алфавит не может быть пустым! Введите буквы через пробел: ";
            std::getline(std::cin, alphabet);
            alphabet = cleanAlphabet(alphabet);
        }

        std::cout << "2. Выберите режим (1 - Шифрование, 2 - Расшифрование): ";
        int choice;
        std::cin >> choice;
        mode = (choice == 1) ? "enc" : "dec";

        std::cout << "3. Введите величину сдвига (K): ";
        std::cin >> shift;

        std::cin.ignore();
        std::cout << "4. Введите текст для обработки: ";
        std::getline(std::cin, text);
    }

    // Выполнение операций
    std::string result;
    std::cout << "\n--- РЕЗУЛЬТАТ ---" << std::endl;
    std::cout << "Мощность алфавита N (без пробелов): " << alphabet.length() << std::endl;

    if (mode == "enc" || mode == "1") {
        result = Encrypt(text, alphabet, shift);
        std::cout << "Шифротекст (Y): " << result << std::endl;
    }
    else if (mode == "dec" || mode == "2") {
        result = Decrypt(text, alphabet, shift);
        std::cout << "Открытый текст (X): " << result << std::endl;
    }
    else {
        std::cout << "Ошибка: Неизвестный режим работы." << std::endl;
    }

    return 0;
}