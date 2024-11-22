// ���, ����� �Ҽ� 2 / 10.4
// 4134	���� �Ҽ�

// n ��ŭ ��ǲ�� �޾� �迭�� ������ �迭�� �����ϰ�
// �迭�ϳ��� ������ ���� �Ҽ��� �������� �ε��� ���� ++ �ϸ� ���.

#include <stdio.h>
#include <math.h>

// �Ҽ� �Ǻ� �Լ�: �����ٱ����� ������ Ȯ��
// : ¦���� ��� �Ҽ��� �ƴϰ� Ȧ���� ���������� ������ �������� ���� Ȯ���غ��� �ƴϸ� �Ҽ���.
int is_prime(long long n) {
    if (n < 2) return 0; // 2���� ���� ���� �Ҽ��� �ƴ�
    if (n == 2) return 1; // 2�� �Ҽ�
    if (n % 2 == 0) return 0; // ¦���� �Ҽ��� �ƴ�

    long long sqrt_n = (long long)sqrt(n);
    for (long long i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0) return 0; // ������ �������� �Ҽ��� �ƴ�
    }
    return 1; // �Ҽ���
}

// ���� �Ҽ� ã��
long long next_prime(long long n) {
    if (n <= 1) return 2; // 1 ������ ��� 2�� ù �Ҽ�
    long long candidate = n;

    if (candidate % 2 == 0) candidate++; // ¦���� 1�� ���ؼ� Ȧ���� ����
    else candidate += 2; // Ȧ���� ���� Ȧ���� �̵�

    while (!is_prime(candidate)) {
        candidate += 2; // �Ҽ��� �ƴϸ� ���� Ȧ���� �̵�
    }

    return candidate;
}

int main() {
    int t;
    scanf("%d", &t); // �׽�Ʈ ���̽� ���� �Է�

    while (t--) {
        long long n;
        scanf("%lld", &n); // �־��� �� �Է�
        printf("%lld\n", next_prime(n));
    }

    return 0;
}
