#include <stdio.h>

int main() {//14215	�� ����, ����: ���簢���� �ﰢ��
    int a, b, c, max, other;

    scanf("%d %d %d", &a, &b, &c);
    max = a;
    other = b + c;
    if (max < b) {
        max = b;
        other = a + c;
    }
    if (max < c) {
        max = c;
        other = a + b;
    }

    if (max < other) {
        printf("%d", a + b + c);
    }
    else {
        max = other - 1;
        printf("%d", max + other);
    }

    return 0;
}