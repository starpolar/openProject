//#include <stdio.h>
//// �ð� ���⵵ / 9.22
//int main() {//24313	�˰��� ���� - ������ ǥ�� 1
//	long long a1, a0, c, n0;
//	scanf("%lld %lld %lld %lld", &a1, &a0, &c, &n0);
//
//	if (a1 * n0 + a0 <= c * n0) printf("1");
//	else printf("0");
//
//	return 0;
//}

#include <stdio.h>

int main() {
    long long a1, a0;
    long long c;
    long long n0;

    scanf("%lld %lld", &a1, &a0);
    scanf("%lld", &c);
    scanf("%lld", &n0);
    // a1 * n0 + a0 <= c * n0 �� ���� �״�� ���� �ȵǴ� ������,
    // �ܼ��� n = n0 ���� �����ϸ� �� �Ǵ� ������.
    // (ai-c) > 0 �Ǹ� n�� ������ �� �������� ���ϴ� ����� ���� �߻��ϹǷ� ����ó��.

    // (0 �� |ai| �� 100) ���� |ai| �� ����? : ���밪.
    // �̴� ai�� �����̵� ����̵� ���밪�� 100 �������� ��Ÿ���ϴ�.
    long long delta = a1 - c;

    if (delta <= 0) {
        long long left_side = delta * n0 + a0;
        if (left_side <= 0) {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
    }
    else {
        printf("0\n");
    }

    return 0;
}
