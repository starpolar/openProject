#include <stdio.h>

int main() { //2563	������
    int n; // �������� ��
    int paper[100][100] = { 0 }; // 100x100 ��ȭ��, �ʱⰪ�� ��� 0
    int x, y; // �������� ��ǥ
    int count = 0; // �����̰� �ٿ��� ������ ����

    // ������ �� �Է�
    scanf("%d", &n);

    // �� �������� ���� �Ʒ� ��ǥ�� �޾ƿ� ��ȭ���� ǥ��
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);

        // �������� ũ��� 10x10
        for (int j = x; j < x + 10; j++) {
            for (int k = y; k < y + 10; k++) {
                // �ش� ������ 1�� ǥ��
                paper[j][k] = 1;
            }
        }
    }

    // ��ȭ������ 1�� ǥ�õ� ������ ���� ���
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (paper[i][j] == 1) {
                count++;
            }
        }
    }

    // ��� ���
    printf("%d\n", count);

    return 0;
}
