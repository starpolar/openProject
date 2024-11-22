#include <stdio.h>

void convert_to_base(int n, int base) {
    char result[36]; // ����� ������ �迭, �ִ� 36�ڸ� (2�������� 10���� �ִ� 1000000000�� �� 30�ڸ�)
    int index = 0;

    // ��ȯ �۾�
    // ��, �����ſ��� �� ������ �Ǵ�
    // ù��° ������ b^0 �� �������� ���� �ǰ�
    // �ι�°�� b^1�� ���� �Ǵ°�. �������� �ڸ����� �ȴ�.
    while (n > 0) {
        int remainder = n % base;
        if (remainder < 10) {
            result[index++] = remainder + '0'; // ������ ���
        }
        else {
            result[index++] = remainder - 10 + 'A'; // ������ ���
        }
        n /= base;
    }

    // �������� ���
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("\n");
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);
    convert_to_base(N, B);
    return 0;
}
