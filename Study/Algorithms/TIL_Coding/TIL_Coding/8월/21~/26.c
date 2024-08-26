#include <stdio.h>

int main() {
    long long n;
    long long factorial = 1;

    // n 입력
    scanf("%lld", &n);

    // 팩토리얼 계산
    for (long long i = 2; i <= n; i++) {
        factorial *= i;
    }

    // 결과 출력
    printf("%lld\n", factorial);

    return 0;
}