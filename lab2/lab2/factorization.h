#pragma once
#include <vector>
#include <utility>
#include <cmath>

inline std::vector<long long> trialDivision(long long n) {
    std::vector<long long> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    for (long long i = 3; i <= std::sqrt(n); i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2) {
        factors.push_back(n);
    }
    return factors;
}

inline std::pair<long long, long long> fermatFactorization(long long n) {
    if (n % 2 == 0) {
        return { 2, n / 2 };
    }
    long long a = static_cast<long long>(std::ceil(std::sqrt(static_cast<double>(n))));
    long long b2 = a * a - n;
    long long b = static_cast<long long>(std::round(std::sqrt(static_cast<double>(b2))));

    while (b * b != b2) {
        a++;
        b2 = a * a - n;
        b = static_cast<long long>(std::round(std::sqrt(static_cast<double>(b2))));
    }
    return { a - b, a + b };
}