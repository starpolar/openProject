#include <stdio.h>

int main() {//2581	소수 / 약수, 배수와 소수
    int m, n, minority, sum = 0, min = 10000;
    scanf("%d %d", &m, &n);

    for (int i = m; i <= n; i++) {
        minority = 1;
        for (int j = 2; j < i - 1; j++) {
            if (i % j == 0) {
                minority = 0;
                break;
            }
        }

        if (minority && i != 1) {
            sum += i;
            if (i < min) min = i;
        }
    }

    if (sum == 0) {
        printf("%d", -1);
        return 0;
    }

    printf("%d\n%d", sum, min);

    return 0;
}