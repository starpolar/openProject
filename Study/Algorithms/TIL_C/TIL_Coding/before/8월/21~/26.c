#include <stdio.h>

int main() {
    long long n;
    long long factorial = 1;

    // n �Է�
    scanf("%lld", &n);

    // ���丮�� ���
    for (long long i = 2; i <= n; i++) {
        factorial *= i;
    }

    // ��� ���
    printf("%lld\n", factorial);

    return 0;
}