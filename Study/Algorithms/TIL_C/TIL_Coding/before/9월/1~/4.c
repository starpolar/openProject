#include <stdio.h>

int main() {//1193	�м�ã�� / �Ϲ� ���� 1
    int x = 1, y = 1, X, nextX = 2, nextY = 2, cnt = 1;
    scanf("%d", &X);

    if (X == 1) {
        printf("%d/%d", x, y);
        return 0;
    }
    for (; ;) {
        x = 1;
        y = nextX;
        cnt++;
        for (int j = 0; j < nextX - 1; j++) {
            if (cnt >= X) break;
            x++;
            y--;
            cnt++;
        }
        nextX++;
        if (cnt >= X) break;

        x = nextX;
        y = 1;
        cnt++;
        for (int j = 0; j < nextX - 1; j++) {
            if (cnt >= X) break;
            x--;
            y++;
            cnt++;
        }
        nextX++;
        if (cnt >= X) break;
    }

    printf("%d/%d", x, y);

    return 0;
} // ���� ������� ã�� ���̿���,
// �� �ܼ�ȭ �� �� �ִ� ������� �밢���� ��ȣ�� �ű��, �밢���� ���� ���ڸ� �ľ� �Ͽ� �ذ� ����.
// ��, �밢�� ��ȣ�� �밢���� ������ �밢�� �м����� ��Ģ�� ã�Ƴ��� �ܼ�ȭ ��Ų��.