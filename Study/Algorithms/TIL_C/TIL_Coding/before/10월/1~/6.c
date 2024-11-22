// ���, ����� �Ҽ� 2 / 10.6
// 1929	�Ҽ� ���ϱ�
#include <stdio.h>
#include <stdbool.h>

#define MAX 1000000

int main() {
    int M, N;
    bool isPrime[MAX + 1]; // �Ҽ� ���θ� ������ �迭

    // �迭�� true�� �ʱ�ȭ
    for (int i = 2; i <= MAX; i++) {
        isPrime[i] = true;
    }

    // �Ҽ� �Ǻ� - �����佺�׳׽��� ü : ����� ��� �����Ѵٸ� ������ ��� �Ҽ���.
    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false; // i�� ����� �Ҽ��� �ƴ�
            }
        }
    }

    // ���� �Է� �ޱ�
    scanf("%d %d", &M, &N);

    // M���� N������ �Ҽ� ���
    for (int i = M; i <= N; i++) {
        if (isPrime[i]) {
            printf("%d\n", i);
        }
    }

    return 0;
}
