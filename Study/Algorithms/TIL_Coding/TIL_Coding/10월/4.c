// 약수, 배수와 소수 2 / 10.4
// 4134	다음 소수
#include <stdio.h>
#include <stdint.h>

// (a * b) % mod를 안전하게 계산하는 함수
uint64_t mulmod(uint64_t a, uint64_t b, uint64_t mod) {
    return (a % mod) * (b % mod) % mod;
}

// (base ^ exponent) % mod를 계산하는 함수
uint64_t powmod(uint64_t base, uint64_t exponent, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exponent) {
        if (exponent & 1)
            result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

// 밀러-라빈 소수 판정 알고리즘 구현
int is_prime(uint64_t n) {
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0) return 0;

    uint64_t d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    uint64_t witnesses[] = { 2, 7, 61 };
    for (int i = 0; i < 3; i++) {
        uint64_t a = witnesses[i];
        if (a >= n) continue;
        uint64_t x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        int r;
        for (r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) break;
        }
        if (r == s) return 0;
    }
    return 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        uint64_t n;
        scanf("%llu", &n);
        if (n <= 2) {
            printf("2\n");
            continue;
        }
        while (1) {
            if (is_prime(n)) {
                printf("%llu\n", n);
                break;
            }
            n += 1;
        }
    }
    return 0;
}
