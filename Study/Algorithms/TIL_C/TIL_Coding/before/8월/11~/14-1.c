#include <stdio.h>

int reverse(int num) {
    int reversed = 0;

    // ���ڸ� ������ ����
    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }

    return reversed;
}

int main() { // 2908	��� ������.
    int a, b;

    // �� ���� ���� �Է�
    scanf("%d %d", &a, &b);

    // ������ ������ ������
    int rev_a = reverse(a);
    int rev_b = reverse(b);

    // �� ū ���� ���
    if (rev_a > rev_b) {
        printf("%d\n", rev_a);
    }
    else {
        printf("%d\n", rev_b);
    }

    return 0;
}
