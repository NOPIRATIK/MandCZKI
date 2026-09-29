#pragma once
#include <vector>
#include <cmath>

inline long long sieveOfEratosthenes(long long limit) {
    if (limit < 2){
        return 0;
    }

    std::vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (long long p = 2; p * p <= limit; ++p) {
        if (isPrime[p]) {
            for (long long i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }

    long long count = 0;
    for (long long i = 2; i <= limit; ++i) {
        if (isPrime[i]) count++;
    }
    return count;
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