// ���, ����� �Ҽ� 2 / 9.30
// 1934	�ּҰ����
#include <stdio.h>

// �ִ�����(GCD)�� ���ϴ� �Լ�
// ��Ŭ���� ȣ���� ���.
// ��Ŭ���� ȣ����(Euclidean Algorithm)�� 
// �� ���� **�ִ�����(Greatest Common Divisor, GCD)**�� ������ ���ϴ� �˰����Դϴ�. 
// �� ����� 2,300�� �� �׸����� ������ ��Ŭ���尡 ������ �˰�������,
// �� ���� �������� �̿��Ͽ� ����� �ݺ������ν� �ִ������� ã���ϴ�
int gcd(int a, int b) {
	while (b != 0) {
		int temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

// �ּҰ����(LCM)�� ���ϴ� �Լ�
int lcm(int a, int b) {
	return a * b / gcd(a, b);
}

int main() {
	int t;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		// �ּҰ���� ���
		printf("%d\n", lcm(a, b));
	}

	return 0;
}



#include <stdio.h>

int main() {
	int t;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		int a, b, res, multipSum = 1;
		scanf("%d %d", &a, &b);

		if (a == 1 || b == 1) {
			printf("%d\n", a * b);
			continue;
		}
		else if (a == b) {
			printf("%d\n", a);
			continue;
		}
		else {
			while (a > 0 && b > 0) {
				if (a % 2 == 0 && b % 2 == 0) {
					a /= 2;
					b /= 2;
					multipSum *= 2;
				}
				else if (a % 3 == 0 && b % 3 == 0) {
					a /= 3;
					b /= 3;
					multipSum *= 3;
				}
				else if (a % 5 == 0 && b % 5 == 0) {
					a /= 5;
					b /= 5;
					multipSum *= 5;
				}
				else if (a % 7 == 0 && b % 7 == 0) {
					a /= 7;
					b /= 7;
					multipSum *= 7;
				}
				else break;
			}
			printf("%d\n", a * b * multipSum);
		}
	}

	return 0;
}