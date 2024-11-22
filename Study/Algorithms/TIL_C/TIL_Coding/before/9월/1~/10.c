#include <stdio.h>

int main() {//11653	소인수분해, 배수와 소수
    int n;
    scanf("%d", &n);

    if (n == 1) return 0;

    for (; ;) {
        for (int i = 2; i <= n; i++) {
            if (n % i == 0) {
                n /= i;
                printf("%d", i);
                break;
            }
        }
        if (n == 1) return 0;
        printf("\n");
    }

    return 0;
}