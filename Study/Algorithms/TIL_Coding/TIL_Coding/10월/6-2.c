// 약수, 배수와 소수 2 / 10.6
// 	4948	베르트랑 공준
#include <stdio.h>
#include <stdbool.h>

#define MAX 246912

int main() {
    bool isPrime[MAX + 1]; // 소수 여부를 저장할 배열
    int n;

    // 배열을 true로 초기화
    for (int i = 2; i <= MAX; i++) {
        isPrime[i] = true;
    }

    // 에라토스테네스의 체를 사용하여 소수 판별
    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false; // i의 배수는 소수가 아님
            }
        }
    }

    // 입력을 받고 처리
    while (1) {
        scanf("%d", &n);
        if (n == 0) break; // 0 입력 시 종료

        int count = 0;
        for (int i = n + 1; i <= 2 * n; i++) {
            if (isPrime[i]) {
                count++; // n < i <= 2n 범위 내에서 소수를 셈
            }
        }

        printf("%d\n", count); // 결과 출력
    }

    return 0;
}
