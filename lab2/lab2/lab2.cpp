#include <iostream>
#include <chrono>
#include <iomanip>
#include <windows.h>
#include "factorization.h"
#include "primality_test.h"

void handleTrialDivision() {
    long long n;
    std::cout << "\n--- Пункт 1: Метод перебора возможных делителей ---\n";
    std::cout << "Введите число: ";
    if (!(std::cin >> n) || n < 2) {
        std::cout << "Ошибка ввода.\n\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<long long> factors = trialDivision(n);
    auto duration = std::chrono::duration<double, std::micro>(
        std::chrono::high_resolution_clock::now() - start
    ).count();

    std::cout << "Множители: ";
    for (auto f : factors) std::cout << f << " ";
    std::cout << "\nВремя: " << std::fixed << std::setprecision(3) << duration << " мкс\n\n";
}

void handleFermatFactorization() {
    long long n;
    std::cout << "\n--- Пункт 2: Факторизация Ферма ---\n";
    std::cout << "Введите нечетное число: ";
    if (!(std::cin >> n) || n < 3 || n % 2 == 0) {
        std::cout << "Ошибка: нужно нечетное число >= 3.\n\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::pair<long long, long long> p = fermatFactorization(n);
    auto duration = std::chrono::duration<double, std::micro>(
        std::chrono::high_resolution_clock::now() - start
    ).count();

    std::cout << "Множители: " << p.first << " и " << p.second
        << "\nВремя: " << std::fixed << std::setprecision(3) << duration << " мкс\n\n";
}

void handleSieve() {
    long long limit;
    std::cout << "\n--- Пункт 3: Решето Эратосфена ---\n";
    std::cout << "Введите предел N: ";
    if (!(std::cin >> limit) || limit < 2) {
        std::cout << "Ошибка ввода.\n\n";
        return;
    }

    long long count = count = sieveOfEratosthenes(limit);
    auto start = std::chrono::high_resolution_clock::now();
    sieveOfEratosthenes(limit);
    auto duration = std::chrono::duration<double, std::milli>(
        std::chrono::high_resolution_clock::now() - start
    ).count();

    std::cout << "Найдено простых: " << count
        << "\nВремя: " << std::fixed << std::setprecision(3) << duration << " мс\n\n";
}

void handlePerfectNumber() {
    long long n, sum = 0;
    std::cout << "\n--- Пункт 4: Проверка на совершенство ---\n";
    std::cout << "Введите число: ";
    if (!(std::cin >> n) || n < 2) {
        std::cout << "Ошибка ввода.\n\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    bool isPerfect = isPerfectNumber(n, sum);
    auto duration = std::chrono::duration<double, std::micro>(
        std::chrono::high_resolution_clock::now() - start
    ).count();

    if (isPerfect) {
        std::cout << "Число " << n << " — совершенное!\n";
    }
    else {
        std::cout << "Не совершенное. Сумма делителей = " << sum << "\n";
    }
    std::cout << "Время: " << std::fixed << std::setprecision(3) << duration << " мкс\n\n";
}

int main() {
    setlocale(LC_ALL,"");
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    int choice = 0;

    do {
        std::cout << "========================================\n";
        std::cout << "1. Перебор возможных делителей\n";
        std::cout << "2. Факторизация Ферма\n";
        std::cout << "3. Решето Эратосфена\n";
        std::cout << "4. Проверка числа на совершенство\n";
        std::cout << "5. Выход\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Выбор (1-5): ";

        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода!\n\n";
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }

        switch (choice) {
        case 1: handleTrialDivision(); break;
        case 2: handleFermatFactorization(); break;
        case 3: handleSieve(); break;
        case 4: handlePerfectNumber(); break;
        case 5: std::cout << "Выход.\n"; break;
        default: std::cout << "Неверный выбор.\n\n";
        }
    } while (choice != 5);

    return 0;
}