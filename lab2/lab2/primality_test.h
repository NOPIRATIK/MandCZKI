#pragma once
#include <vector>
#include <cmath>

inline bool isPrimeBySieve(long long number) {
    if (number < 2) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;

    std::vector<bool> isPrime(number + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (long long p = 3; p * p <= number; p += 2) {
        if (isPrime[p]) {
            for (long long i = p * p; i <= number; i += p) {
                isPrime[i] = false;
            }
        }
    }

    return isPrime[number];
}

inline bool isPerfectNumber(long long n, long long& outSum) {
    if (n < 2) {
        outSum = 0;
        return false;
    }
    long long sum = 1;
    long long limit = static_cast<long long>(std::sqrt(static_cast<double>(n)));

    for (long long i = 2; i <= limit; ++i) {
        if (n % i == 0) {
            sum += i;
            long long companion = n / i;
            if (companion != i) sum += companion;
        }
    }
    outSum = sum;
    return (sum == n);
}