#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
#endif

#include "algo.h"

using namespace math;

static void printMenu() {
    std::cout << "\n========== МЕНЮ ==========\n"
        << "1. Функция Эйлера\n"
        << "2. Расширенный алгоритм Евклида\n"
        << "3. Китайская теорема об остатках\n"
        << "0. Выход\n"
        << "Выбор: ";
}

static void runEulerPhi() {
    std::cout << "Введите n: ";
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);
    u64 n;
    if (!(iss >> n)) { std::cout << "Неверный ввод\n"; return; }

    auto t0 = Clock::now();
    u64 result = eulerPhi(n);
    auto t1 = Clock::now();
    double ms = Ms(t1 - t0).count();

    std::cout << "φ(" << n << ") = " << result << "\n";
    std::cout << "Время: " << ms << " мс\n";
}

static void runGcd() {
    std::cout << "Введите a и b: ";

    std::string line;
    std::getline(std::cin, line);

    // Replace any non-digit (except '-') with space for flexible parsing
    for (char& c : line)
        if (!std::isdigit((unsigned char)c) && c != '-')
            c = ' ';

    std::istringstream iss(line);
    u64 a, b;
    if (!(iss >> a >> b)) { std::cout << "Неверный ввод\n"; return; }

    i64 x = 0, y = 0;
    auto t0 = Clock::now();
    i64 d = extended_gcd((i64)a, (i64)b, x, y);
    auto t1 = Clock::now();
    double ms = Ms(t1 - t0).count();

    std::cout << "gcd(" << a << ", " << b << ") = " << d << "\n";
    std::cout << "x = " << x << ", y = " << y << "\n";
    std::cout << "Проверка: " << a << " * " << x << " + "
        << b << " * " << y << " = "
        << (i64)a * x + (i64)b * y << "\n";
    std::cout << "Время: " << ms << " мс\n";
}


static void runCrt() {
    // Number of equations
    std::cout << "Количество уравнений: ";
    std::string line;
    std::getline(std::cin, line);

    size_t n;
    {
        std::istringstream iss(line);
        if (!(iss >> n) || n == 0) {
            std::cout << "Неверное количество\n";
            return;
        }
    }

    std::cout << "Введите модули m_i (через пробел):\n  ";
    std::getline(std::cin, line);

    std::vector<u64> ms;
    {
        std::istringstream iss(line);
        u64 x;
        while (iss >> x) ms.push_back(x);
    }
    if (ms.size() != n) {
        std::cout << "Ожидалось " << n << " модулей, введено "
            << ms.size() << "\n";
        return;
    }

    std::cout << "Введите остатки r_i (через пробел):\n  ";
    std::getline(std::cin, line);

    std::vector<u64> rs;
    {
        std::istringstream iss(line);
        u64 x;
        while (iss >> x) rs.push_back(x);
    }
    if (rs.size() != n) {
        std::cout << "Ожидалось " << n << " остатков, введено "
            << rs.size() << "\n";
        return;
    }

    // Time and solve
    auto t0 = Clock::now();
    u64 x = crt(ms, rs);
    auto t1 = Clock::now();
    double ms_time = Ms(t1 - t0).count();

    // Check if x == 0 is a trivial solution or an error
    if (x == 0) {
        bool trivial = true;
        for (size_t i = 0; i < n; ++i)
            if (rs[i] % ms[i] != 0) { trivial = false; break; }

        if (!trivial) {
            std::cout << "Решения нет (модули не взаимно просты"
                " или переполнение)\n";
            return;
        }
    }

    std::cout << "Решение: x = " << x << "\n";
    std::cout << "Проверка:\n";
    for (size_t i = 0; i < n; ++i) {
        bool ok = (x % ms[i] == rs[i] % ms[i]);
        std::cout << "  " << x << " % " << ms[i] << " = " << x % ms[i]
            << "  (ожидается " << rs[i] % ms[i] << ") "
            << (ok ? "OK" : "FAIL") << "\n";
    }
    std::cout << "Время: " << ms_time << " мс\n";
}


int main() {
    setlocale(LC_ALL,"");
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << std::fixed << std::setprecision(6);

    int choice;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');

        if (choice == 0) break;

        switch (choice) {
        case 1: runEulerPhi(); break;
        case 2: runGcd();      break;
        case 3: runCrt();      break;
        default: std::cout << "Неверный выбор.\n";
        }
    }

    std::cout << "Выход.\n";
    return 0;
}