#include <stdio.h>

int main() {//5073	�ﰢ���� �� ��, ����: ���簢���� �ﰢ��
    int a, b, c, max, other;

    for (; ;) {
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

        if (a == 0 && b == 0 && c == 0) break;
        else if (max >= other) printf("Invalid");
        else if (a == b && b == c && a == c) printf("Equilateral");
        else if (a == b || b == c || a == c) printf("Isosceles");
        else printf("Scalene");
        printf("\n"); // ���ų�, �߰��� �� ����ϸ� ��������. ������ ������ �Ѿ�µ�.
    }

    return 0;
}