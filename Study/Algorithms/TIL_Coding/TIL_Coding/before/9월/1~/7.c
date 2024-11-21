#include <stdio.h>

int main() {//	9506	약수들의 합 / 약수, 배수와 소수
    int n;
    for (; ;) {
        int arr[100000] = { 0 };
        int cnt = 0, perf = 0;
        scanf("%d", &n);
        if (n == -1) break;

        for (int i = 1; i <= n; i++) {
            if (n % i == 0 && n != i) {
                arr[cnt++] = i;
                perf += i;
            }
        }

        if (perf == n) {
            printf("%d =", n);
            int* p = arr;
            for (; ;) {
                printf(" %d ", *p++);
                if (*p == 0) {
                    printf("\n");
                    break;
                }
                else printf("+");
            }
        }
        else {
            printf("%d is NOT perfect.\n", n);
        }
    }

    return 0;
}