#include <stdio.h>

int main() {
    int a, b;

    while (1) {
        // �� ���� �Է¹޽��ϴ�.
        scanf("%d %d", &a, &b);

        // �Է��� 0 0�̸� ���α׷��� �����մϴ�.
        if (a == 0 && b == 0) {
            break;
        }

        // ù ��° ���� �� ��° ���� ����� ���
        if (b % a == 0) {
            printf("factor\n");
        }
        // ù ��° ���� �� ��° ���� ����� ���
        else if (a % b == 0) {
            printf("multiple\n");
        }
        // �� �� �ƴ� ���
        else {
            printf("neither\n");
        }
    }

    return 0;
}
