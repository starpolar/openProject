#include <stdio.h>

int main() {//1978	�Ҽ� ã�� / ���, ����� �Ҽ�
    int n, x, minority = 1, cnt = 0;
    scanf("%d", &n);

    for (int _ = 0; _ < n; _++) {
        scanf("%d", &x);

        minority = 1;
        for (int i = 2; i < x - 1; i++) {
            if (x % i == 0) {
                minority = 0;
            }
        }

        if (x == 1) minority = 0;

        if (minority) cnt++;
    }

    printf("%d", cnt);

    return 0;
}