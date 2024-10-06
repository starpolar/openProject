// 약수, 배수와 소수 2 / 10.6
// 1929	소수 구하기
#include <stdio.h>
#include <stdbool.h>

#define MAX 1000000

int main() {
    int M, N;
    bool isPrime[MAX + 1]; // 소수 여부를 저장할 배열

    // 배열을 true로 초기화
    for (int i = 2; i <= MAX; i++) {
        isPrime[i] = true;
    }

    // 소수 판별 - 에라토스테네스의 체
    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false; // i의 배수는 소수가 아님
            }
        }
    }

    // 범위 입력 받기
    scanf("%d %d", &M, &N);

    // M부터 N까지의 소수 출력
    for (int i = M; i <= N; i++) {
        if (isPrime[i]) {
            printf("%d\n", i);
        }
    }

    return 0;
}
