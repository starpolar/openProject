#include <stdio.h>

int main() {//11653	���μ�����, ����� �Ҽ�
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