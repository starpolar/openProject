// ���, ����� �Ҽ� 2 / 10.6
// 	4948	����Ʈ�� ����
#include <stdio.h>
#include <stdbool.h>

#define MAX 246912

int main() {
    bool isPrime[MAX + 1]; // �Ҽ� ���θ� ������ �迭
    int n;

    // �迭�� true�� �ʱ�ȭ
    for (int i = 2; i <= MAX; i++) {
        isPrime[i] = true;
    }

    // �����佺�׳׽��� ü�� ����Ͽ� �Ҽ� �Ǻ�
    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false; // i�� ����� �Ҽ��� �ƴ�
            }
        }
    }

    // �Է��� �ް� ó��
    while (1) {
        scanf("%d", &n);
        if (n == 0) break; // 0 �Է� �� ����

        int count = 0;
        for (int i = n + 1; i <= 2 * n; i++) {
            if (isPrime[i]) {
                count++; // n < i <= 2n ���� ������ �Ҽ��� ��
            }
        }

        printf("%d\n", count); // ��� ���
    }

    return 0;
}
