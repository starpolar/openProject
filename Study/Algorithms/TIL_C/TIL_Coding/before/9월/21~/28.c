#include <stdio.h>
// ���Ʈ ���� / 9.28
int main() {//2839	���� ���
    // 3���� ���� �����ٰ� �ؾ� �¾ƶ�����.
    int n;
    scanf("%d", &n);

    int count = 0; // ���� ��

    while (n > 0) {
        if (n % 5 == 0) { // 5�� �����������
            count += n / 5;
            n = 0;
            break;
        }
        n -= 3; // 3kg ���� �ϳ� ���
        count++;
    }

    if (n < 0) { // ��Ȯ�� ���� �� ���� ���
        printf("-1\n");
    }
    else {
        printf("%d\n", count);
    }

    return 0;
}