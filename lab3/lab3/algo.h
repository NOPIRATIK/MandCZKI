#pragma once
#include <cstdint>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>

using i64 = std::int64_t;
using u64 = std::uint64_t;

using Clock = std::chrono::steady_clock;
using Ms = std::chrono::duration<double, std::milli>;

namespace math {

    //  Extended Euclidean algorithm.
    //  Returns d = gcd(a, b) and sets x, y such that:
    //      a*x + b*y = d
    //  Coefficients may be negative (hence i64).
    inline i64 extended_gcd(i64 a, i64 b, i64& x, i64& y) {
        // Base case: gcd(0, b) = b, and 0*0 + b*1 = b
        if (a == 0) { x = 0; y = 1; return b; }

        i64 x1, y1;
        i64 d = extended_gcd(b % a, a, x1, y1);

        // Back-substitution:
        //   x = y1 - (b/a) * x1
        //   y = x1
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }

    //  Modular multiplication: (a * b) % m
    //  Avoids overflow by using binary doubling.
    //  Works with any unsigned 64-bit modulus.
    inline u64 mulmod(u64 a, u64 b, u64 m) {
        if (m == 0) return 0;
        u64 res = 0;
        a %= m;
        while (b > 0) {
            if (b & 1) {
                res += a;
                if (res >= m) res -= m;   // keep res < m
            }
            a += a;
            if (a >= m) a -= m;           // keep a < m
            b >>= 1;
        }
        return res;
    }

    //  Euler's totient function φ(n).
    //  Returns the count of integers in [1, n]
    //  that are coprime with n.
    //  Uses the formula: φ(n) = n * ∏ (1 - 1/p)
    //  for distinct prime factors p of n.
    inline u64 eulerPhi(u64 n) {
        if (n <= 1) return n;
        u64 res = n;
        // Iterate over possible prime factors up to sqrt(n)
        for (u64 i = 2; i <= n / i; ++i) {
            if (n % i == 0) {
                // Remove all powers of i from n
                while (n % i == 0) n /= i;
                // Apply the factor (1 - 1/i) to res
                res -= res / i;
            }
        }
        // If a prime factor > sqrt(original n) remains, include it
        if (n > 1) res -= res / n;
        return res;
    }

    //  Chinese Remainder Theorem.
    //  Solves the system:
    //      x ≡ rs[i] (mod ms[i])
    //  Returns x in [0, M), where M = product of ms.
    //  Returns 0 if no solution (moduli not coprime)
    //  or on overflow.
    inline u64 crt(const std::vector<u64>& ms, const std::vector<u64>& rs) {
        if (ms.empty() || ms.size() != rs.size()) return 0;

        // Compute M = product of all moduli, checking for overflow
        u64 M = 1;
        for (u64 a : ms) {
            if (a == 0) return 0;
            if (M > UINT64_MAX / a) return 0;
            M *= a;
        }

        u64 result = 0;
        for (std::size_t i = 0; i < ms.size(); ++i) {
            u64 a_i = ms[i];
            u64 r_i = rs[i] % a_i;          // normalize remainder
            u64 M_i = M / a_i;

            // Find inverse of M_i modulo a_i using extended gcd
            i64 k, m;
            i64 g = extended_gcd((i64)M_i, (i64)a_i, k, m);
            if (g != 1) return 0;           // inverse does not exist

            i64 ai = (i64)a_i;
            // Normalize k to [0, a_i)
            u64 N_i = (u64)(((k % ai) + ai) % ai);

            // term = (r_i * M_i * N_i) mod M, using mulmod
            u64 t1 = mulmod(r_i, M_i, M);
            u64 term = mulmod(t1, N_i, M);

            result += term;
            if (result >= M) result -= M;    // result %= M
        }
        return result;
    }

} // namespace math